# Python script to analyze JITed code and identify common instruction patterns
# Pass the "--binary" or "-b" flag to analyze the .bin.log files instead of the .log files.

import os
import sys
from collections import defaultdict
import re

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

def metrics_dir():
    candidate = os.path.join(logs_dir, 'metrics')
    return candidate if os.path.isdir(candidate) else logs_dir


def parse_duration_ns(time_path):
    try:
        with open(time_path, "r", encoding="utf-8", errors="replace") as f:
            for line in f:
                if "duration_time" not in line:
                    continue
                parts = line.strip().split()
                if not parts:
                    continue
                value = parts[0].replace(",", "")
                try:
                    return int(value)
                except ValueError:
                    return None
    except FileNotFoundError:
        return None
    return None


def parse_emu_metrics(stderr_path):
    metrics = {}
    try:
        with open(stderr_path, "r", encoding="utf-8", errors="replace") as f:
            for line in f:
                line = line.strip()
                if not line.startswith("EMU_METRIC "):
                    continue
                payload = line[len("EMU_METRIC "):]
                if "=" not in payload:
                    continue
                key, value = payload.split("=", 1)
                key = key.strip()
                value = value.strip()
                try:
                    metrics[key] = int(value)
                except ValueError:
                    continue
    except FileNotFoundError:
        return metrics
    return metrics


def discover_runs(metrics_dir):
    runs = []
    ts_re = re.compile(r"^(?P<program>.+)-(?P<ts>\d{4}-\d{2}-\d{2}-\d{2}:\d{2}:\d{2})$")
    for filename in os.listdir(metrics_dir):
        if not filename.endswith(".time"):
            continue
        stem = filename[:-5]
        match = ts_re.match(stem)
        if not match:
            continue
        program = match.group("program")
        timestamp = match.group("ts")
        time_path = os.path.join(metrics_dir, filename)
        mode_path = os.path.join(metrics_dir, f"{stem}.mode")
        stderr_path = os.path.join(metrics_dir, f"{stem}.stderr")
        mode = "unknown"
        if os.path.exists(mode_path):
            with open(mode_path, "r", encoding="utf-8", errors="replace") as f:
                mode = f.read().strip().lower() or "unknown"
        time_ns = parse_duration_ns(time_path)
        metrics = parse_emu_metrics(stderr_path)
        runs.append({
            "program": program,
            "timestamp": timestamp,
            "mode": mode,
            "stem": stem,
            "time_ns": time_ns,
            "metrics": metrics,
        })
    return runs

def print_metrics():
    runs = discover_runs(metrics_dir())
    if not runs:
        print(f"No .time artifacts found in {metrics_dir}")
        return

    selected = {}
    for run in runs:
        key = (run["program"], run["mode"])
        prev = selected.get(key)
        if prev is None or run["timestamp"] > prev["timestamp"]:
            selected[key] = run

    programs = sorted({run["program"] for run in runs})
    header = (
        "program,baseline_time_ns,emu_time_ns,emu_overhead_ns,"
        "wasmbchk_count,wasmld_count,wasmstr_count,total_count,baseline_stem,emu_stem"
    )
    print(header)

    for program in programs:
        baseline = selected.get((program, "baseline"))
        emu = selected.get((program, "emu"))
        baseline_time = baseline["time_ns"] if baseline else None
        emu_time = emu["time_ns"] if emu else None
        overhead = None
        if baseline_time is not None and emu_time is not None:
            overhead = emu_time - baseline_time

        metrics = emu["metrics"] if emu else {}
        wasmbchk = metrics.get("wasmbchk_count", 0)
        wasmld = metrics.get("wasmld_count", 0)
        wasmstr = metrics.get("wasmstr_count", 0)
        total = metrics.get("total_count", wasmbchk + wasmld + wasmstr)

        print(
            f"{program},{baseline_time},{emu_time},{overhead},"
            f"{wasmbchk},{wasmld},{wasmstr},{total},"
            f"{baseline['stem'] if baseline else ''},{emu['stem'] if emu else ''}"
        )


def main():
    if len(sys.argv) > 1 and sys.argv[1] in ("--binary", "-b"):
        process_binary_log()
    elif len(sys.argv) > 1 and sys.argv[1] in ("--metrics", "-m"):
        print_metrics()
    else:
        process_qemu_log()

if __name__ == "__main__":
    main()
