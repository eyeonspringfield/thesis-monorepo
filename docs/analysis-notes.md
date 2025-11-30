# Notes

These are some explanations and additional thoughts of some of the longer and frequent patterns observed during analysis, followed by a sample output of the full analysis

---

`mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000 -> cmp sb, ip -> bhi #BRANCH_TARGET`:

- `MVN` (move not) to intra procedure scratch register `ip` with 0xFE000000.

- `MVN` executes a bitwise logical NOT on the value, so `ip` gets 0x01FFFFFF stored.

- `BIC` (bit clear) intra procedure scratch with 0x00FE0000. `ip = 0x01FFFFFF & ~(0x00FE0000) = 0x01FFFFFF & 0xFF01FFFF = 0x0101FFFF`

- `CMP` static base to intra procedure.

- `BHI` (branch if unsigned higher) to `BRANCH_TARGET`.

This could be a bounds check, a 32-bit constant is constructed via `mvn ip #0xfe000000` then `bic ip, ip, #0xfe0000`. The register `sb` (`r9`) could be holding a memory-limit or bounds-check value. The following `cmp sb, ip` and `bhi #BRANCH_TARGET` pattern performs an unsigned bounds check: if `sb` exceeds the constructed limit, branch to `BRANCH_TARGET`.

`BRANCH_TARGET` could be a trap handler implemented by Walrus, as traps cannot be handled within WASM code. See [WASM Concepts](https://www.w3.org/TR/wasm-core-1/#concepts%E2%91%A0).

---

```
[BEGIN] Processing log file: helloworld-2025-11-30-21:13:41.log
19 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4 -> str r0, [sp]
29 occurrences: mov r1, r4 -> ldr r2, [sp]
27 occurrences: sub sp, sp, #4 -> str r0, [sp]
19 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4
17 occurrences: add sp, sp, #4 -> pop {pc}
37 occurrences: cmp r0, #0
33 occurrences: str r0, [sp]
32 occurrences: ldr r1, [r5, #0x30]
30 occurrences: blx ip
29 occurrences: mov r1, r4
29 occurrences: ldr r2, [sp]
28 occurrences: sub sp, sp, #4
26 occurrences: add sp, sp, #4
22 occurrences: cmp r2, ip
19 occurrences: str lr, [sp, #-4]!
17 occurrences: pop {pc}
17 occurrences: cmp r3, ip
15 occurrences: ldr r0, [r1, r2]
14 occurrences: ldr r2, [r5, #0x30]
13 occurrences: bhs #0x408529f8
13 occurrences: bhi #0x408529f8
12 occurrences: str r0, [r4]
10 occurrences: mov lr, #0
10 occurrences: bhi #0x40854a4c
[END] Finished processing log file: helloworld-2025-11-30-21:13:41.log

[BEGIN] Processing log file: polynomial-2025-11-30-21:13:41.log
12 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000 -> cmp sb, ip -> bhi #0x4085379c
19 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4 -> str r0, [sp]
12 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000 -> cmp sb, ip
12 occurrences: bic ip, ip, #0xfe0000 -> cmp sb, ip -> bhi #0x4085379c
42 occurrences: mov r1, r4 -> ldr r2, [sp]
31 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000
29 occurrences: sub sp, sp, #4 -> str r0, [sp]
19 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4
17 occurrences: add sp, sp, #4 -> pop {pc}
15 occurrences: mov r2, r6 -> ldr r1, [r5, #0x30]
12 occurrences: bic ip, ip, #0xfe0000 -> cmp sb, ip
12 occurrences: cmp sb, ip -> bhi #0x4085379c
10 occurrences: cmp r0, #0 -> bne #0x40856770
52 occurrences: cmp r0, #0
50 occurrences: ldr r1, [r5, #0x30]
46 occurrences: blx ip
43 occurrences: mov r1, r4
43 occurrences: ldr r2, [sp]
39 occurrences: str r0, [sp]
35 occurrences: cmp r2, ip
32 occurrences: cmp r3, ip
31 occurrences: mvn ip, #0xfe000000
31 occurrences: bic ip, ip, #0xfe0000
30 occurrences: sub sp, sp, #4
28 occurrences: add sp, sp, #4
23 occurrences: ldr r2, [r5, #0x30]
20 occurrences: ldr r0, [r1, r2]
19 occurrences: str lr, [sp, #-4]!
18 occurrences: bhi #0x40856764
17 occurrences: pop {pc}
17 occurrences: mov r2, r6
17 occurrences: cmp sb, ip
16 occurrences: bhi #0x4085379c
15 occurrences: bhs #0x40852510
15 occurrences: bhi #0x40852510
15 occurrences: ldr r3, [r5, #0x30]
14 occurrences: ldr r0, [r5, #0x30]
13 occurrences: ldr r8, [r5, #0x30]
13 occurrences: bhs #0x40852de0
13 occurrences: bhi #0x40852de0
12 occurrences: mov lr, #0
12 occurrences: str r0, [r4]
11 occurrences: bhs #0x40852244
11 occurrences: bhs #0x40856764
10 occurrences: ldr r0, [r4]
10 occurrences: adds r2, r2, #0x10
10 occurrences: bhi #0x40852244
10 occurrences: cmp r6, ip
10 occurrences: bhi #0x40854e08
10 occurrences: bne #0x40856770
10 occurrences: mov r3, r0
[END] Finished processing log file: polynomial-2025-11-30-21:13:41.log

[BEGIN] Processing log file: square-2025-11-30-21:13:42.log
10 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000 -> cmp sb, ip -> bhi #0x40853538
20 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4 -> str r0, [sp]
10 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000 -> cmp sb, ip
10 occurrences: bic ip, ip, #0xfe0000 -> cmp sb, ip -> bhi #0x40853538
40 occurrences: mov r1, r4 -> ldr r2, [sp]
30 occurrences: sub sp, sp, #4 -> str r0, [sp]
27 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000
20 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4
18 occurrences: add sp, sp, #4 -> pop {pc}
10 occurrences: cmp r0, #0 -> bne #0x40856538
10 occurrences: bic ip, ip, #0xfe0000 -> cmp sb, ip
10 occurrences: cmp sb, ip -> bhi #0x40853538
49 occurrences: cmp r0, #0
43 occurrences: blx ip
42 occurrences: ldr r1, [r5, #0x30]
40 occurrences: mov r1, r4
40 occurrences: ldr r2, [sp]
38 occurrences: str r0, [sp]
31 occurrences: sub sp, sp, #4
29 occurrences: add sp, sp, #4
27 occurrences: cmp r2, ip
27 occurrences: mvn ip, #0xfe000000
27 occurrences: bic ip, ip, #0xfe0000
25 occurrences: cmp r3, ip
20 occurrences: str lr, [sp, #-4]!
18 occurrences: pop {pc}
17 occurrences: ldr r2, [r5, #0x30]
17 occurrences: bhi #0x4085652c
16 occurrences: ldr r0, [r1, r2]
15 occurrences: cmp sb, ip
13 occurrences: ldr r0, [r5, #0x30]
13 occurrences: bhs #0x40852b80
13 occurrences: bhi #0x40852b80
12 occurrences: mov lr, #0
12 occurrences: str r0, [r4]
12 occurrences: bhi #0x40853538
11 occurrences: ldr r8, [r5, #0x30]
10 occurrences: ldr r0, [r4]
10 occurrences: bhi #0x40854ba8
10 occurrences: bhs #0x4085652c
10 occurrences: ldr r3, [r5, #0x30]
10 occurrences: bne #0x40856538
10 occurrences: mov r3, r0
[END] Finished processing log file: square-2025-11-30-21:13:42.log

[BEGIN] Processing log file: dispatcher-2025-11-30-21:13:40.log
12 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4 -> str r0, [sp] -> mov lr, r5
11 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000 -> cmp sb, ip -> bhi #0x40854480
25 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4 -> str r0, [sp]
12 occurrences: sub sp, sp, #4 -> str r0, [sp] -> mov lr, r5
12 occurrences: push {r6, lr} -> sub sp, sp, #8 -> str r0, [sp]
12 occurrences: str r0, [sp] -> ldr r0, [r4] -> ldr r1, [r4, #4]
11 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000 -> cmp sb, ip
11 occurrences: bic ip, ip, #0xfe0000 -> cmp sb, ip -> bhi #0x40854480
10 occurrences: sub sp, sp, #8 -> str r0, [sp] -> ldr r0, [r4]
44 occurrences: mov r1, r4 -> ldr r2, [sp]
39 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000
37 occurrences: sub sp, sp, #4 -> str r0, [sp]
30 occurrences: mov r2, r6 -> ldr r1, [r5, #0x30]
25 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4
24 occurrences: cmp r2, ip -> bhi #0x408528e4
23 occurrences: add sp, sp, #4 -> pop {pc}
17 occurrences: mov r3, r2 -> ldr r1, [r5, #0x30]
16 occurrences: str r0, [sp] -> ldr r0, [r4]
14 occurrences: sub sp, sp, #8 -> str r0, [sp]
13 occurrences: mov r3, r6 -> ldr r2, [r5, #0x30]
12 occurrences: str r0, [sp] -> mov lr, r5
12 occurrences: push {r6, lr} -> sub sp, sp, #8
12 occurrences: ldr r0, [r4] -> ldr r1, [r4, #4]
11 occurrences: cmp r3, ip -> bhi #0x408528e4
11 occurrences: add sp, sp, #8 -> pop {r6, pc}
11 occurrences: cmp r0, #0 -> bne #0x408574b4
11 occurrences: bic ip, ip, #0xfe0000 -> cmp sb, ip
11 occurrences: cmp sb, ip -> bhi #0x40854480
10 occurrences: cmp r1, ip -> bhi #0x408528e4
83 occurrences: ldr r1, [r5, #0x30]
62 occurrences: cmp r3, ip
53 occurrences: cmp r0, #0
52 occurrences: str r0, [sp]
52 occurrences: bhi #0x408528e4
52 occurrences: cmp r2, ip
48 occurrences: blx ip
47 occurrences: bhs #0x408528e4
44 occurrences: mov r1, r4
44 occurrences: ldr r2, [sp]
39 occurrences: mvn ip, #0xfe000000
39 occurrences: bic ip, ip, #0xfe0000
38 occurrences: sub sp, sp, #4
36 occurrences: add sp, sp, #4
33 occurrences: mov r2, r6
31 occurrences: ldr r3, [r5, #0x30]
29 occurrences: ldr r2, [r5, #0x30]
29 occurrences: ldr r0, [r1, r2]
28 occurrences: ldr r0, [r5, #0x30]
25 occurrences: str lr, [sp, #-4]!
25 occurrences: mov r3, r2
23 occurrences: pop {pc}
22 occurrences: bhi #0x408574a8
18 occurrences: mov lr, #0
18 occurrences: str r0, [r4]
18 occurrences: cmp r6, ip
17 occurrences: ldr r0, [r4]
17 occurrences: cmp r1, ip
16 occurrences: cmp sb, ip
15 occurrences: bhs #0x408574a8
15 occurrences: bhi #0x40854480
14 occurrences: mov r3, r6
14 occurrences: sub sp, sp, #8
14 occurrences: add sp, sp, #8
13 occurrences: ldr lr, [r5, #0x3c]
13 occurrences: cmp r7, ip
13 occurrences: ldr r8, [r5, #0x30]
13 occurrences: bhs #0x40853ad0
13 occurrences: bhi #0x40853ad0
12 occurrences: mov lr, r5
12 occurrences: ldr r1, [r2, r3]
12 occurrences: str r0, [r1, r2]
12 occurrences: push {r6, lr}
12 occurrences: mov r3, r0
12 occurrences: ldr r1, [r4, #4]
11 occurrences: pop {r6, pc}
11 occurrences: mov r6, r2
11 occurrences: bhs #0x408530fc
11 occurrences: bhi #0x408530fc
11 occurrences: ldr r0, [r1, r3]
11 occurrences: bne #0x408574b4
10 occurrences: adds r3, r3, #0xc
10 occurrences: adds r3, r3, #8
10 occurrences: bhi #0x40855b20
10 occurrences: ldr r7, [r5, #0x30]
[END] Finished processing log file: dispatcher-2025-11-30-21:13:40.log

[BEGIN] Processing log file: factorial-2025-11-30-21:13:40.log
12 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000 -> cmp sb, ip -> bhi #0x408536a4
19 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4 -> str r0, [sp]
12 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000 -> cmp sb, ip
12 occurrences: bic ip, ip, #0xfe0000 -> cmp sb, ip -> bhi #0x408536a4
41 occurrences: mov r1, r4 -> ldr r2, [sp]
30 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000
28 occurrences: sub sp, sp, #4 -> str r0, [sp]
19 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4
17 occurrences: add sp, sp, #4 -> pop {pc}
12 occurrences: mov r3, r6 -> ldr r2, [r5, #0x30]
12 occurrences: bic ip, ip, #0xfe0000 -> cmp sb, ip
12 occurrences: cmp sb, ip -> bhi #0x408536a4
10 occurrences: cmp r0, #0 -> bne #0x4085669c
50 occurrences: cmp r0, #0
45 occurrences: blx ip
41 occurrences: mov r1, r4
41 occurrences: ldr r2, [sp]
41 occurrences: ldr r1, [r5, #0x30]
38 occurrences: str r0, [sp]
30 occurrences: mvn ip, #0xfe000000
30 occurrences: bic ip, ip, #0xfe0000
29 occurrences: sub sp, sp, #4
28 occurrences: cmp r3, ip
27 occurrences: add sp, sp, #4
25 occurrences: cmp r2, ip
21 occurrences: ldr r2, [r5, #0x30]
19 occurrences: str lr, [sp, #-4]!
17 occurrences: pop {pc}
17 occurrences: bhi #0x40856690
17 occurrences: cmp sb, ip
16 occurrences: ldr r0, [r5, #0x30]
16 occurrences: bhi #0x408536a4
15 occurrences: ldr r0, [r1, r2]
13 occurrences: mov lr, #0
13 occurrences: ldr r8, [r5, #0x30]
13 occurrences: bhs #0x40852cd8
13 occurrences: bhi #0x40852cd8
12 occurrences: str r0, [r4]
12 occurrences: cmp r1, ip
12 occurrences: mov r3, r6
10 occurrences: ldr r0, [r4]
10 occurrences: sub sp, sp, #8
10 occurrences: bhi #0x40854d04
10 occurrences: bhs #0x40856690
10 occurrences: ldr r3, [r5, #0x30]
10 occurrences: bne #0x4085669c
10 occurrences: mov r3, r0
[END] Finished processing log file: factorial-2025-11-30-21:13:40.log

[BEGIN] Processing log file: promote-2025-11-30-21:13:42.log
12 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000 -> cmp sb, ip -> bhi #0x40854510
21 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4 -> str r0, [sp]
12 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000 -> cmp sb, ip
12 occurrences: bic ip, ip, #0xfe0000 -> cmp sb, ip -> bhi #0x40854510
61 occurrences: mov r1, r4 -> ldr r2, [sp]
35 occurrences: sub sp, sp, #4 -> str r0, [sp]
29 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000
24 occurrences: mov r1, r6 -> ldr r0, [r5, #0x30]
24 occurrences: mov r2, r6 -> ldr r1, [r5, #0x30]
22 occurrences: mov r3, r6 -> ldr r2, [r5, #0x30]
21 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4
19 occurrences: add sp, sp, #4 -> pop {pc}
17 occurrences: cmp r1, ip -> bhi #0x40852df0
12 occurrences: str r0, [sp] -> ldr r0, [r4]
12 occurrences: ldr lr, [ip] -> ldr ip, [ip, #4]
12 occurrences: bic ip, ip, #0xfe0000 -> cmp sb, ip
12 occurrences: cmp sb, ip -> bhi #0x40854510
10 occurrences: sub sp, sp, #8 -> str r0, [sp]
10 occurrences: cmp r0, #0 -> bne #0x4085751c
10 occurrences: cmp r0, #0 -> bne #0x4085a22c
81 occurrences: cmp r0, #0
69 occurrences: blx ip
63 occurrences: ldr r1, [r5, #0x30]
61 occurrences: mov r1, r4
61 occurrences: ldr r2, [sp]
50 occurrences: cmp r3, ip
50 occurrences: cmp r2, ip
48 occurrences: str r0, [sp]
47 occurrences: ldr r2, [r5, #0x30]
40 occurrences: ldr r0, [r5, #0x30]
37 occurrences: sub sp, sp, #4
36 occurrences: bhi #0x40852df0
35 occurrences: add sp, sp, #4
35 occurrences: bhs #0x40852df0
31 occurrences: cmp r1, ip
29 occurrences: mvn ip, #0xfe000000
29 occurrences: bic ip, ip, #0xfe0000
27 occurrences: mov r2, r6
27 occurrences: ldr r0, [r1, r2]
24 occurrences: mov lr, #0
24 occurrences: mov r1, r6
22 occurrences: mov r3, r6
21 occurrences: str lr, [sp, #-4]!
19 occurrences: pop {pc}
18 occurrences: cmp sb, ip
18 occurrences: bhi #0x40857510
16 occurrences: cmp ip, #0
16 occurrences: bhs #0x408527c0
16 occurrences: bhi #0x408527c0
16 occurrences: bhi #0x40854510
15 occurrences: ldr r3, [r5, #0x30]
15 occurrences: ldr r8, [r5, #0x30]
14 occurrences: add ip, r0, r1
14 occurrences: mov r1, r0
14 occurrences: bhi #0x4085a220
13 occurrences: str r0, [r4]
13 occurrences: ldr r0, [r4]
13 occurrences: bhi #0x408523d0
13 occurrences: cmp r6, ip
13 occurrences: ldr ip, [r4, #0x14]
13 occurrences: mov r3, r0
13 occurrences: bhs #0x40853b9c
13 occurrences: bhi #0x40853b9c
12 occurrences: ldr lr, [r5, #0x3c]
12 occurrences: add ip, r2, r3
12 occurrences: ldr r1, [r2, r3]
12 occurrences: ldr lr, [ip]
12 occurrences: ldr ip, [ip, #4]
12 occurrences: cmp r8, ip
12 occurrences: bhi #0x40857fec
11 occurrences: sub sp, sp, #8
11 occurrences: str r0, [r1, r2]
11 occurrences: bhs #0x40857510
11 occurrences: ldr ip, [r4, #0x1c]
11 occurrences: bne #0x4085751c
10 occurrences: bhs #0x408523d0
10 occurrences: add sp, sp, #8
10 occurrences: mov r2, r0
10 occurrences: mov r1, #0
10 occurrences: mov r0, #0
10 occurrences: bhi #0x40855ba0
10 occurrences: mov r6, r0
10 occurrences: bne #0x4085a22c
[END] Finished processing log file: promote-2025-11-30-21:13:42.log

[BEGIN] Processing log file: memwalk-2025-11-30-21:13:41.log
10 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000 -> cmp r2, ip -> bhi #0x40852900
19 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4 -> str r0, [sp]
14 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000 -> cmp r2, ip
10 occurrences: bic ip, ip, #0xfe0000 -> cmp r2, ip -> bhi #0x40852900
41 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000
40 occurrences: mov r1, r4 -> ldr r2, [sp]
37 occurrences: mov r2, r6 -> ldr r1, [r5, #0x30]
32 occurrences: cmp r2, ip -> bhi #0x40852900
29 occurrences: sub sp, sp, #4 -> str r0, [sp]
20 occurrences: mov r3, r6 -> ldr r2, [r5, #0x30]
19 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4
17 occurrences: add sp, sp, #4 -> pop {pc}
15 occurrences: cmp r3, ip -> bhi #0x40852900
14 occurrences: bic ip, ip, #0xfe0000 -> cmp r2, ip
10 occurrences: cmp r0, #0 -> bne #0x40856cc8
74 occurrences: ldr r1, [r5, #0x30]
58 occurrences: cmp r2, ip
55 occurrences: bhs #0x40852900
54 occurrences: bhi #0x40852900
50 occurrences: cmp r0, #0
41 occurrences: blx ip
41 occurrences: cmp r3, ip
41 occurrences: mvn ip, #0xfe000000
41 occurrences: bic ip, ip, #0xfe0000
40 occurrences: mov r1, r4
40 occurrences: ldr r2, [sp]
40 occurrences: mov r2, r6
38 occurrences: str r0, [sp]
36 occurrences: ldr r2, [r5, #0x30]
30 occurrences: sub sp, sp, #4
28 occurrences: add sp, sp, #4
27 occurrences: ldr r0, [r1, r2]
22 occurrences: ldr r1, [r2, r3]
20 occurrences: mov r3, r6
20 occurrences: bhi #0x40856cbc
19 occurrences: str lr, [sp, #-4]!
17 occurrences: pop {pc}
16 occurrences: mov lr, #0
14 occurrences: ldr r0, [r5, #0x30]
14 occurrences: cmp sb, ip
13 occurrences: cmp r1, ip
13 occurrences: mov r3, r0
13 occurrences: ldr r3, [r5, #0x30]
13 occurrences: str r0, [r1, r2]
13 occurrences: bhs #0x40856cbc
13 occurrences: bhs #0x40853418
13 occurrences: bhi #0x40853418
12 occurrences: str r0, [r4]
11 occurrences: bhi #0x40853cdc
10 occurrences: ldr r0, [r4]
10 occurrences: mov r6, r0
10 occurrences: bhi #0x40855420
10 occurrences: bne #0x40856cc8
10 occurrences: ldr r8, [r5, #0x30]
[END] Finished processing log file: memwalk-2025-11-30-21:13:41.log

[BEGIN] Processing log file: guarded_sum-2025-11-30-21:13:41.log
20 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4 -> str r0, [sp]
50 occurrences: mov r1, r4 -> ldr r2, [sp]
34 occurrences: sub sp, sp, #4 -> str r0, [sp]
27 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000
20 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4
20 occurrences: mov r2, r6 -> ldr r1, [r5, #0x30]
18 occurrences: add sp, sp, #4 -> pop {pc}
14 occurrences: mov r3, r6 -> ldr r2, [r5, #0x30]
12 occurrences: str r0, [sp] -> ldr r0, [r4]
10 occurrences: cmp r0, #0 -> bne #0x40857464
66 occurrences: ldr r1, [r5, #0x30]
62 occurrences: cmp r0, #0
56 occurrences: blx ip
51 occurrences: cmp r2, ip
50 occurrences: mov r1, r4
50 occurrences: ldr r2, [sp]
45 occurrences: str r0, [sp]
40 occurrences: cmp r3, ip
38 occurrences: ldr r2, [r5, #0x30]
35 occurrences: sub sp, sp, #4
33 occurrences: add sp, sp, #4
30 occurrences: ldr r0, [r1, r2]
28 occurrences: bhi #0x40852d08
27 occurrences: mvn ip, #0xfe000000
27 occurrences: bic ip, ip, #0xfe0000
25 occurrences: bhs #0x40852d08
24 occurrences: ldr r0, [r5, #0x30]
23 occurrences: mov r2, r6
21 occurrences: mov lr, #0
20 occurrences: str lr, [sp, #-4]!
19 occurrences: cmp r1, ip
18 occurrences: pop {pc}
17 occurrences: bhi #0x40857458
16 occurrences: cmp sb, ip
16 occurrences: bhi #0x408527f0
15 occurrences: ldr r1, [r2, r3]
14 occurrences: mov r3, r6
13 occurrences: str r0, [r4]
13 occurrences: ldr r0, [r4]
13 occurrences: bhs #0x40852418
13 occurrences: bhi #0x40852418
13 occurrences: ldr r3, [r5, #0x30]
13 occurrences: bhi #0x40854430
13 occurrences: bhs #0x40853ae0
13 occurrences: bhi #0x40853ae0
12 occurrences: ldr r8, [r5, #0x30]
12 occurrences: cmp r8, ip
11 occurrences: ldr lr, [r5, #0x3c]
10 occurrences: sub sp, sp, #8
10 occurrences: mov r3, r7
10 occurrences: str r0, [r1, r2]
10 occurrences: bhi #0x40855ad4
10 occurrences: bhs #0x40857458
10 occurrences: bne #0x40857464
10 occurrences: mov r3, r0
[END] Finished processing log file: guarded_sum-2025-11-30-21:13:41.log

```
