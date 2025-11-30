# Python script to analyze JITed code and identify common instruction patterns
# This script automatically reads all log files in the 'logs' directory and summarizes findings.

import os
from collections import defaultdict

logs_dir = 'logs'
file_extension = '.log'

def process_log(file_path):
    with open(file_path, "r", encoding="utf-8") as f:
        content = f.read()

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

def filter_and_sort_patterns(pattern_freq, min_frequency=3):
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

def main():
    for file in os.listdir(logs_dir):
        if not file.endswith(file_extension):
            print(f"{file} is not a log file.")
            continue

        print(f"[BEGIN] Processing log file: {file}")
        file_path = os.path.join(logs_dir, file)
        blocks = process_log(file_path)

        pattern_freq, pattern_operands = find_patterns(blocks, max_window_size=10)
        candidates = filter_and_sort_patterns(pattern_freq, min_frequency=10)

        for seq, freq in candidates.items():
            formatted_seq = ' -> '.join(
                f"{mnemonic} {' '.join(operands)}" if operands else mnemonic
                for mnemonic, operands in seq
            )
            print(f"{freq} occurrences: {formatted_seq}")

        print(f"[END] Finished processing log file: {file}\n")

if __name__ == "__main__":
    main()