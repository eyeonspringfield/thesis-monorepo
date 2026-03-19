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
