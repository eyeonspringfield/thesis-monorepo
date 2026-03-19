# Python script to analyze JITed code and identify common instruction patterns
# Pass the "--binary" or "-b" flag to analyze the .bin.log files instead of the .log files.

import os
import sys
from collections import defaultdict

logs_dir = 'logs'

def load_log(file_path):
    with open(file_path, "r", encoding="utf-8") as f:
        content = f.read()
    return content

def find_patterns(blocks, max_window_size=10):
    pattern_freq = defaultdict(int)
    pattern_operands = defaultdict(list)

    for window_size in range(max_window_size, 0, -1):

        for block in blocks:
            for i in range(len(block) - window_size + 1):
                full_window = tuple((instr[2], tuple(instr[3])) for instr in block[i:i+window_size])
                pattern_freq[full_window] += 1
                pattern_operands[full_window].append(i)

    return pattern_freq, pattern_operands

def filter_and_sort_patterns(pattern_freq, min_frequency=10):
    sorted_patterns = sorted(
        pattern_freq.items(),
        key=lambda x: (len(x[0]), x[1]),
        reverse=True
    )

    filtered_patterns = {}

    for pattern, freq in sorted_patterns:
        if freq >= min_frequency:
            filtered_patterns[pattern] = freq

    return filtered_patterns

def print_findings(filename, candidates):
    for seq, freq in candidates.items():
        formatted_seq = ' -> '.join(
            f"{mnemonic} {' '.join(operands)}" if operands else mnemonic
            for mnemonic, operands in seq
        )
        print(f"{freq} occurrences: {formatted_seq}")
    print(f"[END] Finished processing log file: {filename}\n")

def split_bin(content):
    branch_mnemonics = {
        'b', 'bl', 'bx', 'blx',
        'beq', 'bne', 'bcs', 'bcc', 'bmi', 'bpl', 'bvs', 'bvc',
        'bhi', 'bls', 'bge', 'blt', 'bgt', 'ble', 'bal',
    }

    lines = content.splitlines()
    blocks = []
    current_block = []

    for line in lines:
        line = line.strip()
        if not line:
            continue
        if ':' not in line or line.endswith(':'):
            continue
        if 'file format' in line or 'Disassembly' in line:
            continue

        parts = line.split()
        if len(parts) < 3:
            continue

        addr_part = parts[0]
        if not addr_part.endswith(':'):
            continue
        addr = addr_part[:-1]
        encoding = parts[1]
        mnemonic = parts[2]

        if mnemonic in ('movw', 'movt', 'nop'):
            continue

        operands = parts[3:] if len(parts) > 3 else []

        cleaned_operands = []
        for op in operands:
            if op.startswith('@'):
                break
            cleaned_operands.append(op)

        instruction = (addr, encoding, mnemonic, cleaned_operands)
        current_block.append(instruction)

        is_branch = mnemonic in branch_mnemonics
        is_pop_pc = mnemonic == 'pop' and any('pc' in op for op in cleaned_operands)

        if is_branch or is_pop_pc:
            if current_block:
                blocks.append(current_block)
                current_block = []

    if current_block:
        blocks.append(current_block)

    return blocks


def process_binary_log():
    file_extension = '.bin.log'
    for filename in os.listdir(logs_dir):
        if filename.endswith(file_extension):
            content = load_log(os.path.join(logs_dir, filename))
            split_content = split_bin(content)
            pattern_freq, pattern_operands = find_patterns(split_content, max_window_size=10)
            candidates = filter_and_sort_patterns(pattern_freq, min_frequency=10)
            print_findings(filename, candidates)

def split_qemu(content):
    blocks = content.split("----------------")

    valid_blocks = []

    for block in blocks:
        lines = [line.strip() for line in block.splitlines() if line.strip()]
        if not lines:
            continue

        in_line = lines[0]
        if not in_line.startswith("IN:"):
            continue

        in_value = in_line[len("IN:"):].strip()
        if in_value != "":
            continue

        instructions = []
        for line in lines[1:]:
            parts = line.split()
            if len(parts) < 3 or parts[2] == 'movw' or parts[2] == 'movt':
                continue
            addr = parts[0]
            encoding = parts[1]
            mnemonic = parts[2]
            operands = parts[3:] if len(parts) > 3 else []
            instructions.append((addr, encoding, mnemonic, operands))

        if instructions:
            valid_blocks.append(instructions)

    return valid_blocks

def process_qemu_log():
    file_extension = '.log'
    for filename in os.listdir(logs_dir):
        if filename.endswith(file_extension) and not filename.endswith('.bin.log'):
            content = load_log(os.path.join(logs_dir, filename))
            split_content = split_qemu(content)
            pattern_freq, pattern_operands = find_patterns(split_content, max_window_size=10)
            candidates = filter_and_sort_patterns(pattern_freq, min_frequency=10)
            print_findings(filename, candidates)

def main():
    if len(sys.argv) > 1 and sys.argv[1] in ("--binary", "-b"):
        process_binary_log()
    else:
        process_qemu_log()

if __name__ == "__main__":
    main()