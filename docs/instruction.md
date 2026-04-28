# Custom Instruction Proposal

## wasmbchk - WASM Bounds Check

This instruction performs a bounds check for linear memory accesses in WebAssembly.

### Motivation

In WebAssembly, accessing memory at `memory[dynamic_offset + static_offset]` of `size` bytes is valid if and only if:

```
dynamic_offset + static_offset + size <= memory_size
```

On a 32-bit architecture, 2 things can go wrong:

- `dynamic_offset + (static_offset + size) > 2^32`, causing an integer overflow
- The sum fits in 32 bits, but it exceeds the memory size

Both cases must trigger a trap.

### Specification

Semantic: `wasmbchk Rd, Rlimit, #imm`

Operands:

| Operand  | Type                  | Description                                                    |
|----------|-----------------------|----------------------------------------------------------------|
| `Rd`     | Register (read/write) | The dynamic offset. Updated to `Rd + imm` if the check passes. |
| `Rlimit` | Register (read-only)  | The memory size.                                               |
| `imm`    | Immediate (read-only) | `static_offset + size`                                         |

### Pseudocode:

```
// Compute the sum of the dynamic offset and the static offset + size via a 33 bit addition
// If the sum overflows, then the check fails as the effective address wrapped past 2^32
(tmp, overflow) = Rd + ZeroExtend(imm)

if overflow == 1 || tmp > Rlimit :
    CPSR.C = 1
else :
    CPSR.C = 0
    Rd = tmp
```

### Post conditions

- C flag = 1 if the check fails (overflow or exceeds limit). `Rd` is unchanged.
- C flag = 0 if the check passes. `Rd` is updated to `Rd + imm`.
- N, Z, V flags remain in-tact.
- The temp register used for the addition is clobbered.

The immediate instruction after `wasmbchk` is expected to be a conditional branch that checks the Carry flag:

```
wasmbchk Rd, Rlimit, #imm
bcs trap_handler
```

## wasmld / wasmstr - WASM Memory Load/Store

These instructions perform a memory load/store operation in WebAssembly.

### Motivation

In WebAssembly, a linear memory access consists of two separate steps:

1. Bounds validation of the effective address (`wasmbchk`)
2. The actual memory operation (load or store)

While `wasmbchk` ensures that `dynamic_offset + static_offset + size <= memory_size`, it does not perform the memory access itself.

After a successful bounds check, the JIT still emits additional instructions to:
- Load the linear memory base pointer from the current instance
- Add the checked offset to that base
- Execute the final load/store

### wasmld Specification

Semantic: `wasmld Rd, Rbase, Roff, #mode`

Operands:

| Operand  | Type                  | Description |
|----------|-----------------------|-------------|
| `Rd`     | Register (write)      | Destination register for the loaded value. |
| `Rbase`  | Register (read-only)  | Base pointer to linear memory (`memory->buffer`). |
| `Roff`   | Register (read-only)  | Checked dynamic offset (typically produced by `wasmbchk`). |
| `mode`   | Immediate (read-only) | Encodes the load width and signedness. |

`mode` encoding:

| mode | Meaning |
|------|---------|
| `0`  | `u8` load (zero-extend) |
| `1`  | `s8` load (sign-extend) |
| `2`  | `u16` load (zero-extend) |
| `3`  | `s16` load (sign-extend) |
| `4`  | `u32` load |

Pseudocode:

```
addr = Rbase + Roff

switch mode:
  case 0: Rd = ZeroExtend8(Load8(addr))
  case 1: Rd = SignExtend8(Load8(addr))
  case 2: Rd = ZeroExtend16(Load16(addr))
  case 3: Rd = SignExtend16(Load16(addr))
  case 4: Rd = Load32(addr)
  default: trap(SIGILL)
```

Post conditions:

- `Rd` is updated with the loaded value.
- CPSR flags are unchanged.

### wasmstr Specification

Semantic: `wasmstr Rs, Rbase, Roff, #mode`

Operands:

| Operand  | Type                  | Description |
|----------|-----------------------|-------------|
| `Rs`     | Register (read-only)  | Source register for the value to store. |
| `Rbase`  | Register (read-only)  | Base pointer to linear memory (`memory->buffer`). |
| `Roff`   | Register (read-only)  | Checked dynamic offset (typically produced by `wasmbchk`). |
| `mode`   | Immediate (read-only) | Encodes the store width. |

`mode` encoding:

| mode | Meaning |
|------|---------|
| `0`  | `store8` (low 8 bits of `Rs`) |
| `2`  | `store16` (low 16 bits of `Rs`) |
| `4`  | `store32` (low 32 bits of `Rs`) |

Pseudocode:

```
addr = Rbase + Roff

switch mode:
  case 0: Store8(addr, Trunc8(Rs))
  case 2: Store16(addr, Trunc16(Rs))
  case 4: Store32(addr, Trunc32(Rs))
  default: trap(SIGILL)
```

Post conditions:

- Linear memory is updated at the effective address.
- CPSR flags are unchanged.

### Expected JIT Pattern

The pair is designed to follow `wasmbchk` directly:

```
wasmbchk Roff, Rlimit, #imm
bcs trap_handler
wasmld  Rd, Rbase, Roff, #mode
```

or

```
wasmbchk Roff, Rlimit, #imm
bcs trap_handler
wasmstr Rs, Rbase, Roff, #mode
```
