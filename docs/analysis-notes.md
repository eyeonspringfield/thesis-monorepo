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
12 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000 -> cmp sb, ip -> bhi #0x408537c0
22 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4 -> str r0, [sp]
12 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000 -> cmp sb, ip
12 occurrences: bic ip, ip, #0xfe0000 -> cmp sb, ip -> bhi #0x408537c0
44 occurrences: mov r1, r4 -> ldr r2, [sp]
32 occurrences: sub sp, sp, #4 -> str r0, [sp]
31 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000
22 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4
20 occurrences: add sp, sp, #4 -> pop {pc}
15 occurrences: mov r2, r6 -> ldr r1, [r5, #0x30]
12 occurrences: bic ip, ip, #0xfe0000 -> cmp sb, ip
12 occurrences: cmp sb, ip -> bhi #0x408537c0
10 occurrences: cmp r0, #0 -> bne #0x408567b0
54 occurrences: cmp r0, #0
49 occurrences: ldr r1, [r5, #0x30]
46 occurrences: blx ip
44 occurrences: mov r1, r4
44 occurrences: ldr r2, [sp]
42 occurrences: str r0, [sp]
34 occurrences: cmp r2, ip
33 occurrences: sub sp, sp, #4
33 occurrences: cmp r3, ip
31 occurrences: add sp, sp, #4
31 occurrences: mvn ip, #0xfe000000
31 occurrences: bic ip, ip, #0xfe0000
23 occurrences: ldr r2, [r5, #0x30]
22 occurrences: str lr, [sp, #-4]!
20 occurrences: pop {pc}
20 occurrences: ldr r0, [r1, r2]
18 occurrences: mov r2, r6
18 occurrences: bhi #0x408567a4
17 occurrences: cmp sb, ip
16 occurrences: bhi #0x408537c0
15 occurrences: bhs #0x40852528
15 occurrences: bhi #0x40852528
15 occurrences: ldr r3, [r5, #0x30]
14 occurrences: str r0, [r4]
14 occurrences: ldr r0, [r5, #0x30]
13 occurrences: ldr r8, [r5, #0x30]
13 occurrences: bhs #0x40852df4
13 occurrences: bhi #0x40852df4
12 occurrences: mov lr, #0
11 occurrences: bhs #0x40852260
11 occurrences: bhs #0x408567a4
10 occurrences: ldr r0, [r4]
10 occurrences: adds r2, r2, #0x10
10 occurrences: bhi #0x40852260
10 occurrences: cmp r6, ip
10 occurrences: bhi #0x40854e30
10 occurrences: bne #0x408567b0
[END] Finished processing log file: polynomial-2026-04-28-21:54:02.log

10 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000 -> cmp sb, ip -> bhi #0x4085355c
23 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4 -> str r0, [sp]
10 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000 -> cmp sb, ip
10 occurrences: bic ip, ip, #0xfe0000 -> cmp sb, ip -> bhi #0x4085355c
41 occurrences: mov r1, r4 -> ldr r2, [sp]
33 occurrences: sub sp, sp, #4 -> str r0, [sp]
27 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000
23 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4
21 occurrences: add sp, sp, #4 -> pop {pc}
10 occurrences: cmp r0, #0 -> bne #0x40856568
10 occurrences: bic ip, ip, #0xfe0000 -> cmp sb, ip
10 occurrences: cmp sb, ip -> bhi #0x4085355c
51 occurrences: cmp r0, #0
43 occurrences: blx ip
41 occurrences: str r0, [sp]
41 occurrences: mov r1, r4
41 occurrences: ldr r2, [sp]
41 occurrences: ldr r1, [r5, #0x30]
34 occurrences: sub sp, sp, #4
32 occurrences: add sp, sp, #4
27 occurrences: mvn ip, #0xfe000000
27 occurrences: bic ip, ip, #0xfe0000
26 occurrences: cmp r2, ip
26 occurrences: cmp r3, ip
23 occurrences: str lr, [sp, #-4]!
21 occurrences: pop {pc}
17 occurrences: ldr r2, [r5, #0x30]
17 occurrences: bhi #0x4085655c
16 occurrences: ldr r0, [r1, r2]
15 occurrences: cmp sb, ip
14 occurrences: str r0, [r4]
13 occurrences: ldr r0, [r5, #0x30]
13 occurrences: bhs #0x40852b94
13 occurrences: bhi #0x40852b94
12 occurrences: mov lr, #0
12 occurrences: bhi #0x4085355c
11 occurrences: ldr r8, [r5, #0x30]
10 occurrences: ldr r0, [r4]
10 occurrences: mov r2, r6
10 occurrences: bhi #0x40854bd8
10 occurrences: bhs #0x4085655c
10 occurrences: ldr r3, [r5, #0x30]
10 occurrences: bne #0x40856568
[END] Finished processing log file: square-2026-04-28-21:54:02.log

23 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4 -> str r0, [sp]
10 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000 -> cmp sb, ip
46 occurrences: mov r1, r4 -> ldr r2, [sp]
35 occurrences: sub sp, sp, #4 -> str r0, [sp]
27 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000
23 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4
21 occurrences: add sp, sp, #4 -> pop {pc}
19 occurrences: mov r2, r6 -> ldr r1, [r5, #0x30]
13 occurrences: mov r3, r6 -> ldr r2, [r5, #0x30]
11 occurrences: str r0, [sp] -> ldr r0, [r4]
10 occurrences: cmp r0, #0 -> bne #0x4085706c
10 occurrences: bic ip, ip, #0xfe0000 -> cmp sb, ip
64 occurrences: ldr r1, [r5, #0x30]
59 occurrences: cmp r0, #0
50 occurrences: blx ip
49 occurrences: cmp r2, ip
46 occurrences: mov r1, r4
46 occurrences: ldr r2, [sp]
45 occurrences: str r0, [sp]
37 occurrences: cmp r3, ip
36 occurrences: sub sp, sp, #4
34 occurrences: add sp, sp, #4
33 occurrences: ldr r2, [r5, #0x30]
30 occurrences: ldr r0, [r1, r2]
28 occurrences: bhi #0x40852d00
27 occurrences: mvn ip, #0xfe000000
27 occurrences: bic ip, ip, #0xfe0000
25 occurrences: bhs #0x40852d00
23 occurrences: str lr, [sp, #-4]!
23 occurrences: ldr r0, [r5, #0x30]
23 occurrences: mov r2, r6
21 occurrences: pop {pc}
19 occurrences: cmp r1, ip
17 occurrences: bhi #0x40857060
16 occurrences: mov lr, #0
16 occurrences: bhi #0x408527e8
16 occurrences: cmp sb, ip
15 occurrences: ldr r1, [r2, r3]
14 occurrences: str r0, [r4]
13 occurrences: bhs #0x4085243c
13 occurrences: bhi #0x4085243c
13 occurrences: mov r3, r6
13 occurrences: bhi #0x40854060
13 occurrences: bhs #0x40853798
13 occurrences: bhi #0x40853798
12 occurrences: ldr r0, [r4]
12 occurrences: ldr r3, [r5, #0x30]
12 occurrences: ldr r8, [r5, #0x30]
12 occurrences: cmp r8, ip
10 occurrences: sub sp, sp, #8
10 occurrences: bhi #0x408557bc
10 occurrences: bhs #0x40857060
10 occurrences: bne #0x4085706c
[END] Finished processing log file: guarded_sum-2026-04-28-21:54:01.log

22 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4 -> str r0, [sp]
30 occurrences: sub sp, sp, #4 -> str r0, [sp]
30 occurrences: mov r1, r4 -> ldr r2, [sp]
22 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4
20 occurrences: add sp, sp, #4 -> pop {pc}
38 occurrences: cmp r0, #0
36 occurrences: str r0, [sp]
32 occurrences: ldr r1, [r5, #0x30]
31 occurrences: sub sp, sp, #4
31 occurrences: blx ip
30 occurrences: mov r1, r4
30 occurrences: ldr r2, [sp]
29 occurrences: add sp, sp, #4
22 occurrences: str lr, [sp, #-4]!
22 occurrences: cmp r2, ip
20 occurrences: pop {pc}
17 occurrences: cmp r3, ip
15 occurrences: ldr r0, [r1, r2]
14 occurrences: str r0, [r4]
14 occurrences: ldr r2, [r5, #0x30]
13 occurrences: bhs #0x40852a04
13 occurrences: bhi #0x40852a04
10 occurrences: mov lr, #0
10 occurrences: bhi #0x40854a58
[END] Finished processing log file: helloworld-2026-04-28-21:54:02.log

22 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4 -> str r0, [sp]
44 occurrences: mov r1, r4 -> ldr r2, [sp]
32 occurrences: sub sp, sp, #4 -> str r0, [sp]
22 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4
22 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000
20 occurrences: add sp, sp, #4 -> pop {pc}
14 occurrences: mov r2, r6 -> ldr r1, [r5, #0x30]
10 occurrences: cmp r0, #0 -> bne #0x4085618c
54 occurrences: cmp r0, #0
48 occurrences: ldr r1, [r5, #0x30]
46 occurrences: blx ip
44 occurrences: mov r1, r4
44 occurrences: ldr r2, [sp]
42 occurrences: str r0, [sp]
33 occurrences: sub sp, sp, #4
31 occurrences: add sp, sp, #4
23 occurrences: ldr r2, [r5, #0x30]
22 occurrences: str lr, [sp, #-4]!
22 occurrences: mvn ip, #0xfe000000
22 occurrences: bic ip, ip, #0xfe0000
20 occurrences: pop {pc}
20 occurrences: .byte 0xf4, 0x12, 0xe0, 0xe7
17 occurrences: mov r2, r6
15 occurrences: ldr r3, [r5, #0x30]
14 occurrences: str r0, [r4]
14 occurrences: bhs #0x40852468
13 occurrences: ldr r0, [r5, #0x30]
13 occurrences: ldr r8, [r5, #0x30]
13 occurrences: bhs #0x40852cac
11 occurrences: mov lr, #0
11 occurrences: bhs #0x40856180
10 occurrences: ldr r0, [r4]
10 occurrences: bhs #0x40852210
10 occurrences: cmp r3, ip
10 occurrences: bne #0x4085618c
10 occurrences: bhi #0x40853548
[END] Finished processing log file: polynomial-2026-04-28-21:54:06.log

22 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4 -> str r0, [sp]
42 occurrences: mov r1, r4 -> ldr r2, [sp]
31 occurrences: sub sp, sp, #4 -> str r0, [sp]
22 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4
21 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000
20 occurrences: add sp, sp, #4 -> pop {pc}
12 occurrences: mov r3, r6 -> ldr r2, [r5, #0x30]
10 occurrences: cmp r0, #0 -> bne #0x40856134
53 occurrences: cmp r0, #0
45 occurrences: blx ip
42 occurrences: mov r1, r4
42 occurrences: ldr r2, [sp]
41 occurrences: str r0, [sp]
40 occurrences: ldr r1, [r5, #0x30]
32 occurrences: sub sp, sp, #4
30 occurrences: add sp, sp, #4
22 occurrences: str lr, [sp, #-4]!
21 occurrences: ldr r2, [r5, #0x30]
21 occurrences: mvn ip, #0xfe000000
21 occurrences: bic ip, ip, #0xfe0000
20 occurrences: pop {pc}
16 occurrences: ldr r0, [r5, #0x30]
15 occurrences: .byte 0xf4, 0x12, 0xe0, 0xe7
14 occurrences: str r0, [r4]
13 occurrences: ldr r8, [r5, #0x30]
13 occurrences: bhs #0x40852c18
12 occurrences: mov lr, #0
12 occurrences: mov r3, r6
12 occurrences: cmp r3, ip
10 occurrences: ldr r0, [r4]
10 occurrences: sub sp, sp, #8
10 occurrences: bhs #0x40856128
10 occurrences: ldr r3, [r5, #0x30]
10 occurrences: bne #0x40856134
10 occurrences: bhi #0x408534d0
[END] Finished processing log file: factorial-2026-04-28-21:54:05.log

23 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4 -> str r0, [sp]
46 occurrences: mov r1, r4 -> ldr r2, [sp]
35 occurrences: sub sp, sp, #4 -> str r0, [sp]
23 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4
21 occurrences: add sp, sp, #4 -> pop {pc}
18 occurrences: mov r2, r6 -> ldr r1, [r5, #0x30]
18 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000
13 occurrences: mov r3, r6 -> ldr r2, [r5, #0x30]
11 occurrences: str r0, [sp] -> ldr r0, [r4]
10 occurrences: cmp r0, #0 -> bne #0x40856a18
62 occurrences: ldr r1, [r5, #0x30]
59 occurrences: cmp r0, #0
50 occurrences: blx ip
46 occurrences: mov r1, r4
46 occurrences: ldr r2, [sp]
45 occurrences: str r0, [sp]
36 occurrences: sub sp, sp, #4
34 occurrences: add sp, sp, #4
33 occurrences: ldr r2, [r5, #0x30]
30 occurrences: .byte 0xf4, 0x12, 0xe0, 0xe7
24 occurrences: bhs #0x40852b64
23 occurrences: str lr, [sp, #-4]!
23 occurrences: ldr r0, [r5, #0x30]
22 occurrences: mov r2, r6
21 occurrences: pop {pc}
18 occurrences: mvn ip, #0xfe000000
18 occurrences: bic ip, ip, #0xfe0000
15 occurrences: .byte 0xf4, 0x23, 0xe1, 0xe7
14 occurrences: str r0, [r4]
13 occurrences: mov lr, #0
13 occurrences: bhs #0x408523c8
13 occurrences: mov r3, r6
13 occurrences: cmp r2, ip
13 occurrences: bhs #0x40853570
12 occurrences: ldr r0, [r4]
12 occurrences: ldr r3, [r5, #0x30]
12 occurrences: ldr r8, [r5, #0x30]
10 occurrences: sub sp, sp, #8
10 occurrences: bhs #0x40856a0c
10 occurrences: bne #0x40856a18
[END] Finished processing log file: guarded_sum-2026-04-28-21:54:06.log

14 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4 -> str r0, [sp] -> mov lr, r5
11 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000 -> cmp sb, ip -> bhi #0x408544a8
28 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4 -> str r0, [sp]
14 occurrences: sub sp, sp, #4 -> str r0, [sp] -> mov lr, r5
12 occurrences: push {r6, lr} -> sub sp, sp, #8 -> str r0, [sp]
12 occurrences: str r0, [sp] -> ldr r0, [r4] -> ldr r1, [r4, #4]
12 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000 -> cmp sb, ip
11 occurrences: bic ip, ip, #0xfe0000 -> cmp sb, ip -> bhi #0x408544a8
10 occurrences: sub sp, sp, #8 -> str r0, [sp] -> ldr r0, [r4]
10 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000 -> cmp r3, ip
45 occurrences: mov r1, r4 -> ldr r2, [sp]
40 occurrences: sub sp, sp, #4 -> str r0, [sp]
39 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000
30 occurrences: mov r2, r6 -> ldr r1, [r5, #0x30]
28 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4
26 occurrences: add sp, sp, #4 -> pop {pc}
24 occurrences: cmp r2, ip -> bhi #0x40852900
17 occurrences: mov r3, r2 -> ldr r1, [r5, #0x30]
16 occurrences: str r0, [sp] -> ldr r0, [r4]
14 occurrences: str r0, [sp] -> mov lr, r5
14 occurrences: sub sp, sp, #8 -> str r0, [sp]
13 occurrences: mov r3, r6 -> ldr r2, [r5, #0x30]
12 occurrences: push {r6, lr} -> sub sp, sp, #8
12 occurrences: ldr r0, [r4] -> ldr r1, [r4, #4]
12 occurrences: bic ip, ip, #0xfe0000 -> cmp sb, ip
11 occurrences: cmp r3, ip -> bhi #0x40852900
11 occurrences: add sp, sp, #8 -> pop {r6, pc}
11 occurrences: cmp r0, #0 -> bne #0x408574d0
11 occurrences: cmp sb, ip -> bhi #0x408544a8
10 occurrences: cmp r1, ip -> bhi #0x40852900
10 occurrences: bic ip, ip, #0xfe0000 -> cmp r3, ip
82 occurrences: ldr r1, [r5, #0x30]
63 occurrences: cmp r3, ip
55 occurrences: str r0, [sp]
55 occurrences: cmp r0, #0
52 occurrences: bhi #0x40852900
51 occurrences: cmp r2, ip
48 occurrences: blx ip
47 occurrences: bhs #0x40852900
45 occurrences: mov r1, r4
45 occurrences: ldr r2, [sp]
41 occurrences: sub sp, sp, #4
39 occurrences: add sp, sp, #4
39 occurrences: mvn ip, #0xfe000000
39 occurrences: bic ip, ip, #0xfe0000
34 occurrences: mov r2, r6
31 occurrences: ldr r3, [r5, #0x30]
29 occurrences: ldr r2, [r5, #0x30]
29 occurrences: ldr r0, [r1, r2]
28 occurrences: str lr, [sp, #-4]!
28 occurrences: ldr r0, [r5, #0x30]
26 occurrences: pop {pc}
25 occurrences: mov r3, r2
22 occurrences: bhi #0x408574c4
20 occurrences: str r0, [r4]
18 occurrences: mov lr, #0
18 occurrences: cmp r6, ip
17 occurrences: ldr r0, [r4]
17 occurrences: cmp r1, ip
17 occurrences: cmp sb, ip
15 occurrences: bhs #0x408574c4
15 occurrences: ldr r8, [r5, #0x30]
15 occurrences: bhi #0x408544a8
14 occurrences: mov lr, r5
14 occurrences: mov r3, r6
14 occurrences: sub sp, sp, #8
14 occurrences: add sp, sp, #8
13 occurrences: ldr lr, [r5, #0x3c]
13 occurrences: cmp r7, ip
13 occurrences: bhs #0x40853af0
13 occurrences: bhi #0x40853af0
12 occurrences: ldr r1, [r2, r3]
12 occurrences: str r0, [r1, r2]
12 occurrences: push {r6, lr}
12 occurrences: ldr r1, [r4, #4]
11 occurrences: pop {r6, pc}
11 occurrences: mov r6, r2
11 occurrences: bhs #0x40853124
11 occurrences: bhi #0x40853124
11 occurrences: ldr r0, [r1, r3]
11 occurrences: bne #0x408574d0
10 occurrences: adds r3, r3, #0xc
10 occurrences: mov r3, r0
10 occurrences: adds r3, r3, #8
10 occurrences: bhi #0x40855b40
10 occurrences: ldr r7, [r5, #0x30]
[END] Finished processing log file: dispatcher-2026-04-28-21:54:01.log

12 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000 -> cmp sb, ip -> bhi #0x408541c8
24 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4 -> str r0, [sp]
12 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000 -> cmp sb, ip
12 occurrences: bic ip, ip, #0xfe0000 -> cmp sb, ip -> bhi #0x408541c8
56 occurrences: mov r1, r4 -> ldr r2, [sp]
36 occurrences: sub sp, sp, #4 -> str r0, [sp]
29 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000
24 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4
24 occurrences: mov r1, r6 -> ldr r0, [r5, #0x30]
23 occurrences: mov r2, r6 -> ldr r1, [r5, #0x30]
22 occurrences: add sp, sp, #4 -> pop {pc}
21 occurrences: mov r3, r6 -> ldr r2, [r5, #0x30]
17 occurrences: cmp r1, ip -> bhi #0x40852dec
12 occurrences: ldr lr, [ip] -> ldr ip, [ip, #4]
12 occurrences: bic ip, ip, #0xfe0000 -> cmp sb, ip
12 occurrences: cmp sb, ip -> bhi #0x408541c8
11 occurrences: str r0, [sp] -> ldr r0, [r4]
11 occurrences: cmp r0, #0 -> bne #0x40857130
10 occurrences: sub sp, sp, #8 -> str r0, [sp]
10 occurrences: cmp r0, #0 -> bne #0x40859ef4
77 occurrences: cmp r0, #0
64 occurrences: blx ip
61 occurrences: ldr r1, [r5, #0x30]
58 occurrences: mov r1, r4
58 occurrences: ldr r2, [sp]
48 occurrences: str r0, [sp]
48 occurrences: cmp r2, ip
47 occurrences: cmp r3, ip
42 occurrences: ldr r2, [r5, #0x30]
39 occurrences: ldr r0, [r5, #0x30]
38 occurrences: sub sp, sp, #4
36 occurrences: add sp, sp, #4
36 occurrences: bhi #0x40852dec
35 occurrences: bhs #0x40852dec
31 occurrences: cmp r1, ip
29 occurrences: mvn ip, #0xfe000000
29 occurrences: bic ip, ip, #0xfe0000
27 occurrences: mov r2, r6
27 occurrences: ldr r0, [r1, r2]
24 occurrences: str lr, [sp, #-4]!
24 occurrences: mov r1, r6
22 occurrences: pop {pc}
21 occurrences: mov r3, r6
19 occurrences: mov lr, #0
19 occurrences: bhi #0x40857124
17 occurrences: cmp sb, ip
16 occurrences: cmp ip, #0
16 occurrences: bhs #0x408527c0
16 occurrences: bhi #0x408527c0
16 occurrences: bhi #0x408541c8
15 occurrences: ldr r3, [r5, #0x30]
15 occurrences: ldr r8, [r5, #0x30]
14 occurrences: str r0, [r4]
14 occurrences: add ip, r0, r1
14 occurrences: mov r1, r0
14 occurrences: bhi #0x40859ee8
13 occurrences: bhi #0x408523f8
13 occurrences: ldr ip, [r4, #0x14]
13 occurrences: bhs #0x4085384c
13 occurrences: bhi #0x4085384c
12 occurrences: ldr r0, [r4]
12 occurrences: ldr r1, [r2, r3]
12 occurrences: ldr lr, [ip]
12 occurrences: ldr ip, [ip, #4]
12 occurrences: cmp r8, ip
12 occurrences: cmp r6, ip
12 occurrences: bhs #0x40857124
12 occurrences: bhi #0x40857cd8
11 occurrences: mov r0, #0
11 occurrences: ldr ip, [r4, #0x1c]
11 occurrences: bne #0x40857130
11 occurrences: mov r3, r0
10 occurrences: mov ip, #0
10 occurrences: sub sp, sp, #8
10 occurrences: ldr lr, [r5, #0x3c]
10 occurrences: bhs #0x408523f8
10 occurrences: mov r1, #0
10 occurrences: mov r2, r1
10 occurrences: ldr r6, [r5, #0x30]
10 occurrences: str r0, [r1, r2]
10 occurrences: bhi #0x40855874
10 occurrences: mov r6, r0
10 occurrences: bne #0x40859ef4
[END] Finished processing log file: promote-2026-04-28-21:54:02.log

23 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4 -> str r0, [sp]
41 occurrences: mov r1, r4 -> ldr r2, [sp]
33 occurrences: sub sp, sp, #4 -> str r0, [sp]
23 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4
21 occurrences: add sp, sp, #4 -> pop {pc}
18 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000
10 occurrences: cmp r0, #0 -> bne #0x40855fbc
51 occurrences: cmp r0, #0
43 occurrences: blx ip
41 occurrences: str r0, [sp]
41 occurrences: mov r1, r4
41 occurrences: ldr r2, [sp]
41 occurrences: ldr r1, [r5, #0x30]
34 occurrences: sub sp, sp, #4
32 occurrences: add sp, sp, #4
23 occurrences: str lr, [sp, #-4]!
21 occurrences: pop {pc}
18 occurrences: mvn ip, #0xfe000000
18 occurrences: bic ip, ip, #0xfe0000
17 occurrences: ldr r2, [r5, #0x30]
16 occurrences: .byte 0xf4, 0x12, 0xe0, 0xe7
14 occurrences: str r0, [r4]
13 occurrences: ldr r0, [r5, #0x30]
13 occurrences: bhs #0x40852ab0
11 occurrences: mov lr, #0
11 occurrences: ldr r8, [r5, #0x30]
10 occurrences: ldr r0, [r4]
10 occurrences: mov r2, r6
10 occurrences: bhs #0x40855fb0
10 occurrences: ldr r3, [r5, #0x30]
10 occurrences: bne #0x40855fbc
[END] Finished processing log file: square-2026-04-28-21:54:07.log

24 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4 -> str r0, [sp]
58 occurrences: mov r1, r4 -> ldr r2, [sp]
36 occurrences: sub sp, sp, #4 -> str r0, [sp]
24 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4
24 occurrences: mov r1, r6 -> ldr r0, [r5, #0x30]
22 occurrences: add sp, sp, #4 -> pop {pc}
21 occurrences: mov r2, r6 -> ldr r1, [r5, #0x30]
21 occurrences: mov r3, r6 -> ldr r2, [r5, #0x30]
20 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000
12 occurrences: ldr lr, [ip] -> ldr ip, [ip, #4]
11 occurrences: cmp r0, #0 -> bne #0x40856a9c
10 occurrences: sub sp, sp, #8 -> str r0, [sp]
10 occurrences: str r0, [sp] -> ldr r0, [r4]
10 occurrences: cmp r0, #0 -> bne #0x40859858
77 occurrences: cmp r0, #0
64 occurrences: blx ip
59 occurrences: ldr r1, [r5, #0x30]
58 occurrences: mov r1, r4
58 occurrences: ldr r2, [sp]
48 occurrences: str r0, [sp]
42 occurrences: ldr r2, [r5, #0x30]
39 occurrences: ldr r0, [r5, #0x30]
38 occurrences: sub sp, sp, #4
36 occurrences: add sp, sp, #4
33 occurrences: bhs #0x40852c14
27 occurrences: .byte 0xf4, 0x12, 0xe0, 0xe7
25 occurrences: mov r2, r6
24 occurrences: str lr, [sp, #-4]!
24 occurrences: mov r1, r6
22 occurrences: pop {pc}
21 occurrences: mov r3, r6
20 occurrences: mvn ip, #0xfe000000
20 occurrences: bic ip, ip, #0xfe0000
16 occurrences: cmp ip, #0
16 occurrences: cmp r3, ip
15 occurrences: mov lr, #0
15 occurrences: bhs #0x408526f0
15 occurrences: ldr r3, [r5, #0x30]
15 occurrences: ldr r8, [r5, #0x30]
14 occurrences: str r0, [r4]
14 occurrences: add ip, r0, r1
14 occurrences: mov r1, r0
13 occurrences: ldr ip, [r4, #0x14]
13 occurrences: bhs #0x40853608
12 occurrences: ldr r0, [r4]
12 occurrences: .byte 0xf4, 0x23, 0xe1, 0xe7
12 occurrences: ldr lr, [ip]
12 occurrences: ldr ip, [ip, #4]
12 occurrences: bhs #0x40856a90
12 occurrences: bhi #0x40857650
11 occurrences: mov r2, #0
11 occurrences: mov r0, #0
11 occurrences: ldr ip, [r4, #0x1c]
11 occurrences: bne #0x40856a9c
11 occurrences: mov r3, r0
10 occurrences: mov ip, #0
10 occurrences: sub sp, sp, #8
10 occurrences: ldr lr, [r5, #0x3c]
10 occurrences: bhs #0x408523ac
10 occurrences: mov r1, #0
10 occurrences: mov r2, r1
10 occurrences: ldr r6, [r5, #0x30]
10 occurrences: .byte 0xf4, 0x12, 0xd0, 0xe7
10 occurrences: mov r6, r0
10 occurrences: bhi #0x40853dac
10 occurrences: bne #0x40859858
[END] Finished processing log file: promote-2026-04-28-21:54:07.log

22 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4 -> str r0, [sp]
30 occurrences: sub sp, sp, #4 -> str r0, [sp]
30 occurrences: mov r1, r4 -> ldr r2, [sp]
22 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4
20 occurrences: add sp, sp, #4 -> pop {pc}
38 occurrences: cmp r0, #0
36 occurrences: str r0, [sp]
32 occurrences: ldr r1, [r5, #0x30]
31 occurrences: sub sp, sp, #4
31 occurrences: blx ip
30 occurrences: mov r1, r4
30 occurrences: ldr r2, [sp]
29 occurrences: add sp, sp, #4
22 occurrences: str lr, [sp, #-4]!
20 occurrences: pop {pc}
15 occurrences: .byte 0xf4, 0x12, 0xe0, 0xe7
14 occurrences: str r0, [r4]
14 occurrences: ldr r2, [r5, #0x30]
13 occurrences: bhs #0x4085296c
[END] Finished processing log file: helloworld-2026-04-28-21:54:06.log

10 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000 -> cmp r2, ip -> bhi #0x4085291c
22 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4 -> str r0, [sp]
14 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000 -> cmp r2, ip
10 occurrences: bic ip, ip, #0xfe0000 -> cmp r2, ip -> bhi #0x4085291c
10 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000 -> cmp sb, ip
41 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000
39 occurrences: mov r1, r4 -> ldr r2, [sp]
37 occurrences: mov r2, r6 -> ldr r1, [r5, #0x30]
32 occurrences: sub sp, sp, #4 -> str r0, [sp]
32 occurrences: cmp r2, ip -> bhi #0x4085291c
22 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4
20 occurrences: add sp, sp, #4 -> pop {pc}
20 occurrences: mov r3, r6 -> ldr r2, [r5, #0x30]
15 occurrences: cmp r3, ip -> bhi #0x4085291c
14 occurrences: bic ip, ip, #0xfe0000 -> cmp r2, ip
10 occurrences: cmp r0, #0 -> bne #0x40856d20
10 occurrences: bic ip, ip, #0xfe0000 -> cmp sb, ip
74 occurrences: ldr r1, [r5, #0x30]
58 occurrences: cmp r2, ip
55 occurrences: bhs #0x4085291c
54 occurrences: bhi #0x4085291c
51 occurrences: cmp r0, #0
42 occurrences: blx ip
41 occurrences: str r0, [sp]
41 occurrences: mov r1, r4
41 occurrences: ldr r2, [sp]
41 occurrences: cmp r3, ip
41 occurrences: mvn ip, #0xfe000000
41 occurrences: bic ip, ip, #0xfe0000
40 occurrences: mov r2, r6
36 occurrences: ldr r2, [r5, #0x30]
33 occurrences: sub sp, sp, #4
31 occurrences: add sp, sp, #4
27 occurrences: ldr r0, [r1, r2]
22 occurrences: str lr, [sp, #-4]!
22 occurrences: ldr r1, [r2, r3]
20 occurrences: pop {pc}
20 occurrences: mov r3, r6
20 occurrences: bhi #0x40856d14
16 occurrences: mov lr, #0
15 occurrences: cmp sb, ip
14 occurrences: str r0, [r4]
14 occurrences: ldr r0, [r5, #0x30]
13 occurrences: cmp r1, ip
13 occurrences: mov r3, r0
13 occurrences: ldr r3, [r5, #0x30]
13 occurrences: str r0, [r1, r2]
13 occurrences: bhs #0x40856d14
13 occurrences: bhs #0x40853438
13 occurrences: bhi #0x40853438
12 occurrences: ldr r8, [r5, #0x30]
11 occurrences: bhi #0x40853d04
10 occurrences: ldr r0, [r4]
10 occurrences: mov r6, r0
10 occurrences: bhi #0x40855460
10 occurrences: bne #0x40856d20
[END] Finished processing log file: memwalk-2026-04-28-21:54:02.log

22 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4 -> str r0, [sp]
10 occurrences: ldr r1, [r5, #0x30] -> mvn lr, #0xfe000000 -> bic lr, lr, #0xfe0000
41 occurrences: mov r1, r4 -> ldr r2, [sp]
35 occurrences: mov r2, r6 -> ldr r1, [r5, #0x30]
32 occurrences: sub sp, sp, #4 -> str r0, [sp]
26 occurrences: mvn lr, #0xfe000000 -> bic lr, lr, #0xfe0000
22 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4
21 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000
20 occurrences: add sp, sp, #4 -> pop {pc}
20 occurrences: mov r3, r6 -> ldr r2, [r5, #0x30]
10 occurrences: ldr r1, [r5, #0x30] -> mvn lr, #0xfe000000
10 occurrences: cmp r0, #0 -> bne #0x408566d8
72 occurrences: ldr r1, [r5, #0x30]
53 occurrences: bhs #0x408527b8
51 occurrences: cmp r0, #0
42 occurrences: blx ip
41 occurrences: str r0, [sp]
41 occurrences: mov r1, r4
41 occurrences: ldr r2, [sp]
38 occurrences: mov r2, r6
35 occurrences: ldr r2, [r5, #0x30]
33 occurrences: sub sp, sp, #4
31 occurrences: add sp, sp, #4
27 occurrences: .byte 0xf4, 0x12, 0xe0, 0xe7
26 occurrences: mvn lr, #0xfe000000
26 occurrences: bic lr, lr, #0xfe0000
22 occurrences: str lr, [sp, #-4]!
22 occurrences: .byte 0xf4, 0x23, 0xe1, 0xe7
21 occurrences: mvn ip, #0xfe000000
21 occurrences: bic ip, ip, #0xfe0000
20 occurrences: pop {pc}
20 occurrences: mov r3, r6
14 occurrences: str r0, [r4]
14 occurrences: ldr r0, [r5, #0x30]
13 occurrences: ldr r3, [r5, #0x30]
13 occurrences: .byte 0xf4, 0x12, 0xd0, 0xe7
13 occurrences: bhs #0x408566cc
13 occurrences: bhs #0x4085321c
12 occurrences: mov r3, r0
12 occurrences: ldr r8, [r5, #0x30]
11 occurrences: mov lr, #0
10 occurrences: ldr r0, [r4]
10 occurrences: mov r6, r0
10 occurrences: cmp r2, ip
10 occurrences: bne #0x408566d8
[END] Finished processing log file: memwalk-2026-04-28-21:54:06.log

14 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4 -> str r0, [sp] -> mov lr, r5
28 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4 -> str r0, [sp]
14 occurrences: sub sp, sp, #4 -> str r0, [sp] -> mov lr, r5
12 occurrences: push {r6, lr} -> sub sp, sp, #8 -> str r0, [sp]
12 occurrences: str r0, [sp] -> ldr r0, [r4] -> ldr r1, [r4, #4]
10 occurrences: sub sp, sp, #8 -> str r0, [sp] -> ldr r0, [r4]
10 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000 -> cmp r3, ip
45 occurrences: mov r1, r4 -> ldr r2, [sp]
40 occurrences: sub sp, sp, #4 -> str r0, [sp]
28 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4
27 occurrences: mov r2, r6 -> ldr r1, [r5, #0x30]
26 occurrences: add sp, sp, #4 -> pop {pc}
25 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000
17 occurrences: mov r3, r2 -> ldr r1, [r5, #0x30]
16 occurrences: str r0, [sp] -> ldr r0, [r4]
15 occurrences: mvn lr, #0xfe000000 -> bic lr, lr, #0xfe0000
14 occurrences: str r0, [sp] -> mov lr, r5
14 occurrences: sub sp, sp, #8 -> str r0, [sp]
13 occurrences: mov r3, r6 -> ldr r2, [r5, #0x30]
12 occurrences: push {r6, lr} -> sub sp, sp, #8
12 occurrences: ldr r0, [r4] -> ldr r1, [r4, #4]
11 occurrences: add sp, sp, #8 -> pop {r6, pc}
11 occurrences: cmp r0, #0 -> bne #0x40856d20
10 occurrences: bic ip, ip, #0xfe0000 -> cmp r3, ip
79 occurrences: ldr r1, [r5, #0x30]
55 occurrences: str r0, [sp]
55 occurrences: cmp r0, #0
48 occurrences: blx ip
45 occurrences: mov r1, r4
45 occurrences: ldr r2, [sp]
44 occurrences: bhs #0x408527bc
41 occurrences: sub sp, sp, #4
39 occurrences: add sp, sp, #4
31 occurrences: mov r2, r6
31 occurrences: ldr r3, [r5, #0x30]
29 occurrences: ldr r2, [r5, #0x30]
29 occurrences: .byte 0xf4, 0x12, 0xe0, 0xe7
28 occurrences: str lr, [sp, #-4]!
28 occurrences: ldr r0, [r5, #0x30]
26 occurrences: pop {pc}
25 occurrences: mov r3, r2
25 occurrences: mvn ip, #0xfe000000
25 occurrences: bic ip, ip, #0xfe0000
20 occurrences: str r0, [r4]
17 occurrences: ldr r0, [r4]
15 occurrences: cmp r3, ip
15 occurrences: bhs #0x40856d14
15 occurrences: mvn lr, #0xfe000000
15 occurrences: bic lr, lr, #0xfe0000
15 occurrences: ldr r8, [r5, #0x30]
14 occurrences: mov lr, r5
14 occurrences: mov r3, r6
14 occurrences: sub sp, sp, #8
14 occurrences: add sp, sp, #8
13 occurrences: ldr lr, [r5, #0x3c]
13 occurrences: bhs #0x40853808
12 occurrences: mov lr, #0
12 occurrences: .byte 0xf4, 0x23, 0xe1, 0xe7
12 occurrences: .byte 0xf4, 0x12, 0xd0, 0xe7
12 occurrences: push {r6, lr}
12 occurrences: ldr r1, [r4, #4]
11 occurrences: bhi #0x408527bc
11 occurrences: cmp r2, ip
11 occurrences: pop {r6, pc}
11 occurrences: mov r6, r2
11 occurrences: bhs #0x40852e44
11 occurrences: .byte 0xf4, 0x13, 0xe0, 0xe7
11 occurrences: bne #0x40856d20
10 occurrences: udf #0x3e0c
10 occurrences: mov r3, r0
10 occurrences: udf #0x3e08
10 occurrences: ldr r7, [r5, #0x30]
[END] Finished processing log file: dispatcher-2026-04-28-21:54:05.log

12 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000 -> cmp sb, ip -> bhi #0x408536c8
22 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4 -> str r0, [sp]
13 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000 -> cmp sb, ip
12 occurrences: bic ip, ip, #0xfe0000 -> cmp sb, ip -> bhi #0x408536c8
42 occurrences: mov r1, r4 -> ldr r2, [sp]
31 occurrences: sub sp, sp, #4 -> str r0, [sp]
30 occurrences: mvn ip, #0xfe000000 -> bic ip, ip, #0xfe0000
22 occurrences: str lr, [sp, #-4]! -> sub sp, sp, #4
20 occurrences: add sp, sp, #4 -> pop {pc}
13 occurrences: bic ip, ip, #0xfe0000 -> cmp sb, ip
12 occurrences: mov r3, r6 -> ldr r2, [r5, #0x30]
12 occurrences: cmp sb, ip -> bhi #0x408536c8
10 occurrences: cmp r0, #0 -> bne #0x408566b8
53 occurrences: cmp r0, #0
45 occurrences: blx ip
42 occurrences: mov r1, r4
42 occurrences: ldr r2, [sp]
41 occurrences: str r0, [sp]
40 occurrences: ldr r1, [r5, #0x30]
32 occurrences: sub sp, sp, #4
30 occurrences: add sp, sp, #4
30 occurrences: mvn ip, #0xfe000000
30 occurrences: bic ip, ip, #0xfe0000
29 occurrences: cmp r3, ip
24 occurrences: cmp r2, ip
22 occurrences: str lr, [sp, #-4]!
21 occurrences: ldr r2, [r5, #0x30]
20 occurrences: pop {pc}
18 occurrences: cmp sb, ip
17 occurrences: bhi #0x408566ac
16 occurrences: ldr r0, [r5, #0x30]
16 occurrences: bhi #0x408536c8
15 occurrences: ldr r0, [r1, r2]
14 occurrences: str r0, [r4]
13 occurrences: mov lr, #0
13 occurrences: ldr r8, [r5, #0x30]
13 occurrences: bhs #0x40852cec
13 occurrences: bhi #0x40852cec
12 occurrences: cmp r1, ip
12 occurrences: mov r3, r6
10 occurrences: ldr r0, [r4]
10 occurrences: sub sp, sp, #8
10 occurrences: bhi #0x40854d24
10 occurrences: bhs #0x408566ac
10 occurrences: ldr r3, [r5, #0x30]
10 occurrences: bne #0x408566b8
[END] Finished processing log file: factorial-2026-04-28-21:54:01.log
```

```
12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
11 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
31 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
12 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
12 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
39 occurrences: push {lr} -> sub sp, sp, #4 -> str r0, [sp]
35 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
31 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16]
16 occurrences: @ <UNDEFINED> instruction: 0xe7e8abf4 -> mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip] -> str r7, [ip, #4]
15 occurrences: sub sp, sp, #4 -> str r0, [sp] -> ldr r0, [r4]
15 occurrences: @ <UNDEFINED> instruction: 0xe7d8abf4 -> mov fp, r1 -> ldr sl, [r5, #48]
14 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r3, ip
13 occurrences: str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1 -> add r1, r1, #4
12 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
12 occurrences: add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
11 occurrences: str r0, [sp] -> ldr r0, [r4] -> ldr r1, [r4, #4]
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432 -> bic ip, ip, #16646144
119 occurrences: mov r1, r4 -> ldr r2, [sp]
59 occurrences: sub sp, sp, #4 -> str r0, [sp]
53 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144
39 occurrences: push {lr} -> sub sp, sp, #4
39 occurrences: add sp, sp, #4 -> pop {pc}
36 occurrences: str r0, [r1, #16] -> ldr r0, [sp]
35 occurrences: ldr r1, [sp] -> str r0, [r1, #16]
33 occurrences: cmp r8, ip -> bhi 0x4d24
32 occurrences: mov r0, #8 -> ldr r1, [sp]
31 occurrences: mvn lr, #-33554432 -> bic lr, lr, #16646144
31 occurrences: cmp r0, #0 -> bne 0x6ef0
26 occurrences: add sp, sp, #4 -> bx r0
22 occurrences: cmp r0, #0 -> bne 0x4184
20 occurrences: str r0, [sp] -> ldr r0, [r4]
19 occurrences: mov r2, r6 -> ldr r1, [r5, #48]
19 occurrences: cmp r7, ip -> bhi 0x4d24
18 occurrences: mov r7, r2 -> ldr r6, [r5, #48]
17 occurrences: mov r3, r6 -> ldr r2, [r5, #48]
17 occurrences: mov fp, r1 -> ldr sl, [r5, #48]
17 occurrences: mov r8, r2 -> ldr r7, [r5, #48]
16 occurrences: @ <UNDEFINED> instruction: 0xe7e8abf4 -> mov fp, r6
16 occurrences: mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: @ <UNDEFINED> instruction: 0xe7d178f4 -> ldr r8, [r5, #48]
16 occurrences: cmp r6, ip -> bhi 0x4d24
16 occurrences: mov r8, r0 -> ldr r6, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip]
16 occurrences: str r1, [ip] -> str r7, [ip, #4]
15 occurrences: @ <UNDEFINED> instruction: 0xe7d8abf4 -> mov fp, r1
14 occurrences: ldr r0, [sp] -> ldr r1, [sp, #12]
14 occurrences: bic ip, ip, #16646144 -> cmp r3, ip
12 occurrences: ldr r1, [r4] -> ldr r0, [r5, #48]
12 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48]
12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1
12 occurrences: mov r6, r1 -> add r1, r1, #4
12 occurrences: add r1, r1, #4 -> mov r8, r2
11 occurrences: ldr r0, [sp] -> ldr r1, [sp, #4]
11 occurrences: add sp, sp, #8 -> bx r0
11 occurrences: sub sp, sp, #8 -> str r0, [sp]
11 occurrences: str r0, [sp] -> ldr r6, [r4]
11 occurrences: ldr r0, [r4] -> ldr r1, [r4, #4]
11 occurrences: cmp r1, ip -> bhi 0x4178
10 occurrences: ldr r2, [r4] -> ldr r1, [r5, #48]
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432
10 occurrences: cmp r3, ip -> bhi 0x4178
10 occurrences: udf #15920 -> bcs 0x4178
10 occurrences: cmp r1, ip -> bhi 0x6ee4
175 occurrences: blx ip
162 occurrences: cmp r0, #0
119 occurrences: mov r1, r4
119 occurrences: ldr r2, [sp]
111 occurrences: andeq r8, r4, ip, lsl #18
108 occurrences: add sp, sp, #4
92 occurrences: ldr r1, [r5, #48]
83 occurrences: ldr r2, [r5, #48]
73 occurrences: str r0, [sp]
68 occurrences: bhi 0x4d24
61 occurrences: sub sp, sp, #4
61 occurrences: mov lr, #0
53 occurrences: mvn ip, #-33554432
53 occurrences: bic ip, ip, #16646144
51 occurrences: ldr r0, [r5, #48]
51 occurrences: ldr r6, [r5, #48]
46 occurrences: bcs 0x4178
45 occurrences: ldr r0, [sp]
45 occurrences: bx r0
45 occurrences: andeq r8, r4, r4
42 occurrences: ldr r3, [r5, #48]
40 occurrences: bhi 0x6ee4
39 occurrences: push {lr}
39 occurrences: pop {pc}
39 occurrences: cmp r3, ip
39 occurrences: cmp r8, ip
36 occurrences: ldr r1, [sp]
36 occurrences: str r0, [r1, #16]
36 occurrences: ldr sl, [r5, #48]
36 occurrences: bcs 0x1540
36 occurrences: cmp r1, ip
34 occurrences: mov r1, r0
34 occurrences: cmp r7, ip
33 occurrences: cmp ip, #0
33 occurrences: ldr r8, [r5, #48]
32 occurrences: mov r0, #8
32 occurrences: @ <UNDEFINED> instruction: 0xe7e012f4
32 occurrences: ldr r7, [r5, #48]
32 occurrences: bhi 0x4178
32 occurrences: bne 0x6ef0
31 occurrences: ldr ip, [r4, #28]
31 occurrences: mvn lr, #-33554432
31 occurrences: bic lr, lr, #16646144
30 occurrences: cmp r6, ip
26 occurrences: add sp, sp, #8
26 occurrences: str r0, [r4]
24 occurrences: mov r2, r6
24 occurrences: mov r7, r2
24 occurrences: mov r8, r0
23 occurrences: ldr ip, [r4, #20]
23 occurrences: bne 0x4184
22 occurrences: cmp r0, ip
22 occurrences: str lr, [r4, #4]
22 occurrences: ldr ip, [r4, #64]
21 occurrences: ldr r0, [r4]
21 occurrences: mov r3, r1
21 occurrences: mov r6, r1
21 occurrences: mov ip, #0
20 occurrences: @ <UNDEFINED> instruction: 0xe7e123f4
20 occurrences: mov r6, r0
20 occurrences: mov fp, r1
19 occurrences: mov r2, #0
19 occurrences: mov r2, r0
19 occurrences: mov r8, r2
19 occurrences: ldr ip, [r4, #80]
19 occurrences: ldr ip, [r4, #84]
18 occurrences: mov r2, r1
18 occurrences: mov r3, r6
18 occurrences: cmp r2, ip
18 occurrences: bcs 0xca4
18 occurrences: mov lr, #1
18 occurrences: ldr ip, [r4, #16]
18 occurrences: str r1, [ip]
17 occurrences: mov r0, #0
17 occurrences: mov lr, #64, 22
17 occurrences: mov r3, r0
17 occurrences: cmp r1, #0
17 occurrences: mov fp, r6
17 occurrences: mov r1, #0
17 occurrences: bcs 0x2a1c
17 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4
17 occurrences: @ <UNDEFINED> instruction: 0xe7d178f4
17 occurrences: b 0x4d1c
16 occurrences: @ <UNDEFINED> instruction: 0xe7e8abf4
16 occurrences: @ <UNDEFINED> instruction: 0xe7d8abf4
16 occurrences: add ip, r6, r8
16 occurrences: str r7, [ip, #4]
15 occurrences: mov r7, #0
15 occurrences: str lr, [r4, #92]
14 occurrences: ldr r1, [sp, #12]
14 occurrences: bcs 0x460
14 occurrences: mov r3, #0
14 occurrences: add r1, r1, #4
14 occurrences: bhi 0x190c
14 occurrences: str lr, [r4, #52]
14 occurrences: ldr r3, [r4, #28]
14 occurrences: str lr, [r4, #84]
14 occurrences: ldr r2, [r4, #28]
14 occurrences: ldr ip, [r4, #72]
13 occurrences: cmp r6, #0
13 occurrences: ldr ip, [r4, #12]
13 occurrences: mov r6, r7
13 occurrences: str lr, [r4, #40]
13 occurrences: str lr, [r4, #164]
12 occurrences: ldr lr, [r5, #60]
12 occurrences: udf #11792
12 occurrences: str r6, [r4]
12 occurrences: ldr r1, [r4, #4]
12 occurrences: mov r0, r1
12 occurrences: bcs 0x190c
12 occurrences: ldr r1, [r4]
12 occurrences: ldr ip, [r4, #44]
12 occurrences: bcs 0x6ee4
11 occurrences: ldr r1, [sp, #4]
11 occurrences: sub sp, sp, #8
11 occurrences: @ <UNDEFINED> instruction: 0xe7e023f4
11 occurrences: @ <UNDEFINED> instruction: 0xe7d201f4
11 occurrences: mov r6, #0
11 occurrences: ldr r6, [r4]
11 occurrences: str lr, [r4, #44]
11 occurrences: udf #15920
11 occurrences: cmp r2, #0
11 occurrences: mov sl, r1
11 occurrences: ldr r2, [r4]
11 occurrences: mvn lr, #0
11 occurrences: mov r7, r0
11 occurrences: str lr, [r4, #36]
11 occurrences: mov lr, #32
10 occurrences: bcs 0x208
10 occurrences: ldr r1, [r5, #60]
10 occurrences: ldr r0, [r4, #4]
10 occurrences: str lr, [r4, #16]
10 occurrences: str lr, [r4]
10 occurrences: ldr r2, [r4, #8]
10 occurrences: cmp r9, ip
10 occurrences: bhi 0x1540
10 occurrences: ldr ip, [r4, #24]
10 occurrences: ldr ip, [r4]
10 occurrences: ldr r1, [ip]
[END] Finished processing log file: polynomial-2026-04-28-21:54:06.bin.log

12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
10 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
32 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
12 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
11 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
40 occurrences: push {lr} -> sub sp, sp, #4 -> str r0, [sp]
36 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
32 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16]
16 occurrences: sub sp, sp, #4 -> str r0, [sp] -> ldr r0, [r4]
16 occurrences: @ <UNDEFINED> instruction: 0xe7e8abf4 -> mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip] -> str r7, [ip, #4]
15 occurrences: @ <UNDEFINED> instruction: 0xe7d8abf4 -> mov fp, r1 -> ldr sl, [r5, #48]
14 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r3, ip
12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1 -> add r1, r1, #4
12 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
12 occurrences: add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
11 occurrences: str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
11 occurrences: str r0, [sp] -> ldr r0, [r4] -> ldr r1, [r4, #4]
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432 -> bic ip, ip, #16646144
119 occurrences: mov r1, r4 -> ldr r2, [sp]
61 occurrences: sub sp, sp, #4 -> str r0, [sp]
53 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144
40 occurrences: push {lr} -> sub sp, sp, #4
40 occurrences: add sp, sp, #4 -> pop {pc}
36 occurrences: ldr r1, [sp] -> str r0, [r1, #16]
36 occurrences: str r0, [r1, #16] -> ldr r0, [sp]
33 occurrences: cmp r8, ip -> bhi 0x4b74
32 occurrences: mov r0, #8 -> ldr r1, [sp]
31 occurrences: mvn lr, #-33554432 -> bic lr, lr, #16646144
31 occurrences: cmp r0, #0 -> bne 0x6d58
27 occurrences: add sp, sp, #4 -> bx r0
23 occurrences: cmp r0, #0 -> bne 0x3fb4
20 occurrences: str r0, [sp] -> ldr r0, [r4]
19 occurrences: cmp r7, ip -> bhi 0x4b74
18 occurrences: mov r7, r2 -> ldr r6, [r5, #48]
17 occurrences: mov fp, r1 -> ldr sl, [r5, #48]
17 occurrences: mov r8, r2 -> ldr r7, [r5, #48]
16 occurrences: @ <UNDEFINED> instruction: 0xe7e8abf4 -> mov fp, r6
16 occurrences: mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: @ <UNDEFINED> instruction: 0xe7d178f4 -> ldr r8, [r5, #48]
16 occurrences: cmp r6, ip -> bhi 0x4b74
16 occurrences: mov r8, r0 -> ldr r6, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip]
16 occurrences: str r1, [ip] -> str r7, [ip, #4]
15 occurrences: mov r3, r6 -> ldr r2, [r5, #48]
15 occurrences: @ <UNDEFINED> instruction: 0xe7d8abf4 -> mov fp, r1
14 occurrences: bic ip, ip, #16646144 -> cmp r3, ip
12 occurrences: ldr r0, [sp] -> ldr r1, [sp, #4]
12 occurrences: add sp, sp, #8 -> bx r0
12 occurrences: mov r2, r6 -> ldr r1, [r5, #48]
12 occurrences: ldr r0, [sp] -> ldr r1, [sp, #12]
12 occurrences: ldr r1, [r4] -> ldr r0, [r5, #48]
12 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48]
12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1
12 occurrences: mov r6, r1 -> add r1, r1, #4
12 occurrences: add r1, r1, #4 -> mov r8, r2
11 occurrences: str r0, [sp] -> ldr r6, [r4]
11 occurrences: ldr r0, [r4] -> ldr r1, [r4, #4]
11 occurrences: cmp r1, ip -> bhi 0x3fa8
10 occurrences: ldr r2, [r4] -> ldr r1, [r5, #48]
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432
10 occurrences: cmp r3, ip -> bhi 0x3fa8
10 occurrences: udf #15920 -> bcs 0x3fa8
10 occurrences: cmp r1, ip -> bhi 0x6d4c
175 occurrences: blx ip
161 occurrences: cmp r0, #0
119 occurrences: mov r1, r4
119 occurrences: ldr r2, [sp]
112 occurrences: add sp, sp, #4
111 occurrences: andeq r8, r4, ip, lsl #18
85 occurrences: ldr r1, [r5, #48]
77 occurrences: ldr r2, [r5, #48]
73 occurrences: str r0, [sp]
68 occurrences: bhi 0x4b74
63 occurrences: sub sp, sp, #4
61 occurrences: mov lr, #0
53 occurrences: mvn ip, #-33554432
53 occurrences: bic ip, ip, #16646144
51 occurrences: ldr r0, [r5, #48]
51 occurrences: ldr r6, [r5, #48]
46 occurrences: bcs 0x3fa8
45 occurrences: ldr r0, [sp]
45 occurrences: bx r0
45 occurrences: andeq r8, r4, r4
40 occurrences: push {lr}
40 occurrences: pop {pc}
40 occurrences: bhi 0x6d4c
39 occurrences: ldr r3, [r5, #48]
39 occurrences: cmp r3, ip
39 occurrences: cmp r8, ip
37 occurrences: cmp r1, ip
36 occurrences: ldr r1, [sp]
36 occurrences: str r0, [r1, #16]
36 occurrences: ldr sl, [r5, #48]
36 occurrences: bcs 0x135c
34 occurrences: mov r1, r0
34 occurrences: cmp r7, ip
33 occurrences: cmp ip, #0
33 occurrences: ldr r8, [r5, #48]
32 occurrences: mov r0, #8
32 occurrences: ldr r7, [r5, #48]
32 occurrences: bhi 0x3fa8
32 occurrences: bne 0x6d58
31 occurrences: ldr ip, [r4, #28]
31 occurrences: mvn lr, #-33554432
31 occurrences: bic lr, lr, #16646144
30 occurrences: cmp r6, ip
28 occurrences: @ <UNDEFINED> instruction: 0xe7e012f4
26 occurrences: str r0, [r4]
25 occurrences: add sp, sp, #8
24 occurrences: mov r7, r2
24 occurrences: mov r8, r0
23 occurrences: ldr ip, [r4, #20]
23 occurrences: bne 0x3fb4
22 occurrences: cmp r0, ip
22 occurrences: str lr, [r4, #4]
22 occurrences: ldr ip, [r4, #64]
21 occurrences: ldr r0, [r4]
21 occurrences: mov ip, #0
20 occurrences: mov r6, r0
20 occurrences: mov fp, r1
19 occurrences: @ <UNDEFINED> instruction: 0xe7e123f4
19 occurrences: mov r2, #0
19 occurrences: mov r2, r0
19 occurrences: mov r8, r2
19 occurrences: ldr ip, [r4, #80]
19 occurrences: ldr ip, [r4, #84]
18 occurrences: mov r3, r1
18 occurrences: bcs 0xaa8
18 occurrences: mov lr, #1
18 occurrences: ldr ip, [r4, #16]
18 occurrences: str r1, [ip]
18 occurrences: mov r6, r1
17 occurrences: mov r2, r6
17 occurrences: mov lr, #64, 22
17 occurrences: cmp r2, ip
17 occurrences: mov r2, r1
17 occurrences: mov r3, r0
17 occurrences: cmp r1, #0
17 occurrences: mov fp, r6
17 occurrences: mov r1, #0
17 occurrences: bcs 0x2860
17 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4
17 occurrences: @ <UNDEFINED> instruction: 0xe7d178f4
17 occurrences: b 0x4b6c
16 occurrences: @ <UNDEFINED> instruction: 0xe7e8abf4
16 occurrences: @ <UNDEFINED> instruction: 0xe7d8abf4
16 occurrences: add ip, r6, r8
16 occurrences: str r7, [ip, #4]
15 occurrences: mov r0, #0
15 occurrences: mov r3, r6
15 occurrences: mov r7, #0
15 occurrences: str lr, [r4, #92]
14 occurrences: mov r3, #0
14 occurrences: add r1, r1, #4
14 occurrences: bhi 0x1728
14 occurrences: str lr, [r4, #52]
14 occurrences: ldr r3, [r4, #28]
14 occurrences: str lr, [r4, #84]
14 occurrences: ldr r2, [r4, #28]
14 occurrences: ldr ip, [r4, #72]
13 occurrences: ldr r1, [sp, #12]
13 occurrences: cmp r6, #0
13 occurrences: ldr ip, [r4, #12]
13 occurrences: mov r6, r7
13 occurrences: str lr, [r4, #40]
13 occurrences: str lr, [r4, #164]
12 occurrences: ldr r1, [sp, #4]
12 occurrences: ldr lr, [r5, #60]
12 occurrences: str r6, [r4]
12 occurrences: ldr r1, [r4, #4]
12 occurrences: mov r0, r1
12 occurrences: bcs 0x1728
12 occurrences: ldr r1, [r4]
12 occurrences: ldr ip, [r4, #44]
12 occurrences: bcs 0x6d4c
11 occurrences: mov r6, #0
11 occurrences: ldr r6, [r4]
11 occurrences: str lr, [r4, #44]
11 occurrences: udf #15920
11 occurrences: cmp r2, #0
11 occurrences: mov sl, r1
11 occurrences: ldr r2, [r4]
11 occurrences: mvn lr, #0
11 occurrences: mov r7, r0
11 occurrences: str lr, [r4, #36]
11 occurrences: mov lr, #32
10 occurrences: @ <UNDEFINED> instruction: 0xe7d201f4
10 occurrences: ldr r1, [r5, #60]
10 occurrences: ldr r0, [r4, #4]
10 occurrences: str lr, [r4, #16]
10 occurrences: str lr, [r4]
10 occurrences: ldr r2, [r4, #8]
10 occurrences: cmp r9, ip
10 occurrences: bhi 0x135c
10 occurrences: ldr ip, [r4, #24]
10 occurrences: ldr ip, [r4]
10 occurrences: ldr r1, [ip]
[END] Finished processing log file: square-2026-04-28-21:54:07.bin.log

18 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
38 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
19 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
14 occurrences: push {lr} -> sub sp, sp, #4 -> str r0, [sp] -> mov lr, r5
12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
12 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
45 occurrences: push {lr} -> sub sp, sp, #4 -> str r0, [sp]
42 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
38 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16]
19 occurrences: str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
17 occurrences: str r0, [sp] -> ldr r0, [r4] -> ldr r1, [r4, #4]
16 occurrences: @ <UNDEFINED> instruction: 0xe7e8abf4 -> mov fp, r6 -> ldr sl, [r5, #48]
15 occurrences: sub sp, sp, #4 -> str r0, [sp] -> ldr r0, [r4]
15 occurrences: @ <UNDEFINED> instruction: 0xe7d8abf4 -> mov fp, r1 -> ldr sl, [r5, #48]
15 occurrences: add ip, r6, r8 -> str r1, [ip] -> str r7, [ip, #4]
14 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r3, ip
14 occurrences: sub sp, sp, #4 -> str r0, [sp] -> mov lr, r5
12 occurrences: push {r6, lr} -> sub sp, sp, #8 -> str r0, [sp]
12 occurrences: ldr r6, [sp, #8] -> add sp, sp, #16 -> bx r0
12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1 -> add r1, r1, #4
12 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
12 occurrences: add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
11 occurrences: sub sp, sp, #8 -> str r0, [sp] -> ldr r0, [r4]
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432 -> bic ip, ip, #16646144
119 occurrences: mov r1, r4 -> ldr r2, [sp]
66 occurrences: sub sp, sp, #4 -> str r0, [sp]
53 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144
45 occurrences: push {lr} -> sub sp, sp, #4
45 occurrences: add sp, sp, #4 -> pop {pc}
42 occurrences: ldr r1, [sp] -> str r0, [r1, #16]
42 occurrences: str r0, [r1, #16] -> ldr r0, [sp]
38 occurrences: mov r0, #8 -> ldr r1, [sp]
33 occurrences: cmp r8, ip -> bhi 0x58d8
32 occurrences: mov r2, r6 -> ldr r1, [r5, #48]
32 occurrences: cmp r0, #0 -> bne 0x7ad0
31 occurrences: mvn lr, #-33554432 -> bic lr, lr, #16646144
27 occurrences: add sp, sp, #4 -> bx r0
26 occurrences: str r0, [sp] -> ldr r0, [r4]
23 occurrences: mov r3, r6 -> ldr r2, [r5, #48]
23 occurrences: cmp r0, #0 -> bne 0x4d18
22 occurrences: mov r3, r2 -> ldr r1, [r5, #48]
20 occurrences: ldr r0, [sp] -> ldr r1, [sp, #12]
19 occurrences: cmp r7, ip -> bhi 0x58d8
18 occurrences: mov r7, r2 -> ldr r6, [r5, #48]
17 occurrences: ldr r0, [r4] -> ldr r1, [r4, #4]
17 occurrences: mov fp, r1 -> ldr sl, [r5, #48]
17 occurrences: mov r8, r2 -> ldr r7, [r5, #48]
16 occurrences: sub sp, sp, #8 -> str r0, [sp]
16 occurrences: @ <UNDEFINED> instruction: 0xe7e8abf4 -> mov fp, r6
16 occurrences: mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: @ <UNDEFINED> instruction: 0xe7d178f4 -> ldr r8, [r5, #48]
16 occurrences: cmp r6, ip -> bhi 0x58d8
16 occurrences: mov r8, r0 -> ldr r6, [r5, #48]
16 occurrences: str r1, [ip] -> str r7, [ip, #4]
15 occurrences: @ <UNDEFINED> instruction: 0xe7d8abf4 -> mov fp, r1
15 occurrences: add ip, r6, r8 -> str r1, [ip]
14 occurrences: bic ip, ip, #16646144 -> cmp r3, ip
14 occurrences: str r0, [sp] -> mov lr, r5
12 occurrences: push {r6, lr} -> sub sp, sp, #8
12 occurrences: add sp, sp, #8 -> pop {r6, pc}
12 occurrences: ldr r6, [sp, #8] -> add sp, sp, #16
12 occurrences: add sp, sp, #16 -> bx r0
12 occurrences: ldr r1, [r4] -> ldr r0, [r5, #48]
12 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48]
12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1
12 occurrences: mov r6, r1 -> add r1, r1, #4
12 occurrences: add r1, r1, #4 -> mov r8, r2
11 occurrences: ldr r0, [sp] -> ldr r1, [sp, #4]
11 occurrences: add sp, sp, #8 -> bx r0
11 occurrences: mov r2, #0 -> @ <UNDEFINED> instruction: 0xe7d201f4
11 occurrences: str r0, [sp] -> ldr r6, [r4]
11 occurrences: cmp r1, ip -> bhi 0x4d0c
10 occurrences: mov r3, r0 -> ldr r2, [r5, #48]
10 occurrences: ldr r2, [r4] -> ldr r1, [r5, #48]
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432
10 occurrences: cmp r3, ip -> bhi 0x4d0c
10 occurrences: udf #15920 -> bcs 0x4d0c
10 occurrences: cmp r1, ip -> bhi 0x7ac4
183 occurrences: blx ip
162 occurrences: cmp r0, #0
128 occurrences: ldr r1, [r5, #48]
120 occurrences: mov r1, r4
120 occurrences: ldr r2, [sp]
117 occurrences: add sp, sp, #4
111 occurrences: andeq r8, r4, ip, lsl #18
89 occurrences: ldr r2, [r5, #48]
85 occurrences: str r0, [sp]
68 occurrences: sub sp, sp, #4
68 occurrences: bhi 0x58d8
66 occurrences: ldr r0, [r5, #48]
61 occurrences: mov lr, #0
56 occurrences: ldr r3, [r5, #48]
53 occurrences: mvn ip, #-33554432
53 occurrences: bic ip, ip, #16646144
51 occurrences: ldr r0, [sp]
51 occurrences: bx r0
51 occurrences: andeq r8, r4, r4
51 occurrences: ldr r6, [r5, #48]
46 occurrences: bcs 0x4d0c
45 occurrences: push {lr}
45 occurrences: pop {pc}
44 occurrences: bcs 0x7b4
42 occurrences: cmp r3, ip
42 occurrences: ldr r1, [sp]
42 occurrences: str r0, [r1, #16]
41 occurrences: @ <UNDEFINED> instruction: 0xe7e012f4
40 occurrences: bhi 0x7ac4
39 occurrences: cmp r8, ip
38 occurrences: cmp r1, ip
38 occurrences: mov r0, #8
37 occurrences: mov r2, r6
37 occurrences: cmp r7, ip
36 occurrences: ldr sl, [r5, #48]
36 occurrences: bcs 0x1fa8
34 occurrences: mov r3, r2
34 occurrences: mov r1, r0
33 occurrences: cmp ip, #0
33 occurrences: ldr r8, [r5, #48]
32 occurrences: str r0, [r4]
32 occurrences: ldr r7, [r5, #48]
32 occurrences: bhi 0x4d0c
32 occurrences: bne 0x7ad0
31 occurrences: add sp, sp, #8
31 occurrences: ldr ip, [r4, #28]
31 occurrences: mvn lr, #-33554432
31 occurrences: bic lr, lr, #16646144
30 occurrences: cmp r6, ip
27 occurrences: ldr r0, [r4]
25 occurrences: @ <UNDEFINED> instruction: 0xe7e123f4
25 occurrences: mov r7, r2
24 occurrences: mov r2, #0
24 occurrences: mov r3, r6
24 occurrences: mov r8, r0
23 occurrences: cmp r0, ip
23 occurrences: ldr ip, [r4, #20]
23 occurrences: bne 0x4d18
22 occurrences: cmp r2, ip
22 occurrences: str lr, [r4, #4]
22 occurrences: ldr ip, [r4, #64]
21 occurrences: mov r0, #0
21 occurrences: str r1, [ip]
21 occurrences: mov ip, #0
20 occurrences: mov r2, r1
20 occurrences: mov r2, r0
20 occurrences: ldr r1, [sp, #12]
20 occurrences: mov r6, r0
20 occurrences: mov fp, r1
19 occurrences: mov r3, r0
19 occurrences: mov r6, r1
19 occurrences: mov r8, r2
19 occurrences: ldr ip, [r4, #80]
19 occurrences: ldr ip, [r4, #84]
18 occurrences: ldr lr, [r5, #60]
18 occurrences: mov r3, r1
18 occurrences: ldr r1, [r4, #4]
18 occurrences: @ <UNDEFINED> instruction: 0xe7e013f4
18 occurrences: bcs 0x1800
18 occurrences: mov lr, #1
18 occurrences: ldr ip, [r4, #16]
17 occurrences: mov lr, #64, 22
17 occurrences: bcs 0xe3c
17 occurrences: cmp r1, #0
17 occurrences: mov fp, r6
17 occurrences: mov r1, #0
17 occurrences: bcs 0x35a4
17 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4
17 occurrences: @ <UNDEFINED> instruction: 0xe7d178f4
17 occurrences: b 0x58d0
16 occurrences: @ <UNDEFINED> instruction: 0xe7d201f4
16 occurrences: sub sp, sp, #8
16 occurrences: @ <UNDEFINED> instruction: 0xe7e8abf4
16 occurrences: @ <UNDEFINED> instruction: 0xe7d8abf4
16 occurrences: add ip, r6, r8
16 occurrences: str r7, [ip, #4]
15 occurrences: mov r6, r2
15 occurrences: mov r7, #0
15 occurrences: str lr, [r4, #92]
14 occurrences: @ <UNDEFINED> instruction: 0xe7d012f4
14 occurrences: mov r3, #0
14 occurrences: add r1, r1, #4
14 occurrences: bhi 0x2448
14 occurrences: str lr, [r4, #52]
14 occurrences: ldr r3, [r4, #28]
14 occurrences: str lr, [r4, #84]
14 occurrences: ldr r2, [r4, #28]
14 occurrences: ldr ip, [r4, #72]
14 occurrences: mov lr, r5
13 occurrences: mov r7, r0
13 occurrences: ldr r1, [ip]
13 occurrences: mov r0, r1
13 occurrences: push {r6, lr}
13 occurrences: pop {r6, pc}
13 occurrences: add sp, sp, #16
13 occurrences: cmp r6, #0
13 occurrences: ldr ip, [r4, #12]
13 occurrences: mov r6, r7
13 occurrences: str lr, [r4, #40]
13 occurrences: str lr, [r4, #164]
12 occurrences: udf #15920
12 occurrences: @ <UNDEFINED> instruction: 0xe7e023f4
12 occurrences: udf #15884
12 occurrences: str r6, [r4]
12 occurrences: ldr r6, [sp, #8]
12 occurrences: bcs 0x2448
12 occurrences: ldr r1, [r4]
12 occurrences: ldr ip, [r4, #44]
12 occurrences: bcs 0x7ac4
11 occurrences: ldr r1, [sp, #4]
11 occurrences: bhi 0x7b4
11 occurrences: add r0, r0, r1
11 occurrences: mov r6, #0
11 occurrences: ldr r6, [r4]
11 occurrences: str lr, [r4, #44]
11 occurrences: cmp r2, #0
11 occurrences: mov sl, r1
11 occurrences: ldr r2, [r4]
11 occurrences: mvn lr, #0
11 occurrences: str lr, [r4, #36]
11 occurrences: mov lr, #32
10 occurrences: ldr r1, [r5, #60]
10 occurrences: udf #15880
10 occurrences: ldr r0, [r4, #4]
10 occurrences: str lr, [r4, #16]
10 occurrences: str lr, [r4]
10 occurrences: ldr r2, [r4, #8]
10 occurrences: cmp r9, ip
10 occurrences: bhi 0x1fa8
10 occurrences: ldr ip, [r4, #24]
10 occurrences: ldr ip, [r4]
[END] Finished processing log file: dispatcher-2026-04-28-21:54:05.bin.log

11 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
11 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
31 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
12 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
11 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
11 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
39 occurrences: push {lr} -> sub sp, sp, #4 -> str r0, [sp]
35 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
31 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16]
16 occurrences: @ <UNDEFINED> instruction: 0xe7e8abf4 -> mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip] -> str r7, [ip, #4]
15 occurrences: sub sp, sp, #4 -> str r0, [sp] -> ldr r0, [r4]
15 occurrences: @ <UNDEFINED> instruction: 0xe7d8abf4 -> mov fp, r1 -> ldr sl, [r5, #48]
14 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r3, ip
12 occurrences: str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1 -> add r1, r1, #4
11 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
11 occurrences: add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
10 occurrences: str r0, [sp] -> ldr r0, [r4] -> ldr r1, [r4, #4]
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432 -> bic ip, ip, #16646144
118 occurrences: mov r1, r4 -> ldr r2, [sp]
59 occurrences: sub sp, sp, #4 -> str r0, [sp]
53 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144
39 occurrences: push {lr} -> sub sp, sp, #4
39 occurrences: add sp, sp, #4 -> pop {pc}
35 occurrences: ldr r1, [sp] -> str r0, [r1, #16]
35 occurrences: str r0, [r1, #16] -> ldr r0, [sp]
33 occurrences: cmp r8, ip -> bhi 0x4a3c
32 occurrences: cmp r0, #0 -> bne 0x6c34
31 occurrences: mov r0, #8 -> ldr r1, [sp]
30 occurrences: mvn lr, #-33554432 -> bic lr, lr, #16646144
26 occurrences: add sp, sp, #4 -> bx r0
23 occurrences: cmp r0, #0 -> bne 0x3e7c
19 occurrences: str r0, [sp] -> ldr r0, [r4]
19 occurrences: cmp r7, ip -> bhi 0x4a3c
18 occurrences: mov r7, r2 -> ldr r6, [r5, #48]
17 occurrences: mov fp, r1 -> ldr sl, [r5, #48]
17 occurrences: mov r8, r2 -> ldr r7, [r5, #48]
16 occurrences: @ <UNDEFINED> instruction: 0xe7e8abf4 -> mov fp, r6
16 occurrences: mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: @ <UNDEFINED> instruction: 0xe7d178f4 -> ldr r8, [r5, #48]
16 occurrences: cmp r6, ip -> bhi 0x4a3c
16 occurrences: mov r8, r0 -> ldr r6, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip]
16 occurrences: str r1, [ip] -> str r7, [ip, #4]
15 occurrences: mov r3, r6 -> ldr r2, [r5, #48]
15 occurrences: @ <UNDEFINED> instruction: 0xe7d8abf4 -> mov fp, r1
14 occurrences: bic ip, ip, #16646144 -> cmp r3, ip
13 occurrences: ldr r0, [sp] -> ldr r1, [sp, #12]
12 occurrences: ldr r1, [r4] -> ldr r0, [r5, #48]
12 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48]
12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1
12 occurrences: mov r6, r1 -> add r1, r1, #4
11 occurrences: ldr r0, [sp] -> ldr r1, [sp, #4]
11 occurrences: add sp, sp, #8 -> bx r0
11 occurrences: str r0, [sp] -> ldr r6, [r4]
11 occurrences: cmp r1, ip -> bhi 0x3e70
11 occurrences: add r1, r1, #4 -> mov r8, r2
10 occurrences: sub sp, sp, #8 -> str r0, [sp]
10 occurrences: ldr r0, [r4] -> ldr r1, [r4, #4]
10 occurrences: mov r2, r6 -> ldr r1, [r5, #48]
10 occurrences: ldr r2, [r4] -> ldr r1, [r5, #48]
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432
10 occurrences: cmp r3, ip -> bhi 0x3e70
10 occurrences: udf #15920 -> bcs 0x3e70
10 occurrences: cmp r1, ip -> bhi 0x6c28
173 occurrences: blx ip
160 occurrences: cmp r0, #0
118 occurrences: mov r1, r4
118 occurrences: ldr r2, [sp]
110 occurrences: andeq r8, r4, ip, lsl #18
108 occurrences: add sp, sp, #4
83 occurrences: ldr r1, [r5, #48]
74 occurrences: ldr r2, [r5, #48]
72 occurrences: str r0, [sp]
68 occurrences: bhi 0x4a3c
62 occurrences: mov lr, #0
61 occurrences: sub sp, sp, #4
53 occurrences: mvn ip, #-33554432
53 occurrences: bic ip, ip, #16646144
51 occurrences: ldr r6, [r5, #48]
48 occurrences: ldr r0, [r5, #48]
46 occurrences: bcs 0x3e70
44 occurrences: ldr r0, [sp]
44 occurrences: bx r0
44 occurrences: andeq r8, r4, r4
40 occurrences: bhi 0x6c28
39 occurrences: push {lr}
39 occurrences: pop {pc}
39 occurrences: ldr r3, [r5, #48]
39 occurrences: cmp r3, ip
39 occurrences: cmp r8, ip
36 occurrences: ldr sl, [r5, #48]
36 occurrences: bcs 0x1210
36 occurrences: cmp r1, ip
35 occurrences: ldr r1, [sp]
35 occurrences: str r0, [r1, #16]
34 occurrences: mov r1, r0
34 occurrences: cmp r7, ip
33 occurrences: cmp ip, #0
33 occurrences: ldr r8, [r5, #48]
32 occurrences: ldr r7, [r5, #48]
32 occurrences: bhi 0x3e70
32 occurrences: bne 0x6c34
31 occurrences: mov r0, #8
31 occurrences: ldr ip, [r4, #28]
31 occurrences: mvn lr, #-33554432
31 occurrences: bic lr, lr, #16646144
30 occurrences: cmp r6, ip
27 occurrences: @ <UNDEFINED> instruction: 0xe7e012f4
26 occurrences: str r0, [r4]
25 occurrences: add sp, sp, #8
24 occurrences: mov r7, r2
24 occurrences: mov r8, r0
23 occurrences: ldr ip, [r4, #20]
23 occurrences: bne 0x3e7c
22 occurrences: cmp r0, ip
22 occurrences: str lr, [r4, #4]
22 occurrences: ldr ip, [r4, #64]
21 occurrences: mov ip, #0
20 occurrences: mov r6, r0
20 occurrences: ldr r0, [r4]
20 occurrences: mov fp, r1
19 occurrences: mov r2, #0
19 occurrences: mov r2, r0
19 occurrences: mov r8, r2
19 occurrences: ldr ip, [r4, #80]
19 occurrences: ldr ip, [r4, #84]
18 occurrences: bcs 0x964
18 occurrences: @ <UNDEFINED> instruction: 0xe7e123f4
18 occurrences: mov lr, #1
18 occurrences: ldr ip, [r4, #16]
18 occurrences: str r1, [ip]
18 occurrences: mov r6, r1
17 occurrences: mov lr, #64, 22
17 occurrences: cmp r2, ip
17 occurrences: mov r2, r1
17 occurrences: mov r3, r0
17 occurrences: cmp r1, #0
17 occurrences: mov fp, r6
17 occurrences: mov r1, #0
17 occurrences: bcs 0x2730
17 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4
17 occurrences: @ <UNDEFINED> instruction: 0xe7d178f4
17 occurrences: b 0x4a34
16 occurrences: @ <UNDEFINED> instruction: 0xe7e8abf4
16 occurrences: @ <UNDEFINED> instruction: 0xe7d8abf4
16 occurrences: add ip, r6, r8
16 occurrences: str r7, [ip, #4]
15 occurrences: mov r0, #0
15 occurrences: mov r3, r6
15 occurrences: mov r2, r6
15 occurrences: mov r3, r1
15 occurrences: mov r7, #0
15 occurrences: str lr, [r4, #92]
14 occurrences: mov r3, #0
14 occurrences: add r1, r1, #4
14 occurrences: bhi 0x15e0
14 occurrences: str lr, [r4, #52]
14 occurrences: ldr r3, [r4, #28]
14 occurrences: str lr, [r4, #84]
14 occurrences: ldr r2, [r4, #28]
14 occurrences: ldr ip, [r4, #72]
13 occurrences: ldr r1, [sp, #12]
13 occurrences: cmp r6, #0
13 occurrences: ldr ip, [r4, #12]
13 occurrences: mov r6, r7
13 occurrences: str lr, [r4, #40]
13 occurrences: str lr, [r4, #164]
12 occurrences: ldr r1, [r4, #4]
12 occurrences: mov r0, r1
12 occurrences: bcs 0x15e0
12 occurrences: ldr r1, [r4]
12 occurrences: ldr ip, [r4, #44]
12 occurrences: bcs 0x6c28
11 occurrences: ldr r1, [sp, #4]
11 occurrences: ldr lr, [r5, #60]
11 occurrences: str lr, [r4, #16]
11 occurrences: mov r6, #0
11 occurrences: ldr r6, [r4]
11 occurrences: str r6, [r4]
11 occurrences: str lr, [r4, #44]
11 occurrences: udf #15920
11 occurrences: cmp r2, #0
11 occurrences: mov sl, r1
11 occurrences: ldr r2, [r4]
11 occurrences: mvn lr, #0
11 occurrences: mov r7, r0
11 occurrences: str lr, [r4, #36]
11 occurrences: mov lr, #32
10 occurrences: sub sp, sp, #8
10 occurrences: ldr r1, [r5, #60]
10 occurrences: str r0, [r4, #4]
10 occurrences: ldr r0, [r4, #4]
10 occurrences: str lr, [r4]
10 occurrences: ldr r2, [r4, #8]
10 occurrences: cmp r9, ip
10 occurrences: bhi 0x1210
10 occurrences: ldr ip, [r4, #24]
10 occurrences: ldr ip, [r4]
10 occurrences: ldr r1, [ip]
[END] Finished processing log file: helloworld-2026-04-28-21:54:06.bin.log

13 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
34 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
14 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
12 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
10 occurrences: sub sp, sp, #4 -> str r0, [sp] -> ldr r0, [r4] -> ldr r1, [r4, #4]
10 occurrences: str r0, [sp] -> ldr r0, [r4] -> ldr r1, [r4, #4] -> ldr r2, [r4, #8]
40 occurrences: push {lr} -> sub sp, sp, #4 -> str r0, [sp]
38 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
34 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16]
17 occurrences: sub sp, sp, #4 -> str r0, [sp] -> ldr r0, [r4]
16 occurrences: @ <UNDEFINED> instruction: 0xe7e8abf4 -> mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip] -> str r7, [ip, #4]
15 occurrences: @ <UNDEFINED> instruction: 0xe7d8abf4 -> mov fp, r1 -> ldr sl, [r5, #48]
14 occurrences: str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
14 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r3, ip
13 occurrences: str r0, [sp] -> ldr r0, [r4] -> ldr r1, [r4, #4]
12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1 -> add r1, r1, #4
12 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
12 occurrences: add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
10 occurrences: ldr r0, [r4] -> ldr r1, [r4, #4] -> ldr r2, [r4, #8]
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432 -> bic ip, ip, #16646144
124 occurrences: mov r1, r4 -> ldr r2, [sp]
62 occurrences: sub sp, sp, #4 -> str r0, [sp]
53 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144
40 occurrences: push {lr} -> sub sp, sp, #4
40 occurrences: add sp, sp, #4 -> pop {pc}
38 occurrences: ldr r1, [sp] -> str r0, [r1, #16]
38 occurrences: str r0, [r1, #16] -> ldr r0, [sp]
34 occurrences: mov r0, #8 -> ldr r1, [sp]
33 occurrences: cmp r8, ip -> bhi 0x5648
32 occurrences: cmp r0, #0 -> bne 0x7850
31 occurrences: mov r3, r6 -> ldr r2, [r5, #48]
31 occurrences: mvn lr, #-33554432 -> bic lr, lr, #16646144
28 occurrences: add sp, sp, #4 -> bx r0
26 occurrences: mov r2, r6 -> ldr r1, [r5, #48]
23 occurrences: mov r1, r6 -> ldr r0, [r5, #48]
23 occurrences: cmp r0, #0 -> bne 0x4a94
22 occurrences: str r0, [sp] -> ldr r0, [r4]
18 occurrences: mov r7, r2 -> ldr r6, [r5, #48]
18 occurrences: cmp r7, ip -> bhi 0x5648
17 occurrences: mov fp, r1 -> ldr sl, [r5, #48]
17 occurrences: mov r8, r2 -> ldr r7, [r5, #48]
16 occurrences: @ <UNDEFINED> instruction: 0xe7e8abf4 -> mov fp, r6
16 occurrences: mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: @ <UNDEFINED> instruction: 0xe7d178f4 -> ldr r8, [r5, #48]
16 occurrences: cmp r6, ip -> bhi 0x5648
16 occurrences: mov r8, r0 -> ldr r6, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip]
16 occurrences: str r1, [ip] -> str r7, [ip, #4]
15 occurrences: ldr r0, [sp] -> ldr r1, [sp, #12]
15 occurrences: @ <UNDEFINED> instruction: 0xe7d8abf4 -> mov fp, r1
14 occurrences: bic ip, ip, #16646144 -> cmp r3, ip
13 occurrences: ldr r0, [r4] -> ldr r1, [r4, #4]
12 occurrences: sub sp, sp, #8 -> str r0, [sp]
12 occurrences: ldr lr, [ip] -> ldr ip, [ip, #4]
12 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48]
12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1
12 occurrences: mov r6, r1 -> add r1, r1, #4
12 occurrences: add r1, r1, #4 -> mov r8, r2
11 occurrences: ldr r0, [sp] -> ldr r1, [sp, #4]
11 occurrences: add sp, sp, #8 -> bx r0
11 occurrences: str r0, [sp] -> ldr r6, [r4]
11 occurrences: ldr r1, [r4] -> ldr r0, [r5, #48]
11 occurrences: cmp r1, ip -> bhi 0x4a88
10 occurrences: ldr r1, [r4, #4] -> ldr r2, [r4, #8]
10 occurrences: ldr r0, [sp] -> ldr r1, [sp, #20]
10 occurrences: ldr r2, [r4] -> ldr r1, [r5, #48]
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432
10 occurrences: cmp r3, ip -> bhi 0x4a88
10 occurrences: udf #15920 -> bcs 0x4a88
10 occurrences: cmp r1, ip -> bhi 0x7844
182 occurrences: blx ip
166 occurrences: cmp r0, #0
124 occurrences: mov r1, r4
124 occurrences: ldr r2, [sp]
116 occurrences: andeq r8, r4, ip, lsl #18
114 occurrences: add sp, sp, #4
100 occurrences: ldr r1, [r5, #48]
95 occurrences: ldr r2, [r5, #48]
77 occurrences: str r0, [sp]
72 occurrences: ldr r0, [r5, #48]
68 occurrences: bhi 0x5648
64 occurrences: sub sp, sp, #4
61 occurrences: mov lr, #0
53 occurrences: mvn ip, #-33554432
53 occurrences: bic ip, ip, #16646144
52 occurrences: ldr r6, [r5, #48]
47 occurrences: ldr r0, [sp]
47 occurrences: bx r0
47 occurrences: andeq r8, r4, r4
46 occurrences: bcs 0x4a88
43 occurrences: ldr r3, [r5, #48]
40 occurrences: push {lr}
40 occurrences: pop {pc}
40 occurrences: cmp r1, ip
40 occurrences: bhi 0x7844
39 occurrences: cmp r3, ip
39 occurrences: cmp r8, ip
38 occurrences: ldr r1, [sp]
38 occurrences: str r0, [r1, #16]
38 occurrences: @ <UNDEFINED> instruction: 0xe7e012f4
36 occurrences: ldr sl, [r5, #48]
36 occurrences: bcs 0x1da4
34 occurrences: mov r0, #8
34 occurrences: ldr r7, [r5, #48]
34 occurrences: mov r1, r0
34 occurrences: cmp r7, ip
33 occurrences: bcs 0xc0c
33 occurrences: cmp ip, #0
33 occurrences: ldr r8, [r5, #48]
32 occurrences: mov r2, r6
32 occurrences: bhi 0x4a88
32 occurrences: bne 0x7850
31 occurrences: mov r3, r6
31 occurrences: cmp r6, ip
31 occurrences: ldr ip, [r4, #28]
31 occurrences: mvn lr, #-33554432
31 occurrences: bic lr, lr, #16646144
28 occurrences: add sp, sp, #8
26 occurrences: str r0, [r4]
24 occurrences: @ <UNDEFINED> instruction: 0xe7e123f4
24 occurrences: mov r7, r2
24 occurrences: mov r8, r0
23 occurrences: mov r1, r6
23 occurrences: mov r2, #0
23 occurrences: mov ip, #0
23 occurrences: ldr r0, [r4]
23 occurrences: ldr ip, [r4, #20]
23 occurrences: bne 0x4a94
22 occurrences: cmp r0, ip
22 occurrences: str lr, [r4, #4]
22 occurrences: ldr ip, [r4, #64]
21 occurrences: mov r2, r0
20 occurrences: mov r1, #0
20 occurrences: cmp r2, ip
20 occurrences: mov r6, r0
20 occurrences: mov fp, r1
19 occurrences: mov r0, #0
19 occurrences: mov r8, r2
19 occurrences: ldr ip, [r4, #80]
19 occurrences: ldr ip, [r4, #84]
18 occurrences: mov r2, r1
18 occurrences: bcs 0x1600
18 occurrences: mov lr, #1
18 occurrences: ldr ip, [r4, #16]
18 occurrences: str r1, [ip]
18 occurrences: mov r6, r1
17 occurrences: mov lr, #64, 22
17 occurrences: mov r3, r0
17 occurrences: cmp r1, #0
17 occurrences: mov fp, r6
17 occurrences: bcs 0x3358
17 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4
17 occurrences: @ <UNDEFINED> instruction: 0xe7d178f4
17 occurrences: b 0x5640
16 occurrences: mov r3, r1
16 occurrences: @ <UNDEFINED> instruction: 0xe7e8abf4
16 occurrences: @ <UNDEFINED> instruction: 0xe7d8abf4
16 occurrences: add ip, r6, r8
16 occurrences: str r7, [ip, #4]
15 occurrences: add ip, r0, r1
15 occurrences: ldr r1, [sp, #12]
15 occurrences: bcs 0x6e8
15 occurrences: ldr r3, [r4, #28]
15 occurrences: mov r3, #0
15 occurrences: mov r7, #0
15 occurrences: str lr, [r4, #92]
14 occurrences: ldr lr, [r5, #60]
14 occurrences: @ <UNDEFINED> instruction: 0xe7d201f4
14 occurrences: ldr r1, [r4, #4]
14 occurrences: add r1, r1, #4
14 occurrences: bhi 0x21f4
14 occurrences: str lr, [r4, #52]
14 occurrences: str lr, [r4, #84]
14 occurrences: ldr r2, [r4, #28]
14 occurrences: ldr ip, [r4, #72]
13 occurrences: udf #15920
13 occurrences: cmp r6, #0
13 occurrences: ldr ip, [r4, #12]
13 occurrences: mov r6, r7
13 occurrences: str lr, [r4, #40]
13 occurrences: str lr, [r4, #164]
12 occurrences: sub sp, sp, #8
12 occurrences: add r0, r0, r1
12 occurrences: ldr lr, [ip]
12 occurrences: ldr ip, [ip, #4]
12 occurrences: str r6, [r4]
12 occurrences: mov r0, r1
12 occurrences: bcs 0x21f4
12 occurrences: ldr r1, [r4]
12 occurrences: ldr ip, [r4, #44]
12 occurrences: bcs 0x7844
11 occurrences: ldr r1, [sp, #4]
11 occurrences: @ <UNDEFINED> instruction: 0xe7d012f4
11 occurrences: ldr r2, [r4, #8]
11 occurrences: mov r6, #0
11 occurrences: ldr r6, [r4]
11 occurrences: str lr, [r4, #44]
11 occurrences: cmp r2, #0
11 occurrences: mov sl, r1
11 occurrences: ldr r2, [r4]
11 occurrences: mvn lr, #0
11 occurrences: mov r7, r0
11 occurrences: str lr, [r4, #36]
11 occurrences: mov lr, #32
10 occurrences: bcs 0x3a4
10 occurrences: str lr, [ip]
10 occurrences: str lr, [ip, #4]
10 occurrences: str r0, [r4, #4]
10 occurrences: ldr r1, [r5, #60]
10 occurrences: ldr r1, [sp, #20]
10 occurrences: ldr r0, [r4, #4]
10 occurrences: str lr, [r4, #16]
10 occurrences: str lr, [r4]
10 occurrences: cmp r9, ip
10 occurrences: bhi 0x1da4
10 occurrences: ldr ip, [r4, #24]
10 occurrences: ldr ip, [r4]
10 occurrences: ldr r1, [ip]
[END] Finished processing log file: promote-2026-04-28-21:54:07.bin.log

12 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
32 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
13 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
12 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
12 occurrences: add ip, r6, r8 -> str r1, [ip] -> str r7, [ip, #4] -> mov r0, #64, 16
39 occurrences: push {lr} -> sub sp, sp, #4 -> str r0, [sp]
36 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
32 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16]
16 occurrences: @ <UNDEFINED> instruction: 0xe7e8abf4 -> mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip] -> str r7, [ip, #4]
15 occurrences: sub sp, sp, #4 -> str r0, [sp] -> ldr r0, [r4]
15 occurrences: @ <UNDEFINED> instruction: 0xe7d8abf4 -> mov fp, r1 -> ldr sl, [r5, #48]
14 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r3, ip
13 occurrences: ldr r1, [r5, #48] -> mvn lr, #-33554432 -> bic lr, lr, #16646144
13 occurrences: str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1 -> add r1, r1, #4
12 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
12 occurrences: add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
12 occurrences: str r1, [ip] -> str r7, [ip, #4] -> mov r0, #64, 16
11 occurrences: str r0, [sp] -> ldr r0, [r4] -> ldr r1, [r4, #4]
10 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r1, ip
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432 -> bic ip, ip, #16646144
119 occurrences: mov r1, r4 -> ldr r2, [sp]
59 occurrences: sub sp, sp, #4 -> str r0, [sp]
58 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144
44 occurrences: mvn lr, #-33554432 -> bic lr, lr, #16646144
40 occurrences: mov r2, r6 -> ldr r1, [r5, #48]
39 occurrences: push {lr} -> sub sp, sp, #4
39 occurrences: add sp, sp, #4 -> pop {pc}
36 occurrences: ldr r1, [sp] -> str r0, [r1, #16]
36 occurrences: str r0, [r1, #16] -> ldr r0, [sp]
33 occurrences: cmp r8, ip -> bhi 0x51d0
32 occurrences: mov r0, #8 -> ldr r1, [sp]
32 occurrences: cmp r0, #0 -> bne 0x73b8
30 occurrences: mov r3, r6 -> ldr r2, [r5, #48]
26 occurrences: add sp, sp, #4 -> bx r0
23 occurrences: cmp r0, #0 -> bne 0x46d0
19 occurrences: str r0, [sp] -> ldr r0, [r4]
19 occurrences: cmp r7, ip -> bhi 0x51d0
18 occurrences: mov r7, r2 -> ldr r6, [r5, #48]
17 occurrences: mov fp, r1 -> ldr sl, [r5, #48]
17 occurrences: mov r8, r2 -> ldr r7, [r5, #48]
16 occurrences: @ <UNDEFINED> instruction: 0xe7e8abf4 -> mov fp, r6
16 occurrences: mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: @ <UNDEFINED> instruction: 0xe7d178f4 -> ldr r8, [r5, #48]
16 occurrences: cmp r6, ip -> bhi 0x51d0
16 occurrences: mov r8, r0 -> ldr r6, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip]
16 occurrences: str r1, [ip] -> str r7, [ip, #4]
15 occurrences: @ <UNDEFINED> instruction: 0xe7d8abf4 -> mov fp, r1
14 occurrences: ldr r0, [sp] -> ldr r1, [sp, #12]
14 occurrences: bic ip, ip, #16646144 -> cmp r3, ip
13 occurrences: ldr r1, [r5, #48] -> mvn lr, #-33554432
12 occurrences: mov r3, r0 -> ldr r2, [r5, #48]
12 occurrences: ldr r1, [r4] -> ldr r0, [r5, #48]
12 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48]
12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1
12 occurrences: mov r6, r1 -> add r1, r1, #4
12 occurrences: add r1, r1, #4 -> mov r8, r2
12 occurrences: str r7, [ip, #4] -> mov r0, #64, 16
11 occurrences: ldr r0, [sp] -> ldr r1, [sp, #4]
11 occurrences: add sp, sp, #8 -> bx r0
11 occurrences: sub sp, sp, #8 -> str r0, [sp]
11 occurrences: str r0, [sp] -> ldr r6, [r4]
11 occurrences: ldr r0, [r4] -> ldr r1, [r4, #4]
11 occurrences: cmp r1, ip -> bhi 0x46c4
10 occurrences: bic ip, ip, #16646144 -> cmp r1, ip
10 occurrences: ldr r2, [r4] -> ldr r1, [r5, #48]
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432
10 occurrences: cmp r3, ip -> bhi 0x46c4
10 occurrences: udf #15920 -> bcs 0x46c4
10 occurrences: cmp r1, ip -> bhi 0x73ac
175 occurrences: blx ip
162 occurrences: cmp r0, #0
119 occurrences: mov r1, r4
119 occurrences: ldr r2, [sp]
116 occurrences: ldr r1, [r5, #48]
111 occurrences: andeq r8, r4, ip, lsl #18
108 occurrences: add sp, sp, #4
95 occurrences: ldr r2, [r5, #48]
73 occurrences: str r0, [sp]
68 occurrences: bhi 0x51d0
61 occurrences: sub sp, sp, #4
61 occurrences: mov lr, #0
58 occurrences: mvn ip, #-33554432
58 occurrences: bic ip, ip, #16646144
53 occurrences: bcs 0x7b0
52 occurrences: ldr r0, [r5, #48]
51 occurrences: ldr r6, [r5, #48]
46 occurrences: bcs 0x46c4
45 occurrences: ldr r0, [sp]
45 occurrences: bx r0
45 occurrences: mov r2, r6
45 occurrences: andeq r8, r4, r4
44 occurrences: mvn lr, #-33554432
44 occurrences: bic lr, lr, #16646144
42 occurrences: ldr r3, [r5, #48]
40 occurrences: bhi 0x73ac
39 occurrences: push {lr}
39 occurrences: pop {pc}
39 occurrences: @ <UNDEFINED> instruction: 0xe7e012f4
39 occurrences: cmp r3, ip
39 occurrences: cmp r8, ip
38 occurrences: cmp r1, ip
36 occurrences: ldr r1, [sp]
36 occurrences: str r0, [r1, #16]
36 occurrences: ldr sl, [r5, #48]
36 occurrences: bcs 0x19c4
35 occurrences: @ <UNDEFINED> instruction: 0xe7e123f4
34 occurrences: mov r1, r0
34 occurrences: cmp r7, ip
33 occurrences: cmp ip, #0
33 occurrences: ldr r8, [r5, #48]
32 occurrences: mov r0, #8
32 occurrences: ldr r7, [r5, #48]
32 occurrences: bhi 0x46c4
32 occurrences: bne 0x73b8
31 occurrences: ldr ip, [r4, #28]
30 occurrences: mov r3, r6
30 occurrences: cmp r6, ip
26 occurrences: add sp, sp, #8
26 occurrences: str r0, [r4]
24 occurrences: mov r7, r2
24 occurrences: mov r8, r0
23 occurrences: ldr ip, [r4, #20]
23 occurrences: bne 0x46d0
22 occurrences: mov r2, #0
22 occurrences: mov r2, r0
22 occurrences: mov r6, r0
22 occurrences: cmp r0, ip
22 occurrences: str lr, [r4, #4]
22 occurrences: ldr ip, [r4, #64]
21 occurrences: cmp r2, ip
21 occurrences: mov r3, r0
21 occurrences: mov ip, #0
20 occurrences: ldr r0, [r4]
20 occurrences: mov fp, r1
19 occurrences: mov r0, #0
19 occurrences: mov r8, r2
19 occurrences: ldr ip, [r4, #80]
19 occurrences: ldr ip, [r4, #84]
18 occurrences: mov r1, #0
18 occurrences: bcs 0x1214
18 occurrences: mov lr, #1
18 occurrences: ldr ip, [r4, #16]
18 occurrences: str r1, [ip]
18 occurrences: mov r6, r1
17 occurrences: mov lr, #64, 22
17 occurrences: mov r2, r1
17 occurrences: cmp r1, #0
17 occurrences: mov fp, r6
17 occurrences: bcs 0x2e88
17 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4
17 occurrences: @ <UNDEFINED> instruction: 0xe7d178f4
17 occurrences: b 0x51c8
16 occurrences: @ <UNDEFINED> instruction: 0xe7e8abf4
16 occurrences: @ <UNDEFINED> instruction: 0xe7d8abf4
16 occurrences: add ip, r6, r8
16 occurrences: str r7, [ip, #4]
16 occurrences: mov r0, #64, 16
15 occurrences: @ <UNDEFINED> instruction: 0xe7d012f4
15 occurrences: mov r3, #0
15 occurrences: mov r3, r1
15 occurrences: mov r7, #0
15 occurrences: str lr, [r4, #92]
14 occurrences: add r0, r0, r1
14 occurrences: ldr r1, [sp, #12]
14 occurrences: add r1, r1, #4
14 occurrences: bhi 0x1d90
14 occurrences: str lr, [r4, #52]
14 occurrences: ldr r3, [r4, #28]
14 occurrences: str lr, [r4, #84]
14 occurrences: ldr r2, [r4, #28]
14 occurrences: ldr ip, [r4, #72]
13 occurrences: @ <UNDEFINED> instruction: 0xe7d201f4
13 occurrences: cmp r6, #0
13 occurrences: ldr ip, [r4, #12]
13 occurrences: mov r6, r7
13 occurrences: str lr, [r4, #40]
13 occurrences: str lr, [r4, #164]
12 occurrences: ldr lr, [r5, #60]
12 occurrences: mov r0, #4161536
12 occurrences: str lr, [r4, #44]
12 occurrences: str r6, [r4]
12 occurrences: ldr r1, [r4, #4]
12 occurrences: mov r0, r1
12 occurrences: bcs 0x1d90
12 occurrences: ldr r1, [r4]
12 occurrences: ldr ip, [r4, #44]
12 occurrences: bcs 0x73ac
11 occurrences: ldr r1, [sp, #4]
11 occurrences: sub sp, sp, #8
11 occurrences: mov r6, #0
11 occurrences: ldr r6, [r4]
11 occurrences: udf #15920
11 occurrences: cmp r2, #0
11 occurrences: mov sl, r1
11 occurrences: ldr r2, [r4]
11 occurrences: mvn lr, #0
11 occurrences: mov r7, r0
11 occurrences: str lr, [r4, #36]
11 occurrences: mov lr, #32
10 occurrences: @ <UNDEFINED> instruction: 0xe7e012f0
10 occurrences: and r0, r0, #255
10 occurrences: udf #15908
10 occurrences: udf #11812
10 occurrences: ldr r1, [r5, #60]
10 occurrences: ldr r0, [r4, #4]
10 occurrences: str lr, [r4, #16]
10 occurrences: str lr, [r4]
10 occurrences: ldr r2, [r4, #8]
10 occurrences: cmp r9, ip
10 occurrences: bhi 0x19c4
10 occurrences: ldr ip, [r4, #24]
10 occurrences: ldr ip, [r4]
10 occurrences: ldr r1, [ip]
[END] Finished processing log file: memwalk-2026-04-28-21:54:06.bin.log

12 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
33 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
13 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
12 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
11 occurrences: sub sp, sp, #4 -> str r0, [sp] -> ldr r0, [r4] -> ldr r1, [r4, #4]
10 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #20]
10 occurrences: str r0, [sp] -> ldr r0, [r4] -> ldr r1, [r4, #4] -> ldr r2, [r4, #8]
40 occurrences: push {lr} -> sub sp, sp, #4 -> str r0, [sp]
38 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
33 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16]
18 occurrences: sub sp, sp, #4 -> str r0, [sp] -> ldr r0, [r4]
16 occurrences: @ <UNDEFINED> instruction: 0xe7e8abf4 -> mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip] -> str r7, [ip, #4]
15 occurrences: @ <UNDEFINED> instruction: 0xe7d8abf4 -> mov fp, r1 -> ldr sl, [r5, #48]
14 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r3, ip
13 occurrences: str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
13 occurrences: str r0, [sp] -> ldr r0, [r4] -> ldr r1, [r4, #4]
12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1 -> add r1, r1, #4
12 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
12 occurrences: add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
10 occurrences: str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #20]
10 occurrences: ldr r0, [r4] -> ldr r1, [r4, #4] -> ldr r2, [r4, #8]
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432 -> bic ip, ip, #16646144
125 occurrences: mov r1, r4 -> ldr r2, [sp]
63 occurrences: sub sp, sp, #4 -> str r0, [sp]
53 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144
40 occurrences: push {lr} -> sub sp, sp, #4
40 occurrences: add sp, sp, #4 -> pop {pc}
38 occurrences: ldr r1, [sp] -> str r0, [r1, #16]
38 occurrences: str r0, [r1, #16] -> ldr r0, [sp]
33 occurrences: mov r0, #8 -> ldr r1, [sp]
33 occurrences: cmp r8, ip -> bhi 0x55d0
32 occurrences: cmp r0, #0 -> bne 0x77dc
31 occurrences: mvn lr, #-33554432 -> bic lr, lr, #16646144
29 occurrences: add sp, sp, #4 -> bx r0
25 occurrences: mov r3, r6 -> ldr r2, [r5, #48]
23 occurrences: mov r2, r6 -> ldr r1, [r5, #48]
23 occurrences: cmp r0, #0 -> bne 0x4a10
22 occurrences: str r0, [sp] -> ldr r0, [r4]
19 occurrences: cmp r7, ip -> bhi 0x55d0
18 occurrences: mov r7, r2 -> ldr r6, [r5, #48]
17 occurrences: mov fp, r1 -> ldr sl, [r5, #48]
17 occurrences: mov r8, r2 -> ldr r7, [r5, #48]
16 occurrences: @ <UNDEFINED> instruction: 0xe7e8abf4 -> mov fp, r6
16 occurrences: mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: @ <UNDEFINED> instruction: 0xe7d178f4 -> ldr r8, [r5, #48]
16 occurrences: cmp r6, ip -> bhi 0x55d0
16 occurrences: mov r8, r0 -> ldr r6, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip]
16 occurrences: str r1, [ip] -> str r7, [ip, #4]
15 occurrences: @ <UNDEFINED> instruction: 0xe7d8abf4 -> mov fp, r1
14 occurrences: ldr r0, [sp] -> ldr r1, [sp, #12]
14 occurrences: bic ip, ip, #16646144 -> cmp r3, ip
13 occurrences: ldr r0, [r4] -> ldr r1, [r4, #4]
12 occurrences: ldr r1, [r4] -> ldr r0, [r5, #48]
12 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48]
12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1
12 occurrences: mov r6, r1 -> add r1, r1, #4
12 occurrences: add r1, r1, #4 -> mov r8, r2
11 occurrences: ldr r0, [sp] -> ldr r1, [sp, #4]
11 occurrences: add sp, sp, #8 -> bx r0
11 occurrences: sub sp, sp, #8 -> str r0, [sp]
11 occurrences: ldr r0, [sp] -> ldr r1, [sp, #20]
11 occurrences: cmp r1, ip -> bhi 0x4a04
10 occurrences: ldr r1, [r4, #4] -> ldr r2, [r4, #8]
10 occurrences: str r0, [sp] -> ldr r6, [r4]
10 occurrences: ldr r2, [r4] -> ldr r1, [r5, #48]
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432
10 occurrences: cmp r3, ip -> bhi 0x4a04
10 occurrences: udf #15920 -> bcs 0x4a04
10 occurrences: cmp r1, ip -> bhi 0x77d0
184 occurrences: blx ip
169 occurrences: cmp r0, #0
125 occurrences: mov r1, r4
125 occurrences: ldr r2, [sp]
117 occurrences: add sp, sp, #4
117 occurrences: andeq r8, r4, ip, lsl #18
106 occurrences: ldr r1, [r5, #48]
96 occurrences: ldr r2, [r5, #48]
77 occurrences: str r0, [sp]
68 occurrences: bhi 0x55d0
65 occurrences: sub sp, sp, #4
62 occurrences: ldr r0, [r5, #48]
61 occurrences: mov lr, #0
53 occurrences: ldr r6, [r5, #48]
53 occurrences: mvn ip, #-33554432
53 occurrences: bic ip, ip, #16646144
47 occurrences: ldr r0, [sp]
47 occurrences: bx r0
47 occurrences: andeq r8, r4, r4
46 occurrences: bcs 0x4a04
44 occurrences: ldr r3, [r5, #48]
43 occurrences: @ <UNDEFINED> instruction: 0xe7e012f4
40 occurrences: push {lr}
40 occurrences: pop {pc}
40 occurrences: cmp r1, ip
40 occurrences: cmp r3, ip
40 occurrences: bhi 0x77d0
39 occurrences: cmp r8, ip
38 occurrences: ldr r1, [sp]
38 occurrences: str r0, [r1, #16]
36 occurrences: ldr sl, [r5, #48]
36 occurrences: bcs 0x1d14
35 occurrences: cmp r7, ip
34 occurrences: ldr r7, [r5, #48]
34 occurrences: mov r0, #8
34 occurrences: ldr r8, [r5, #48]
34 occurrences: mov r1, r0
33 occurrences: cmp ip, #0
32 occurrences: bhi 0x4a04
32 occurrences: bne 0x77dc
31 occurrences: ldr ip, [r4, #28]
31 occurrences: mvn lr, #-33554432
31 occurrences: bic lr, lr, #16646144
30 occurrences: cmp r6, ip
29 occurrences: mov r2, r6
28 occurrences: @ <UNDEFINED> instruction: 0xe7e123f4
28 occurrences: bcs 0xb5c
27 occurrences: add sp, sp, #8
26 occurrences: str r0, [r4]
25 occurrences: mov r3, r6
25 occurrences: cmp r2, ip
24 occurrences: mov r2, #0
24 occurrences: mov r7, r2
24 occurrences: mov r8, r0
23 occurrences: ldr r0, [r4]
23 occurrences: cmp r0, ip
23 occurrences: ldr ip, [r4, #20]
23 occurrences: bne 0x4a10
22 occurrences: mov r1, #0
22 occurrences: mov r2, r0
22 occurrences: str lr, [r4, #4]
22 occurrences: ldr ip, [r4, #64]
21 occurrences: mov ip, #0
20 occurrences: mov r6, r0
20 occurrences: mov fp, r1
19 occurrences: mov r8, r2
19 occurrences: ldr ip, [r4, #80]
19 occurrences: ldr ip, [r4, #84]
18 occurrences: mov lr, #64, 22
18 occurrences: cmp r1, #0
18 occurrences: mov r0, #0
18 occurrences: mov r2, r1
18 occurrences: bcs 0x1568
18 occurrences: mov lr, #1
18 occurrences: ldr ip, [r4, #16]
18 occurrences: str r1, [ip]
18 occurrences: mov r6, r1
17 occurrences: add ip, r6, r8
17 occurrences: mov r3, r0
17 occurrences: mov fp, r6
17 occurrences: bcs 0x31ac
17 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4
17 occurrences: @ <UNDEFINED> instruction: 0xe7d178f4
17 occurrences: b 0x55c8
16 occurrences: @ <UNDEFINED> instruction: 0xe7d201f4
16 occurrences: mov r3, r1
16 occurrences: @ <UNDEFINED> instruction: 0xe7e8abf4
16 occurrences: @ <UNDEFINED> instruction: 0xe7d8abf4
16 occurrences: str r7, [ip, #4]
15 occurrences: bcs 0x3c0
15 occurrences: mov r6, r7
15 occurrences: mov r3, #0
15 occurrences: mov r7, #0
15 occurrences: str lr, [r4, #92]
14 occurrences: ldr lr, [r5, #60]
14 occurrences: ldr r1, [sp, #12]
14 occurrences: ldr r1, [r4, #4]
14 occurrences: mov r0, r1
14 occurrences: add r1, r1, #4
14 occurrences: bhi 0x20e4
14 occurrences: str lr, [r4, #52]
14 occurrences: ldr r3, [r4, #28]
14 occurrences: str lr, [r4, #84]
14 occurrences: ldr r2, [r4, #28]
14 occurrences: ldr ip, [r4, #72]
13 occurrences: add r0, r0, r1
13 occurrences: cmp r6, #0
13 occurrences: ldr ip, [r4, #12]
13 occurrences: str lr, [r4, #40]
13 occurrences: str lr, [r4, #164]
12 occurrences: udf #11820
12 occurrences: udf #15920
12 occurrences: str r6, [r4]
12 occurrences: bcs 0x20e4
12 occurrences: ldr r1, [r4]
12 occurrences: ldr ip, [r4, #44]
12 occurrences: bcs 0x77d0
11 occurrences: ldr r1, [sp, #4]
11 occurrences: sub sp, sp, #8
11 occurrences: @ <UNDEFINED> instruction: 0xe7d012f4
11 occurrences: ldr r1, [sp, #20]
11 occurrences: ldr r2, [r4, #8]
11 occurrences: mov r6, #0
11 occurrences: ldr r6, [r4]
11 occurrences: str lr, [r4, #44]
11 occurrences: cmp r2, #0
11 occurrences: mov sl, r1
11 occurrences: ldr r2, [r4]
11 occurrences: mvn lr, #0
11 occurrences: mov r7, r0
11 occurrences: str lr, [r4, #36]
11 occurrences: mov lr, #32
10 occurrences: ldr r1, [r5, #60]
10 occurrences: mov r8, r7
10 occurrences: mov r3, r7
10 occurrences: ldr r0, [r4, #4]
10 occurrences: str lr, [r4, #16]
10 occurrences: str lr, [r4]
10 occurrences: cmp r9, ip
10 occurrences: bhi 0x1d14
10 occurrences: ldr ip, [r4, #24]
10 occurrences: ldr ip, [r4]
10 occurrences: ldr r1, [ip]
[END] Finished processing log file: guarded_sum-2026-04-28-21:54:06.bin.log

12 occurrences: ldr r1, [r6, r7] -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
10 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
32 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
12 occurrences: ldr r1, [r6, r7] -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
12 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
11 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
10 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #20]
10 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r9, ip -> bhi 0x16c0
10 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48] -> adds r3, r3, #48 -> bcs 0x46a4
39 occurrences: push {lr} -> sub sp, sp, #4 -> str r0, [sp]
36 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
32 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16]
23 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r3, ip
16 occurrences: ldr r8, [sl, fp] -> mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip] -> str r7, [ip, #4]
15 occurrences: sub sp, sp, #4 -> str r0, [sp] -> ldr r0, [r4]
14 occurrences: str r8, [sl, fp] -> mov fp, r1 -> ldr sl, [r5, #48]
13 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r9, ip
12 occurrences: str r0, [sp] -> ldr r0, [r4] -> ldr r1, [r4, #4]
12 occurrences: ldr r1, [r6, r7] -> mov r6, r1 -> add r1, r1, #4
12 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
12 occurrences: add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
11 occurrences: str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
11 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r6, ip
10 occurrences: str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #20]
10 occurrences: bic ip, ip, #16646144 -> cmp r9, ip -> bhi 0x16c0
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432 -> bic ip, ip, #16646144
10 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48] -> adds r3, r3, #48
10 occurrences: ldr r2, [r5, #48] -> adds r3, r3, #48 -> bcs 0x46a4
120 occurrences: mov r1, r4 -> ldr r2, [sp]
83 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144
59 occurrences: sub sp, sp, #4 -> str r0, [sp]
39 occurrences: push {lr} -> sub sp, sp, #4
39 occurrences: add sp, sp, #4 -> pop {pc}
36 occurrences: ldr r1, [sp] -> str r0, [r1, #16]
36 occurrences: str r0, [r1, #16] -> ldr r0, [sp]
33 occurrences: cmp r8, ip -> bhi 0x5180
32 occurrences: mov r0, #8 -> ldr r1, [sp]
32 occurrences: cmp fp, ip -> bhi 0x16c0
32 occurrences: cmp r0, #0 -> bne 0x73ec
28 occurrences: add sp, sp, #4 -> bx r0
25 occurrences: cmp r3, ip -> bhi 0x46a4
23 occurrences: bic ip, ip, #16646144 -> cmp r3, ip
23 occurrences: cmp r0, #0 -> bne 0x46b0
21 occurrences: mov r3, r6 -> ldr r2, [r5, #48]
20 occurrences: str r0, [sp] -> ldr r0, [r4]
19 occurrences: cmp r1, ip -> bhi 0x46a4
19 occurrences: cmp r7, ip -> bhi 0x5180
18 occurrences: mov r7, r2 -> ldr r6, [r5, #48]
17 occurrences: mov r8, r2 -> ldr r7, [r5, #48]
16 occurrences: mov fp, r1 -> ldr sl, [r5, #48]
16 occurrences: ldr r8, [sl, fp] -> mov fp, r6
16 occurrences: mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: str r1, [r7, r8] -> ldr r8, [r5, #48]
16 occurrences: cmp r6, ip -> bhi 0x5180
16 occurrences: mov r8, r0 -> ldr r6, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip]
16 occurrences: str r1, [ip] -> str r7, [ip, #4]
15 occurrences: str r8, [sl, fp] -> mov fp, r1
14 occurrences: cmp r2, ip -> bhi 0x73e0
13 occurrences: bic ip, ip, #16646144 -> cmp r9, ip
12 occurrences: ldr r0, [r4] -> ldr r1, [r4, #4]
12 occurrences: ldr r0, [sp] -> ldr r1, [sp, #12]
12 occurrences: cmp r2, ip -> bhi 0x2d1c
12 occurrences: ldr r1, [r4] -> ldr r0, [r5, #48]
12 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48]
12 occurrences: ldr r1, [r6, r7] -> mov r6, r1
12 occurrences: mov r6, r1 -> add r1, r1, #4
12 occurrences: add r1, r1, #4 -> mov r8, r2
11 occurrences: ldr r0, [sp] -> ldr r1, [sp, #4]
11 occurrences: add sp, sp, #8 -> bx r0
11 occurrences: sub sp, sp, #8 -> str r0, [sp]
11 occurrences: ldr r0, [sp] -> ldr r1, [sp, #20]
11 occurrences: str r0, [sp] -> ldr r6, [r4]
11 occurrences: ldr r2, [r5, #48] -> adds r3, r3, #48
11 occurrences: bic ip, ip, #16646144 -> cmp r6, ip
11 occurrences: cmp r1, ip -> bhi 0x73e0
11 occurrences: cmp r3, ip -> bhi 0x7bfc
10 occurrences: mov r2, r6 -> ldr r1, [r5, #48]
10 occurrences: cmp r9, ip -> bhi 0x16c0
10 occurrences: ldr r2, [r4] -> ldr r1, [r5, #48]
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432
10 occurrences: adds r3, r3, #48 -> bcs 0x46a4
176 occurrences: blx ip
162 occurrences: cmp r0, #0
120 occurrences: mov r1, r4
120 occurrences: ldr r2, [sp]
112 occurrences: @ <UNDEFINED> instruction: 0x000487b4
110 occurrences: add sp, sp, #4
84 occurrences: cmp r3, ip
83 occurrences: ldr r1, [r5, #48]
83 occurrences: mvn ip, #-33554432
83 occurrences: bic ip, ip, #16646144
80 occurrences: ldr r2, [r5, #48]
78 occurrences: bhi 0x46a4
73 occurrences: str r0, [sp]
70 occurrences: mov lr, #0
68 occurrences: bhi 0x5180
64 occurrences: cmp r1, ip
61 occurrences: sub sp, sp, #4
60 occurrences: cmp r2, ip
54 occurrences: ldr r0, [r5, #48]
52 occurrences: bhi 0x73e0
51 occurrences: ldr r6, [r5, #48]
48 occurrences: cmp r6, ip
46 occurrences: bhi 0x16c0
46 occurrences: bcs 0x46a4
45 occurrences: ldr r0, [sp]
45 occurrences: bx r0
45 occurrences: andeq r7, r4, ip, lsr #29
45 occurrences: cmp r8, ip
41 occurrences: cmp r7, ip
39 occurrences: push {lr}
39 occurrences: pop {pc}
39 occurrences: ldr r3, [r5, #48]
39 occurrences: cmp fp, ip
36 occurrences: ldr r1, [sp]
36 occurrences: str r0, [r1, #16]
36 occurrences: ldr sl, [r5, #48]
36 occurrences: bcs 0x16c0
34 occurrences: mov r1, r0
33 occurrences: cmp ip, #0
33 occurrences: ldr r8, [r5, #48]
32 occurrences: mov r0, #8
32 occurrences: ldr r7, [r5, #48]
32 occurrences: bne 0x73ec
31 occurrences: ldr ip, [r4, #28]
28 occurrences: add sp, sp, #8
27 occurrences: ldr r0, [r1, r2]
26 occurrences: str r0, [r4]
26 occurrences: bhi 0x1aec
24 occurrences: bhi 0xce4
24 occurrences: cmp r0, ip
24 occurrences: mov r7, r2
24 occurrences: mov r8, r0
23 occurrences: ldr ip, [r4, #20]
23 occurrences: bne 0x46b0
22 occurrences: cmp r9, ip
22 occurrences: str lr, [r4, #4]
22 occurrences: ldr ip, [r4, #64]
21 occurrences: ldr r0, [r4]
21 occurrences: mov r3, r6
21 occurrences: mov ip, #0
21 occurrences: bhi 0x2d1c
20 occurrences: mov r8, r2
20 occurrences: mov r6, r0
20 occurrences: mov fp, r1
19 occurrences: mov r1, #0
19 occurrences: mov r2, r0
19 occurrences: ldr ip, [r4, #80]
19 occurrences: ldr ip, [r4, #84]
18 occurrences: bcs 0xce4
18 occurrences: ldr r1, [r2, r3]
18 occurrences: mov lr, #1
18 occurrences: ldr ip, [r4, #16]
18 occurrences: str r1, [ip]
18 occurrences: mov r6, r1
17 occurrences: mov lr, #64, 22
17 occurrences: mov r2, r1
17 occurrences: mov r3, r0
17 occurrences: cmp r1, #0
17 occurrences: mov fp, r6
17 occurrences: bcs 0x2d1c
17 occurrences: ldr r1, [r6, r7]
17 occurrences: str r1, [r7, r8]
17 occurrences: b 0x5178
16 occurrences: ldr r8, [sl, fp]
16 occurrences: str r8, [sl, fp]
16 occurrences: add ip, r6, r8
16 occurrences: str r7, [ip, #4]
15 occurrences: mov r0, #0
15 occurrences: mov r2, r6
15 occurrences: mov r3, r1
15 occurrences: mov r7, #0
15 occurrences: str lr, [r4, #92]
14 occurrences: add r1, r1, #4
14 occurrences: str lr, [r4, #52]
14 occurrences: ldr r3, [r4, #28]
14 occurrences: str lr, [r4, #84]
14 occurrences: ldr r2, [r4, #28]
14 occurrences: ldr ip, [r4, #72]
14 occurrences: mov lr, #48
14 occurrences: bhi 0x7bfc
13 occurrences: ldr r1, [r4, #4]
13 occurrences: cmp r6, #0
13 occurrences: ldr ip, [r4, #12]
13 occurrences: mov r3, #0
13 occurrences: mov r6, r7
13 occurrences: str lr, [r4, #40]
13 occurrences: str lr, [r4, #164]
12 occurrences: ldr lr, [r5, #60]
12 occurrences: mov r7, r0
12 occurrences: str r6, [r4]
12 occurrences: ldr r1, [sp, #12]
12 occurrences: mov r0, r1
12 occurrences: mov r2, #0
12 occurrences: bcs 0x1aec
12 occurrences: ldr r1, [r4]
12 occurrences: ldr ip, [r4, #44]
12 occurrences: bcs 0x73e0
11 occurrences: ldr r1, [sp, #4]
11 occurrences: sub sp, sp, #8
11 occurrences: add r0, r0, r1
11 occurrences: ldr r1, [sp, #20]
11 occurrences: mov r6, #0
11 occurrences: ldr r6, [r4]
11 occurrences: str lr, [r4, #44]
11 occurrences: adds r3, r3, #48
11 occurrences: cmp r2, #0
11 occurrences: mov sl, r1
11 occurrences: ldr r2, [r4]
11 occurrences: mvn lr, #0
11 occurrences: str lr, [r4, #36]
11 occurrences: mov lr, #32
10 occurrences: ldr r1, [r5, #60]
10 occurrences: str r0, [r4, #4]
10 occurrences: ldr r0, [r4, #4]
10 occurrences: str lr, [r4, #16]
10 occurrences: ldr r0, [r2, r3]
10 occurrences: str lr, [r4]
10 occurrences: ldr r2, [r4, #8]
10 occurrences: bhi 0x20b4
10 occurrences: bhi 0x27e4
10 occurrences: ldr ip, [r4, #24]
10 occurrences: ldr ip, [r4]
10 occurrences: ldr r1, [ip]
[END] Finished processing log file: factorial-2026-04-28-21:54:01.bin.log

12 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
12 occurrences: ldr r1, [r6, r7] -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
32 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
13 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
12 occurrences: ldr r1, [r6, r7] -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
12 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
12 occurrences: add ip, r6, r8 -> str r1, [ip] -> str r7, [ip, #4] -> mov r0, #64, 16
10 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r2, ip -> bhi 0x914
10 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r9, ip -> bhi 0x1cfc
10 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48] -> adds r3, r3, #48 -> bcs 0x4d0c
39 occurrences: push {lr} -> sub sp, sp, #4 -> str r0, [sp]
36 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
32 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16]
23 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r3, ip
18 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r2, ip
16 occurrences: ldr r8, [sl, fp] -> mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip] -> str r7, [ip, #4]
15 occurrences: sub sp, sp, #4 -> str r0, [sp] -> ldr r0, [r4]
15 occurrences: str r8, [sl, fp] -> mov fp, r1 -> ldr sl, [r5, #48]
13 occurrences: str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
13 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r9, ip
12 occurrences: ldr r1, [r6, r7] -> mov r6, r1 -> add r1, r1, #4
12 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
12 occurrences: add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
12 occurrences: str r1, [ip] -> str r7, [ip, #4] -> mov r0, #64, 16
11 occurrences: str r0, [sp] -> ldr r0, [r4] -> ldr r1, [r4, #4]
11 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r6, ip
10 occurrences: bic ip, ip, #16646144 -> cmp r2, ip -> bhi 0x914
10 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r1, ip
10 occurrences: bic ip, ip, #16646144 -> cmp r9, ip -> bhi 0x1cfc
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432 -> bic ip, ip, #16646144
10 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48] -> adds r3, r3, #48
10 occurrences: ldr r2, [r5, #48] -> adds r3, r3, #48 -> bcs 0x4d0c
117 occurrences: mov r1, r4 -> ldr r2, [sp]
96 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144
59 occurrences: sub sp, sp, #4 -> str r0, [sp]
40 occurrences: mov r2, r6 -> ldr r1, [r5, #48]
39 occurrences: push {lr} -> sub sp, sp, #4
39 occurrences: add sp, sp, #4 -> pop {pc}
36 occurrences: ldr r1, [sp] -> str r0, [r1, #16]
36 occurrences: str r0, [r1, #16] -> ldr r0, [sp]
33 occurrences: cmp r8, ip -> bhi 0x590c
32 occurrences: cmp r2, ip -> bhi 0x914
32 occurrences: mov r0, #8 -> ldr r1, [sp]
32 occurrences: cmp fp, ip -> bhi 0x1cfc
32 occurrences: cmp r0, #0 -> bne 0x7b24
30 occurrences: mov r3, r6 -> ldr r2, [r5, #48]
26 occurrences: add sp, sp, #4 -> bx r0
25 occurrences: cmp r3, ip -> bhi 0x4d0c
23 occurrences: bic ip, ip, #16646144 -> cmp r3, ip
23 occurrences: cmp r0, #0 -> bne 0x4d18
19 occurrences: str r0, [sp] -> ldr r0, [r4]
19 occurrences: cmp r1, ip -> bhi 0x4d0c
19 occurrences: cmp r7, ip -> bhi 0x590c
18 occurrences: bic ip, ip, #16646144 -> cmp r2, ip
18 occurrences: mov r7, r2 -> ldr r6, [r5, #48]
17 occurrences: mov fp, r1 -> ldr sl, [r5, #48]
17 occurrences: mov r8, r2 -> ldr r7, [r5, #48]
16 occurrences: ldr r8, [sl, fp] -> mov fp, r6
16 occurrences: mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: str r1, [r7, r8] -> ldr r8, [r5, #48]
16 occurrences: cmp r6, ip -> bhi 0x590c
16 occurrences: mov r8, r0 -> ldr r6, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip]
16 occurrences: str r1, [ip] -> str r7, [ip, #4]
15 occurrences: cmp r3, ip -> bhi 0x914
15 occurrences: str r8, [sl, fp] -> mov fp, r1
14 occurrences: ldr r0, [sp] -> ldr r1, [sp, #12]
14 occurrences: cmp r2, ip -> bhi 0x7b18
13 occurrences: bic ip, ip, #16646144 -> cmp r9, ip
12 occurrences: mov r3, r0 -> ldr r2, [r5, #48]
12 occurrences: cmp r2, ip -> bhi 0x3458
12 occurrences: ldr r1, [r4] -> ldr r0, [r5, #48]
12 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48]
12 occurrences: ldr r1, [r6, r7] -> mov r6, r1
12 occurrences: mov r6, r1 -> add r1, r1, #4
12 occurrences: add r1, r1, #4 -> mov r8, r2
12 occurrences: str r7, [ip, #4] -> mov r0, #64, 16
11 occurrences: ldr r0, [sp] -> ldr r1, [sp, #4]
11 occurrences: add sp, sp, #8 -> bx r0
11 occurrences: sub sp, sp, #8 -> str r0, [sp]
11 occurrences: str r0, [sp] -> ldr r6, [r4]
11 occurrences: ldr r0, [r4] -> ldr r1, [r4, #4]
11 occurrences: ldr r2, [r5, #48] -> adds r3, r3, #48
11 occurrences: bic ip, ip, #16646144 -> cmp r6, ip
11 occurrences: cmp r1, ip -> bhi 0x7b18
11 occurrences: cmp r3, ip -> bhi 0x823c
10 occurrences: ldr r1, [r5, #48] -> adds r2, r2, #36
10 occurrences: bic ip, ip, #16646144 -> cmp r1, ip
10 occurrences: cmp r9, ip -> bhi 0x1cfc
10 occurrences: ldr r2, [r4] -> ldr r1, [r5, #48]
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432
10 occurrences: adds r3, r3, #48 -> bcs 0x4d0c
175 occurrences: blx ip
162 occurrences: cmp r0, #0
119 occurrences: mov r1, r4
119 occurrences: ldr r2, [sp]
116 occurrences: ldr r1, [r5, #48]
111 occurrences: @ <UNDEFINED> instruction: 0x000487b4
108 occurrences: add sp, sp, #4
97 occurrences: cmp r3, ip
96 occurrences: mvn ip, #-33554432
96 occurrences: bic ip, ip, #16646144
95 occurrences: ldr r2, [r5, #48]
94 occurrences: cmp r2, ip
78 occurrences: bhi 0x4d0c
74 occurrences: mov lr, #0
73 occurrences: str r0, [sp]
68 occurrences: bhi 0x590c
64 occurrences: cmp r1, ip
61 occurrences: sub sp, sp, #4
54 occurrences: bhi 0x914
53 occurrences: bcs 0x914
52 occurrences: ldr r0, [r5, #48]
52 occurrences: bhi 0x7b18
51 occurrences: ldr r6, [r5, #48]
50 occurrences: cmp r6, ip
46 occurrences: bhi 0x1cfc
46 occurrences: bcs 0x4d0c
45 occurrences: ldr r0, [sp]
45 occurrences: bx r0
45 occurrences: mov r2, r6
45 occurrences: andeq r7, r4, ip, lsr #29
45 occurrences: cmp r8, ip
42 occurrences: ldr r3, [r5, #48]
41 occurrences: cmp r7, ip
39 occurrences: push {lr}
39 occurrences: pop {pc}
39 occurrences: ldr r0, [r1, r2]
39 occurrences: cmp fp, ip
36 occurrences: ldr r1, [sp]
36 occurrences: str r0, [r1, #16]
36 occurrences: ldr sl, [r5, #48]
36 occurrences: bcs 0x1cfc
35 occurrences: ldr r1, [r2, r3]
34 occurrences: mov r1, r0
33 occurrences: cmp ip, #0
33 occurrences: ldr r8, [r5, #48]
32 occurrences: mov r0, #8
32 occurrences: ldr r7, [r5, #48]
32 occurrences: bne 0x7b24
31 occurrences: ldr ip, [r4, #28]
30 occurrences: mov r3, r6
26 occurrences: add sp, sp, #8
26 occurrences: str r0, [r4]
26 occurrences: bhi 0x219c
24 occurrences: bhi 0x1430
24 occurrences: cmp r0, ip
24 occurrences: mov r7, r2
24 occurrences: mov r8, r0
23 occurrences: ldr ip, [r4, #20]
23 occurrences: bne 0x4d18
22 occurrences: mov r2, r0
22 occurrences: mov r6, r0
22 occurrences: cmp r9, ip
22 occurrences: str lr, [r4, #4]
22 occurrences: ldr ip, [r4, #64]
21 occurrences: mov r3, r0
21 occurrences: mov ip, #0
21 occurrences: bhi 0x3458
20 occurrences: ldr r0, [r4]
20 occurrences: mov fp, r1
19 occurrences: mov r8, r2
19 occurrences: ldr ip, [r4, #80]
19 occurrences: ldr ip, [r4, #84]
18 occurrences: mov r0, #0
18 occurrences: mov r1, #0
18 occurrences: bcs 0x1430
18 occurrences: mov lr, #1
18 occurrences: ldr ip, [r4, #16]
18 occurrences: str r1, [ip]
18 occurrences: mov r6, r1
17 occurrences: mov lr, #64, 22
17 occurrences: mov r2, r1
17 occurrences: cmp r1, #0
17 occurrences: mov fp, r6
17 occurrences: bcs 0x3458
17 occurrences: ldr r1, [r6, r7]
17 occurrences: str r1, [r7, r8]
17 occurrences: b 0x5904
16 occurrences: ldr r8, [sl, fp]
16 occurrences: str r8, [sl, fp]
16 occurrences: add ip, r6, r8
16 occurrences: str r7, [ip, #4]
15 occurrences: str r0, [r1, r2]
15 occurrences: mov r3, r1
15 occurrences: mov r7, #0
15 occurrences: str lr, [r4, #92]
14 occurrences: add r0, r0, r1
14 occurrences: ldr r1, [sp, #12]
14 occurrences: add r1, r1, #4
14 occurrences: str lr, [r4, #52]
14 occurrences: ldr r3, [r4, #28]
14 occurrences: str lr, [r4, #84]
14 occurrences: ldr r2, [r4, #28]
14 occurrences: ldr ip, [r4, #72]
14 occurrences: mov lr, #48
14 occurrences: mov r0, #64, 16
14 occurrences: bhi 0x823c
13 occurrences: cmp r6, #0
13 occurrences: ldr ip, [r4, #12]
13 occurrences: mov r3, #0
13 occurrences: mov r6, r7
13 occurrences: str lr, [r4, #40]
13 occurrences: str lr, [r4, #164]
12 occurrences: ldr lr, [r5, #60]
12 occurrences: str lr, [r4, #44]
12 occurrences: str r6, [r4]
12 occurrences: ldr r1, [r4, #4]
12 occurrences: mov r0, r1
12 occurrences: mov r2, #0
12 occurrences: bcs 0x219c
12 occurrences: ldr r1, [r4]
12 occurrences: ldr ip, [r4, #44]
12 occurrences: bcs 0x7b18
11 occurrences: ldr r1, [sp, #4]
11 occurrences: sub sp, sp, #8
11 occurrences: str lr, [r0, r1]
11 occurrences: mov r6, #0
11 occurrences: ldr r6, [r4]
11 occurrences: adds r3, r3, #48
11 occurrences: cmp r2, #0
11 occurrences: mov sl, r1
11 occurrences: ldr r2, [r4]
11 occurrences: mvn lr, #0
11 occurrences: mov r7, r0
11 occurrences: str lr, [r4, #36]
11 occurrences: mov lr, #32
10 occurrences: ldrb r0, [r1, r2]
10 occurrences: and r0, r0, #255
10 occurrences: adds r3, r3, #36
10 occurrences: adds r2, r2, #36
10 occurrences: ldr r1, [r5, #60]
10 occurrences: ldr r0, [r4, #4]
10 occurrences: str lr, [r4, #16]
10 occurrences: ldr r0, [r2, r3]
10 occurrences: str lr, [r4]
10 occurrences: ldr r2, [r4, #8]
10 occurrences: bhi 0x2764
10 occurrences: bhi 0x2e04
10 occurrences: ldr ip, [r4, #24]
10 occurrences: ldr ip, [r4]
10 occurrences: ldr r1, [ip]
[END] Finished processing log file: memwalk-2026-04-28-21:54:02.bin.log

12 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
12 occurrences: ldr r1, [r6, r7] -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
31 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
13 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
12 occurrences: ldr r1, [r6, r7] -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
12 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
10 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r9, ip -> bhi 0x17b8
10 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48] -> adds r3, r3, #48 -> bcs 0x479c
39 occurrences: push {lr} -> sub sp, sp, #4 -> str r0, [sp]
36 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
31 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16]
23 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r3, ip
16 occurrences: ldr r8, [sl, fp] -> mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip] -> str r7, [ip, #4]
15 occurrences: sub sp, sp, #4 -> str r0, [sp] -> ldr r0, [r4]
15 occurrences: str r8, [sl, fp] -> mov fp, r1 -> ldr sl, [r5, #48]
13 occurrences: str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
13 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r9, ip
12 occurrences: ldr r1, [r6, r7] -> mov r6, r1 -> add r1, r1, #4
12 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
12 occurrences: add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
11 occurrences: str r0, [sp] -> ldr r0, [r4] -> ldr r1, [r4, #4]
11 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r6, ip
10 occurrences: bic ip, ip, #16646144 -> cmp r9, ip -> bhi 0x17b8
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432 -> bic ip, ip, #16646144
10 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48] -> adds r3, r3, #48
10 occurrences: ldr r2, [r5, #48] -> adds r3, r3, #48 -> bcs 0x479c
119 occurrences: mov r1, r4 -> ldr r2, [sp]
83 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144
59 occurrences: sub sp, sp, #4 -> str r0, [sp]
39 occurrences: push {lr} -> sub sp, sp, #4
39 occurrences: add sp, sp, #4 -> pop {pc}
36 occurrences: ldr r1, [sp] -> str r0, [r1, #16]
36 occurrences: str r0, [r1, #16] -> ldr r0, [sp]
33 occurrences: cmp r8, ip -> bhi 0x5280
32 occurrences: cmp fp, ip -> bhi 0x17b8
32 occurrences: cmp r0, #0 -> bne 0x75cc
31 occurrences: mov r0, #8 -> ldr r1, [sp]
26 occurrences: add sp, sp, #4 -> bx r0
25 occurrences: cmp r3, ip -> bhi 0x479c
23 occurrences: bic ip, ip, #16646144 -> cmp r3, ip
23 occurrences: cmp r0, #0 -> bne 0x47a8
20 occurrences: str r0, [sp] -> ldr r0, [r4]
19 occurrences: mov r2, r6 -> ldr r1, [r5, #48]
19 occurrences: cmp r1, ip -> bhi 0x479c
19 occurrences: cmp r7, ip -> bhi 0x5280
18 occurrences: mov r3, r6 -> ldr r2, [r5, #48]
18 occurrences: mov r7, r2 -> ldr r6, [r5, #48]
17 occurrences: mov fp, r1 -> ldr sl, [r5, #48]
17 occurrences: mov r8, r2 -> ldr r7, [r5, #48]
16 occurrences: ldr r8, [sl, fp] -> mov fp, r6
16 occurrences: mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: str r1, [r7, r8] -> ldr r8, [r5, #48]
16 occurrences: cmp r6, ip -> bhi 0x5280
16 occurrences: mov r8, r0 -> ldr r6, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip]
16 occurrences: str r1, [ip] -> str r7, [ip, #4]
15 occurrences: str r8, [sl, fp] -> mov fp, r1
14 occurrences: ldr r0, [sp] -> ldr r1, [sp, #12]
14 occurrences: cmp r2, ip -> bhi 0x75c0
13 occurrences: bic ip, ip, #16646144 -> cmp r9, ip
12 occurrences: cmp r2, ip -> bhi 0x2e28
12 occurrences: ldr r1, [r4] -> ldr r0, [r5, #48]
12 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48]
12 occurrences: ldr r1, [r6, r7] -> mov r6, r1
12 occurrences: mov r6, r1 -> add r1, r1, #4
12 occurrences: add r1, r1, #4 -> mov r8, r2
11 occurrences: ldr r0, [sp] -> ldr r1, [sp, #4]
11 occurrences: add sp, sp, #8 -> bx r0
11 occurrences: sub sp, sp, #8 -> str r0, [sp]
11 occurrences: str r0, [sp] -> ldr r6, [r4]
11 occurrences: ldr r0, [r4] -> ldr r1, [r4, #4]
11 occurrences: ldr r2, [r5, #48] -> adds r3, r3, #48
11 occurrences: bic ip, ip, #16646144 -> cmp r6, ip
11 occurrences: cmp r1, ip -> bhi 0x75c0
11 occurrences: cmp r3, ip -> bhi 0x7ce8
10 occurrences: ldr r1, [r5, #48] -> adds r2, r2, #16
10 occurrences: cmp r9, ip -> bhi 0x17b8
10 occurrences: ldr r2, [r4] -> ldr r1, [r5, #48]
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432
10 occurrences: adds r3, r3, #48 -> bcs 0x479c
175 occurrences: blx ip
162 occurrences: cmp r0, #0
119 occurrences: mov r1, r4
119 occurrences: ldr r2, [sp]
111 occurrences: @ <UNDEFINED> instruction: 0x000487b4
108 occurrences: add sp, sp, #4
92 occurrences: ldr r1, [r5, #48]
87 occurrences: cmp r3, ip
83 occurrences: ldr r2, [r5, #48]
83 occurrences: mvn ip, #-33554432
83 occurrences: bic ip, ip, #16646144
78 occurrences: bhi 0x479c
73 occurrences: str r0, [sp]
70 occurrences: cmp r2, ip
70 occurrences: mov lr, #0
68 occurrences: bhi 0x5280
61 occurrences: sub sp, sp, #4
60 occurrences: cmp r1, ip
52 occurrences: bhi 0x75c0
51 occurrences: cmp r6, ip
51 occurrences: ldr r0, [r5, #48]
51 occurrences: ldr r6, [r5, #48]
46 occurrences: bhi 0x17b8
46 occurrences: bcs 0x479c
45 occurrences: ldr r0, [sp]
45 occurrences: bx r0
45 occurrences: andeq r7, r4, ip, lsr #29
45 occurrences: cmp r8, ip
42 occurrences: ldr r3, [r5, #48]
41 occurrences: cmp r7, ip
39 occurrences: push {lr}
39 occurrences: pop {pc}
39 occurrences: cmp fp, ip
36 occurrences: ldr r1, [sp]
36 occurrences: str r0, [r1, #16]
36 occurrences: ldr sl, [r5, #48]
36 occurrences: bcs 0x17b8
34 occurrences: mov r1, r0
33 occurrences: cmp ip, #0
33 occurrences: ldr r8, [r5, #48]
32 occurrences: mov r0, #8
32 occurrences: ldr r0, [r1, r2]
32 occurrences: ldr r7, [r5, #48]
32 occurrences: bne 0x75cc
31 occurrences: ldr ip, [r4, #28]
26 occurrences: add sp, sp, #8
26 occurrences: str r0, [r4]
26 occurrences: bhi 0x1be4
24 occurrences: mov r2, r6
24 occurrences: bhi 0xdec
24 occurrences: cmp r0, ip
24 occurrences: mov r7, r2
24 occurrences: mov r8, r0
23 occurrences: ldr ip, [r4, #20]
23 occurrences: bne 0x47a8
22 occurrences: cmp r9, ip
22 occurrences: str lr, [r4, #4]
22 occurrences: ldr ip, [r4, #64]
21 occurrences: ldr r0, [r4]
21 occurrences: mov r3, r1
21 occurrences: mov r6, r1
21 occurrences: mov ip, #0
21 occurrences: bhi 0x2e28
20 occurrences: ldr r1, [r2, r3]
20 occurrences: mov r6, r0
20 occurrences: mov fp, r1
19 occurrences: mov r2, r0
19 occurrences: mov r8, r2
19 occurrences: ldr ip, [r4, #80]
19 occurrences: ldr ip, [r4, #84]
18 occurrences: mov r2, r1
18 occurrences: mov r3, r6
18 occurrences: bcs 0xdec
18 occurrences: mov lr, #1
18 occurrences: ldr ip, [r4, #16]
18 occurrences: str r1, [ip]
17 occurrences: mov lr, #64, 22
17 occurrences: mov r3, r0
17 occurrences: cmp r1, #0
17 occurrences: mov fp, r6
17 occurrences: mov r1, #0
17 occurrences: bcs 0x2e28
17 occurrences: ldr r1, [r6, r7]
17 occurrences: str r1, [r7, r8]
17 occurrences: b 0x5278
16 occurrences: mov r0, #0
16 occurrences: ldr r8, [sl, fp]
16 occurrences: str r8, [sl, fp]
16 occurrences: add ip, r6, r8
16 occurrences: str r7, [ip, #4]
15 occurrences: bhi 0x520
15 occurrences: mov r7, #0
15 occurrences: str lr, [r4, #92]
14 occurrences: ldr r1, [sp, #12]
14 occurrences: bcs 0x520
14 occurrences: add r1, r1, #4
14 occurrences: str lr, [r4, #52]
14 occurrences: ldr r3, [r4, #28]
14 occurrences: str lr, [r4, #84]
14 occurrences: ldr r2, [r4, #28]
14 occurrences: ldr ip, [r4, #72]
14 occurrences: mov lr, #48
14 occurrences: bhi 0x7ce8
13 occurrences: ldr r0, [r2, r3]
13 occurrences: cmp r6, #0
13 occurrences: ldr ip, [r4, #12]
13 occurrences: mov r3, #0
13 occurrences: mov r6, r7
13 occurrences: str lr, [r4, #40]
13 occurrences: str lr, [r4, #164]
12 occurrences: ldr lr, [r5, #60]
12 occurrences: adds r2, r2, #16
12 occurrences: str r6, [r4]
12 occurrences: ldr r1, [r4, #4]
12 occurrences: mov r0, r1
12 occurrences: mov r2, #0
12 occurrences: bcs 0x1be4
12 occurrences: ldr r1, [r4]
12 occurrences: ldr ip, [r4, #44]
12 occurrences: bcs 0x75c0
11 occurrences: ldr r1, [sp, #4]
11 occurrences: sub sp, sp, #8
11 occurrences: mov r6, #0
11 occurrences: ldr r6, [r4]
11 occurrences: str lr, [r4, #44]
11 occurrences: adds r3, r3, #48
11 occurrences: cmp r2, #0
11 occurrences: mov sl, r1
11 occurrences: ldr r2, [r4]
11 occurrences: mvn lr, #0
11 occurrences: mov r7, r0
11 occurrences: str lr, [r4, #36]
11 occurrences: mov lr, #32
10 occurrences: bcs 0x258
10 occurrences: bhi 0x258
10 occurrences: ldr r1, [r5, #60]
10 occurrences: ldr r0, [r4, #4]
10 occurrences: str lr, [r4, #16]
10 occurrences: str lr, [r4]
10 occurrences: ldr r2, [r4, #8]
10 occurrences: bhi 0x2244
10 occurrences: bhi 0x28f0
10 occurrences: ldr ip, [r4, #24]
10 occurrences: ldr ip, [r4]
10 occurrences: ldr r1, [ip]
[END] Finished processing log file: polynomial-2026-04-28-21:54:02.bin.log

13 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
12 occurrences: ldr r1, [r6, r7] -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
34 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
14 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
12 occurrences: ldr r1, [r6, r7] -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
12 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
10 occurrences: sub sp, sp, #4 -> str r0, [sp] -> ldr r0, [r4] -> ldr r1, [r4, #4]
10 occurrences: str r0, [sp] -> ldr r0, [r4] -> ldr r1, [r4, #4] -> ldr r2, [r4, #8]
10 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r9, ip -> bhi 0x21c0
10 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48] -> adds r3, r3, #48 -> bcs 0x511c
40 occurrences: push {lr} -> sub sp, sp, #4 -> str r0, [sp]
38 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
34 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16]
22 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r3, ip
17 occurrences: sub sp, sp, #4 -> str r0, [sp] -> ldr r0, [r4]
16 occurrences: ldr r8, [sl, fp] -> mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip] -> str r7, [ip, #4]
15 occurrences: str r8, [sl, fp] -> mov fp, r1 -> ldr sl, [r5, #48]
14 occurrences: str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
13 occurrences: str r0, [sp] -> ldr r0, [r4] -> ldr r1, [r4, #4]
13 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r9, ip
12 occurrences: ldr r1, [r6, r7] -> mov r6, r1 -> add r1, r1, #4
12 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
12 occurrences: add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
11 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r6, ip
10 occurrences: ldr r0, [r4] -> ldr r1, [r4, #4] -> ldr r2, [r4, #8]
10 occurrences: bic ip, ip, #16646144 -> cmp r9, ip -> bhi 0x21c0
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432 -> bic ip, ip, #16646144
10 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48] -> adds r3, r3, #48
10 occurrences: ldr r2, [r5, #48] -> adds r3, r3, #48 -> bcs 0x511c
123 occurrences: mov r1, r4 -> ldr r2, [sp]
82 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144
62 occurrences: sub sp, sp, #4 -> str r0, [sp]
40 occurrences: push {lr} -> sub sp, sp, #4
40 occurrences: add sp, sp, #4 -> pop {pc}
38 occurrences: ldr r1, [sp] -> str r0, [r1, #16]
38 occurrences: str r0, [r1, #16] -> ldr r0, [sp]
34 occurrences: mov r0, #8 -> ldr r1, [sp]
33 occurrences: cmp r8, ip -> bhi 0x5cd0
32 occurrences: cmp fp, ip -> bhi 0x21c0
32 occurrences: cmp r0, #0 -> bne 0x7eec
31 occurrences: mov r3, r6 -> ldr r2, [r5, #48]
28 occurrences: add sp, sp, #4 -> bx r0
26 occurrences: mov r2, r6 -> ldr r1, [r5, #48]
25 occurrences: cmp r3, ip -> bhi 0x511c
23 occurrences: mov r1, r6 -> ldr r0, [r5, #48]
23 occurrences: bic ip, ip, #16646144 -> cmp r3, ip
23 occurrences: cmp r0, #0 -> bne 0x5128
22 occurrences: str r0, [sp] -> ldr r0, [r4]
19 occurrences: cmp r1, ip -> bhi 0x511c
19 occurrences: cmp r7, ip -> bhi 0x5cd0
18 occurrences: mov r7, r2 -> ldr r6, [r5, #48]
17 occurrences: cmp r1, ip -> bhi 0xde4
17 occurrences: mov fp, r1 -> ldr sl, [r5, #48]
17 occurrences: mov r8, r2 -> ldr r7, [r5, #48]
16 occurrences: ldr r8, [sl, fp] -> mov fp, r6
16 occurrences: mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: str r1, [r7, r8] -> ldr r8, [r5, #48]
16 occurrences: cmp r6, ip -> bhi 0x5cd0
16 occurrences: mov r8, r0 -> ldr r6, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip]
16 occurrences: str r1, [ip] -> str r7, [ip, #4]
15 occurrences: ldr r0, [sp] -> ldr r1, [sp, #12]
15 occurrences: str r8, [sl, fp] -> mov fp, r1
14 occurrences: cmp r2, ip -> bhi 0x7ee0
13 occurrences: ldr r2, [r5, #48] -> adds r3, r3, #48
13 occurrences: ldr r0, [r4] -> ldr r1, [r4, #4]
13 occurrences: bic ip, ip, #16646144 -> cmp r9, ip
12 occurrences: sub sp, sp, #8 -> str r0, [sp]
12 occurrences: ldr lr, [ip] -> ldr ip, [ip, #4]
12 occurrences: cmp r2, ip -> bhi 0x386c
12 occurrences: ldr r1, [r4] -> ldr r0, [r5, #48]
12 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48]
12 occurrences: ldr r1, [r6, r7] -> mov r6, r1
12 occurrences: mov r6, r1 -> add r1, r1, #4
12 occurrences: add r1, r1, #4 -> mov r8, r2
11 occurrences: ldr r0, [sp] -> ldr r1, [sp, #4]
11 occurrences: add sp, sp, #8 -> bx r0
11 occurrences: str r0, [sp] -> ldr r6, [r4]
11 occurrences: bic ip, ip, #16646144 -> cmp r6, ip
11 occurrences: cmp r1, ip -> bhi 0x7ee0
11 occurrences: cmp r3, ip -> bhi 0x8740
10 occurrences: ldr r1, [r4, #4] -> ldr r2, [r4, #8]
10 occurrences: ldr r0, [sp] -> ldr r1, [sp, #20]
10 occurrences: cmp r9, ip -> bhi 0x21c0
10 occurrences: ldr r2, [r4] -> ldr r1, [r5, #48]
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432
10 occurrences: adds r3, r3, #48 -> bcs 0x511c
182 occurrences: blx ip
166 occurrences: cmp r0, #0
124 occurrences: mov r1, r4
124 occurrences: ldr r2, [sp]
116 occurrences: @ <UNDEFINED> instruction: 0x000487b4
114 occurrences: add sp, sp, #4
100 occurrences: ldr r1, [r5, #48]
95 occurrences: ldr r2, [r5, #48]
94 occurrences: cmp r3, ip
83 occurrences: mvn ip, #-33554432
83 occurrences: bic ip, ip, #16646144
82 occurrences: cmp r1, ip
80 occurrences: cmp r2, ip
78 occurrences: bhi 0x511c
77 occurrences: str r0, [sp]
72 occurrences: ldr r0, [r5, #48]
72 occurrences: mov lr, #0
68 occurrences: bhi 0x5cd0
64 occurrences: sub sp, sp, #4
52 occurrences: ldr r6, [r5, #48]
52 occurrences: bhi 0x7ee0
49 occurrences: cmp r6, ip
47 occurrences: ldr r0, [sp]
47 occurrences: bx r0
47 occurrences: cmp r8, ip
47 occurrences: andeq r7, r4, ip, lsr #29
46 occurrences: bhi 0x21c0
46 occurrences: bcs 0x511c
44 occurrences: cmp r7, ip
43 occurrences: ldr r3, [r5, #48]
40 occurrences: push {lr}
40 occurrences: pop {pc}
39 occurrences: cmp fp, ip
38 occurrences: ldr r1, [sp]
38 occurrences: str r0, [r1, #16]
38 occurrences: ldr r0, [r1, r2]
36 occurrences: bhi 0xde4
36 occurrences: ldr sl, [r5, #48]
36 occurrences: bcs 0x21c0
34 occurrences: mov r0, #8
34 occurrences: ldr r7, [r5, #48]
34 occurrences: mov r1, r0
33 occurrences: bcs 0xde4
33 occurrences: cmp ip, #0
33 occurrences: ldr r8, [r5, #48]
32 occurrences: mov r2, r6
32 occurrences: bne 0x7eec
31 occurrences: mov r3, r6
31 occurrences: ldr ip, [r4, #28]
28 occurrences: add sp, sp, #8
26 occurrences: str r0, [r4]
26 occurrences: bhi 0x25ec
24 occurrences: ldr r1, [r2, r3]
24 occurrences: bhi 0x1844
24 occurrences: cmp r0, ip
24 occurrences: mov r7, r2
24 occurrences: mov r8, r0
23 occurrences: mov r1, r6
23 occurrences: mov ip, #0
23 occurrences: ldr r0, [r4]
23 occurrences: ldr ip, [r4, #20]
23 occurrences: bne 0x5128
22 occurrences: cmp r9, ip
22 occurrences: str lr, [r4, #4]
22 occurrences: ldr ip, [r4, #64]
21 occurrences: mov r2, r0
21 occurrences: bhi 0x386c
20 occurrences: mov r1, #0
20 occurrences: mov r6, r0
20 occurrences: mov fp, r1
19 occurrences: mov r8, r2
19 occurrences: ldr ip, [r4, #80]
19 occurrences: ldr ip, [r4, #84]
18 occurrences: mov r0, #0
18 occurrences: mov r2, r1
18 occurrences: bcs 0x1844
18 occurrences: mov lr, #1
18 occurrences: ldr ip, [r4, #16]
18 occurrences: str r1, [ip]
18 occurrences: mov r6, r1
17 occurrences: mov lr, #64, 22
17 occurrences: mov r3, r0
17 occurrences: cmp r1, #0
17 occurrences: mov fp, r6
17 occurrences: bcs 0x386c
17 occurrences: ldr r1, [r6, r7]
17 occurrences: str r1, [r7, r8]
17 occurrences: b 0x5cc8
16 occurrences: bhi 0x7b8
16 occurrences: mov r3, r1
16 occurrences: ldr r8, [sl, fp]
16 occurrences: str r8, [sl, fp]
16 occurrences: add ip, r6, r8
16 occurrences: str r7, [ip, #4]
15 occurrences: add ip, r0, r1
15 occurrences: ldr r1, [sp, #12]
15 occurrences: bcs 0x7b8
15 occurrences: ldr r3, [r4, #28]
15 occurrences: mov r7, #0
15 occurrences: str lr, [r4, #92]
14 occurrences: ldr lr, [r5, #60]
14 occurrences: mov r2, #0
14 occurrences: ldr r1, [r4, #4]
14 occurrences: mov r3, #0
14 occurrences: add r1, r1, #4
14 occurrences: str lr, [r4, #52]
14 occurrences: str lr, [r4, #84]
14 occurrences: ldr r2, [r4, #28]
14 occurrences: ldr ip, [r4, #72]
14 occurrences: mov lr, #48
14 occurrences: bhi 0x8740
13 occurrences: bhi 0x3f0
13 occurrences: adds r3, r3, #48
13 occurrences: cmp r6, #0
13 occurrences: ldr ip, [r4, #12]
13 occurrences: mov r6, r7
13 occurrences: str lr, [r4, #40]
13 occurrences: str lr, [r4, #164]
12 occurrences: sub sp, sp, #8
12 occurrences: add r0, r0, r1
12 occurrences: ldr lr, [ip]
12 occurrences: ldr ip, [ip, #4]
12 occurrences: str r6, [r4]
12 occurrences: mov r0, r1
12 occurrences: bcs 0x25ec
12 occurrences: ldr r1, [r4]
12 occurrences: ldr ip, [r4, #44]
12 occurrences: bcs 0x7ee0
11 occurrences: ldr r1, [sp, #4]
11 occurrences: str lr, [r0, r1]
11 occurrences: str r0, [r1, r2]
11 occurrences: ldr r2, [r4, #8]
11 occurrences: mov r6, #0
11 occurrences: ldr r6, [r4]
11 occurrences: str lr, [r4, #44]
11 occurrences: cmp r2, #0
11 occurrences: mov sl, r1
11 occurrences: ldr r2, [r4]
11 occurrences: mvn lr, #0
11 occurrences: mov r7, r0
11 occurrences: str lr, [r4, #36]
11 occurrences: mov lr, #32
10 occurrences: bcs 0x3f0
10 occurrences: str lr, [ip]
10 occurrences: str lr, [ip, #4]
10 occurrences: str r0, [r4, #4]
10 occurrences: ldr r1, [r5, #60]
10 occurrences: ldr r1, [sp, #20]
10 occurrences: ldr r0, [r4, #4]
10 occurrences: str lr, [r4, #16]
10 occurrences: ldr r0, [r2, r3]
10 occurrences: str lr, [r4]
10 occurrences: bhi 0x2bb4
10 occurrences: bhi 0x3330
10 occurrences: ldr ip, [r4, #24]
10 occurrences: ldr ip, [r4]
10 occurrences: ldr r1, [ip]
[END] Finished processing log file: promote-2026-04-28-21:54:02.bin.log

18 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
12 occurrences: ldr r1, [r6, r7] -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
38 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
19 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
14 occurrences: push {lr} -> sub sp, sp, #4 -> str r0, [sp] -> mov lr, r5
12 occurrences: ldr r1, [r6, r7] -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
12 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
10 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r9, ip -> bhi 0x24a0
10 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48] -> adds r3, r3, #48 -> bcs 0x54bc
45 occurrences: push {lr} -> sub sp, sp, #4 -> str r0, [sp]
42 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
38 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16]
23 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r3, ip
19 occurrences: str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
17 occurrences: str r0, [sp] -> ldr r0, [r4] -> ldr r1, [r4, #4]
16 occurrences: ldr r8, [sl, fp] -> mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip] -> str r7, [ip, #4]
15 occurrences: sub sp, sp, #4 -> str r0, [sp] -> ldr r0, [r4]
15 occurrences: str r8, [sl, fp] -> mov fp, r1 -> ldr sl, [r5, #48]
14 occurrences: sub sp, sp, #4 -> str r0, [sp] -> mov lr, r5
13 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r9, ip
12 occurrences: push {r6, lr} -> sub sp, sp, #8 -> str r0, [sp]
12 occurrences: ldr r6, [sp, #8] -> add sp, sp, #16 -> bx r0
12 occurrences: ldr r1, [r6, r7] -> mov r6, r1 -> add r1, r1, #4
12 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
12 occurrences: add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
11 occurrences: sub sp, sp, #8 -> str r0, [sp] -> ldr r0, [r4]
11 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r6, ip
10 occurrences: bic ip, ip, #16646144 -> cmp r9, ip -> bhi 0x24a0
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432 -> bic ip, ip, #16646144
10 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48] -> adds r3, r3, #48
10 occurrences: ldr r2, [r5, #48] -> adds r3, r3, #48 -> bcs 0x54bc
120 occurrences: mov r1, r4 -> ldr r2, [sp]
83 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144
66 occurrences: sub sp, sp, #4 -> str r0, [sp]
45 occurrences: push {lr} -> sub sp, sp, #4
45 occurrences: add sp, sp, #4 -> pop {pc}
42 occurrences: ldr r1, [sp] -> str r0, [r1, #16]
42 occurrences: str r0, [r1, #16] -> ldr r0, [sp]
38 occurrences: mov r0, #8 -> ldr r1, [sp]
33 occurrences: cmp r8, ip -> bhi 0x5fa0
32 occurrences: mov r2, r6 -> ldr r1, [r5, #48]
32 occurrences: cmp r0, #0 -> bne 0x8204
31 occurrences: cmp fp, ip -> bhi 0x24a0
27 occurrences: add sp, sp, #4 -> bx r0
26 occurrences: str r0, [sp] -> ldr r0, [r4]
25 occurrences: cmp r3, ip -> bhi 0x54bc
24 occurrences: cmp r2, ip -> bhi 0x8f8
23 occurrences: mov r3, r6 -> ldr r2, [r5, #48]
23 occurrences: bic ip, ip, #16646144 -> cmp r3, ip
23 occurrences: cmp r0, #0 -> bne 0x54c8
21 occurrences: mov r3, r2 -> ldr r1, [r5, #48]
20 occurrences: ldr r0, [sp] -> ldr r1, [sp, #12]
19 occurrences: cmp r1, ip -> bhi 0x54bc
19 occurrences: cmp r7, ip -> bhi 0x5fa0
18 occurrences: mov r7, r2 -> ldr r6, [r5, #48]
17 occurrences: ldr r0, [r4] -> ldr r1, [r4, #4]
17 occurrences: mov fp, r1 -> ldr sl, [r5, #48]
17 occurrences: mov r8, r2 -> ldr r7, [r5, #48]
16 occurrences: sub sp, sp, #8 -> str r0, [sp]
16 occurrences: ldr r8, [sl, fp] -> mov fp, r6
16 occurrences: mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: str r1, [r7, r8] -> ldr r8, [r5, #48]
16 occurrences: cmp r6, ip -> bhi 0x5fa0
16 occurrences: mov r8, r0 -> ldr r6, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip]
16 occurrences: str r1, [ip] -> str r7, [ip, #4]
15 occurrences: str r8, [sl, fp] -> mov fp, r1
14 occurrences: cmp r2, ip -> bhi 0x81f8
14 occurrences: str r0, [sp] -> mov lr, r5
13 occurrences: cmp r3, ip -> bhi 0x111c
13 occurrences: bic ip, ip, #16646144 -> cmp r9, ip
12 occurrences: push {r6, lr} -> sub sp, sp, #8
12 occurrences: add sp, sp, #8 -> pop {r6, pc}
12 occurrences: ldr r6, [sp, #8] -> add sp, sp, #16
12 occurrences: add sp, sp, #16 -> bx r0
12 occurrences: cmp r2, ip -> bhi 0x3b38
12 occurrences: ldr r1, [r4] -> ldr r0, [r5, #48]
12 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48]
12 occurrences: ldr r1, [r6, r7] -> mov r6, r1
12 occurrences: mov r6, r1 -> add r1, r1, #4
12 occurrences: add r1, r1, #4 -> mov r8, r2
11 occurrences: ldr r0, [sp] -> ldr r1, [sp, #4]
11 occurrences: add sp, sp, #8 -> bx r0
11 occurrences: mov lr, #0 -> str lr, [r0, r1]
11 occurrences: cmp r3, ip -> bhi 0x8f8
11 occurrences: str r0, [sp] -> ldr r6, [r4]
11 occurrences: ldr r2, [r5, #48] -> adds r3, r3, #48
11 occurrences: bic ip, ip, #16646144 -> cmp r6, ip
11 occurrences: cmp r1, ip -> bhi 0x81f8
11 occurrences: cmp r3, ip -> bhi 0x8a2c
10 occurrences: cmp r1, ip -> bhi 0x8f8
10 occurrences: mov r3, r0 -> ldr r2, [r5, #48]
10 occurrences: cmp r9, ip -> bhi 0x24a0
10 occurrences: ldr r2, [r4] -> ldr r1, [r5, #48]
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432
10 occurrences: adds r3, r3, #48 -> bcs 0x54bc
183 occurrences: blx ip
162 occurrences: cmp r0, #0
128 occurrences: ldr r1, [r5, #48]
120 occurrences: mov r1, r4
120 occurrences: ldr r2, [sp]
120 occurrences: cmp r3, ip
117 occurrences: add sp, sp, #4
111 occurrences: @ <UNDEFINED> instruction: 0x000487b4
89 occurrences: ldr r2, [r5, #48]
87 occurrences: cmp r2, ip
85 occurrences: str r0, [sp]
83 occurrences: mvn ip, #-33554432
83 occurrences: bic ip, ip, #16646144
78 occurrences: bhi 0x54bc
75 occurrences: mov lr, #0
68 occurrences: sub sp, sp, #4
68 occurrences: cmp r1, ip
68 occurrences: bhi 0x5fa0
66 occurrences: ldr r0, [r5, #48]
57 occurrences: cmp r6, ip
56 occurrences: ldr r3, [r5, #48]
52 occurrences: bhi 0x8f8
52 occurrences: bhi 0x81f8
51 occurrences: ldr r0, [sp]
51 occurrences: bx r0
51 occurrences: andeq r7, r4, ip, lsr #29
51 occurrences: ldr r6, [r5, #48]
47 occurrences: cmp r7, ip
46 occurrences: bhi 0x24a0
46 occurrences: bcs 0x54bc
45 occurrences: push {lr}
45 occurrences: pop {pc}
45 occurrences: cmp r8, ip
44 occurrences: bcs 0x8f8
42 occurrences: ldr r1, [sp]
42 occurrences: str r0, [r1, #16]
41 occurrences: ldr r0, [r1, r2]
39 occurrences: cmp fp, ip
38 occurrences: mov r0, #8
37 occurrences: mov r2, r6
36 occurrences: ldr sl, [r5, #48]
36 occurrences: bcs 0x24a0
34 occurrences: mov r3, r2
34 occurrences: mov r1, r0
33 occurrences: cmp ip, #0
33 occurrences: ldr r8, [r5, #48]
32 occurrences: str r0, [r4]
32 occurrences: ldr r7, [r5, #48]
32 occurrences: bne 0x8204
31 occurrences: add sp, sp, #8
31 occurrences: ldr ip, [r4, #28]
27 occurrences: ldr r0, [r4]
26 occurrences: bhi 0x28cc
25 occurrences: ldr r1, [r2, r3]
25 occurrences: cmp r0, ip
25 occurrences: mov r7, r2
24 occurrences: mov r3, r6
24 occurrences: bhi 0x1ae8
24 occurrences: mov r8, r0
23 occurrences: ldr ip, [r4, #20]
23 occurrences: bne 0x54c8
22 occurrences: cmp r9, ip
22 occurrences: str lr, [r4, #4]
22 occurrences: ldr ip, [r4, #64]
21 occurrences: str r1, [ip]
21 occurrences: mov ip, #0
21 occurrences: bhi 0x3b38
20 occurrences: mov r0, #0
20 occurrences: mov r2, r1
20 occurrences: mov r2, r0
20 occurrences: ldr r1, [sp, #12]
20 occurrences: mov r6, r0
20 occurrences: mov fp, r1
19 occurrences: mov r3, r0
19 occurrences: mov r6, r1
19 occurrences: mov r8, r2
19 occurrences: ldr ip, [r4, #80]
19 occurrences: ldr ip, [r4, #84]
18 occurrences: ldr lr, [r5, #60]
18 occurrences: mov r3, r1
18 occurrences: ldr r1, [r4, #4]
18 occurrences: ldr r0, [r1, r3]
18 occurrences: bcs 0x1ae8
18 occurrences: mov lr, #1
18 occurrences: ldr ip, [r4, #16]
17 occurrences: mov lr, #64, 22
17 occurrences: bcs 0x111c
17 occurrences: bhi 0x111c
17 occurrences: cmp r1, #0
17 occurrences: mov fp, r6
17 occurrences: mov r1, #0
17 occurrences: bcs 0x3b38
17 occurrences: ldr r1, [r6, r7]
17 occurrences: str r1, [r7, r8]
17 occurrences: b 0x5f98
16 occurrences: sub sp, sp, #8
16 occurrences: ldr r8, [sl, fp]
16 occurrences: str r8, [sl, fp]
16 occurrences: add ip, r6, r8
16 occurrences: str r7, [ip, #4]
15 occurrences: mov r6, r2
15 occurrences: mov r7, #0
15 occurrences: str lr, [r4, #92]
14 occurrences: str lr, [r0, r1]
14 occurrences: str r0, [r1, r2]
14 occurrences: ldr r0, [r2, r3]
14 occurrences: add r1, r1, #4
14 occurrences: str lr, [r4, #52]
14 occurrences: ldr r3, [r4, #28]
14 occurrences: str lr, [r4, #84]
14 occurrences: ldr r2, [r4, #28]
14 occurrences: ldr ip, [r4, #72]
14 occurrences: mov lr, #48
14 occurrences: bhi 0x8a2c
14 occurrences: mov lr, r5
13 occurrences: mov r7, r0
13 occurrences: ldr r1, [ip]
13 occurrences: mov r0, r1
13 occurrences: push {r6, lr}
13 occurrences: pop {r6, pc}
13 occurrences: add sp, sp, #16
13 occurrences: cmp r6, #0
13 occurrences: ldr ip, [r4, #12]
13 occurrences: mov r3, #0
13 occurrences: mov r6, r7
13 occurrences: str lr, [r4, #40]
13 occurrences: str lr, [r4, #164]
12 occurrences: adds r3, r3, #48
12 occurrences: adds r3, r3, #12
12 occurrences: str r6, [r4]
12 occurrences: ldr r6, [sp, #8]
12 occurrences: mov r2, #0
12 occurrences: bcs 0x28cc
12 occurrences: ldr r1, [r4]
12 occurrences: ldr ip, [r4, #44]
12 occurrences: bcs 0x81f8
11 occurrences: ldr r1, [sp, #4]
11 occurrences: add r0, r0, r1
11 occurrences: mov r6, #0
11 occurrences: ldr r6, [r4]
11 occurrences: str lr, [r4, #44]
11 occurrences: cmp r2, #0
11 occurrences: mov sl, r1
11 occurrences: ldr r2, [r4]
11 occurrences: mvn lr, #0
11 occurrences: str lr, [r4, #36]
11 occurrences: mov lr, #32
10 occurrences: ldr r1, [r5, #60]
10 occurrences: adds r3, r3, #8
10 occurrences: ldr r0, [r4, #4]
10 occurrences: str lr, [r4, #16]
10 occurrences: str lr, [r4]
10 occurrences: ldr r2, [r4, #8]
10 occurrences: bhi 0x2ea0
10 occurrences: bhi 0x3600
10 occurrences: ldr ip, [r4, #24]
10 occurrences: ldr ip, [r4]
[END] Finished processing log file: dispatcher-2026-04-28-21:54:01.bin.log

12 occurrences: ldr r1, [r6, r7] -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
11 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
31 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
12 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
12 occurrences: ldr r1, [r6, r7] -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
12 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
10 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r9, ip -> bhi 0x1554
10 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48] -> adds r3, r3, #48 -> bcs 0x4554
40 occurrences: push {lr} -> sub sp, sp, #4 -> str r0, [sp]
35 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
31 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16]
23 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r3, ip
16 occurrences: sub sp, sp, #4 -> str r0, [sp] -> ldr r0, [r4]
16 occurrences: ldr r8, [sl, fp] -> mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip] -> str r7, [ip, #4]
15 occurrences: str r8, [sl, fp] -> mov fp, r1 -> ldr sl, [r5, #48]
13 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r9, ip
12 occurrences: str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
12 occurrences: ldr r1, [r6, r7] -> mov r6, r1 -> add r1, r1, #4
12 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
12 occurrences: add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
11 occurrences: str r0, [sp] -> ldr r0, [r4] -> ldr r1, [r4, #4]
11 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r6, ip
10 occurrences: bic ip, ip, #16646144 -> cmp r9, ip -> bhi 0x1554
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432 -> bic ip, ip, #16646144
10 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48] -> adds r3, r3, #48
10 occurrences: ldr r2, [r5, #48] -> adds r3, r3, #48 -> bcs 0x4554
119 occurrences: mov r1, r4 -> ldr r2, [sp]
83 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144
61 occurrences: sub sp, sp, #4 -> str r0, [sp]
40 occurrences: push {lr} -> sub sp, sp, #4
40 occurrences: add sp, sp, #4 -> pop {pc}
36 occurrences: str r0, [r1, #16] -> ldr r0, [sp]
35 occurrences: ldr r1, [sp] -> str r0, [r1, #16]
33 occurrences: cmp r8, ip -> bhi 0x5030
32 occurrences: mov r0, #8 -> ldr r1, [sp]
32 occurrences: cmp fp, ip -> bhi 0x1554
32 occurrences: cmp r0, #0 -> bne 0x7294
27 occurrences: add sp, sp, #4 -> bx r0
25 occurrences: cmp r3, ip -> bhi 0x4554
23 occurrences: bic ip, ip, #16646144 -> cmp r3, ip
23 occurrences: cmp r0, #0 -> bne 0x4560
20 occurrences: str r0, [sp] -> ldr r0, [r4]
19 occurrences: cmp r1, ip -> bhi 0x4554
19 occurrences: cmp r7, ip -> bhi 0x5030
18 occurrences: mov r7, r2 -> ldr r6, [r5, #48]
17 occurrences: mov fp, r1 -> ldr sl, [r5, #48]
17 occurrences: mov r8, r2 -> ldr r7, [r5, #48]
16 occurrences: ldr r8, [sl, fp] -> mov fp, r6
16 occurrences: mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: str r1, [r7, r8] -> ldr r8, [r5, #48]
16 occurrences: cmp r6, ip -> bhi 0x5030
16 occurrences: mov r8, r0 -> ldr r6, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip]
16 occurrences: str r1, [ip] -> str r7, [ip, #4]
15 occurrences: mov r3, r6 -> ldr r2, [r5, #48]
15 occurrences: str r8, [sl, fp] -> mov fp, r1
14 occurrences: cmp r2, ip -> bhi 0x7288
13 occurrences: ldr r0, [sp] -> ldr r1, [sp, #12]
13 occurrences: bic ip, ip, #16646144 -> cmp r9, ip
12 occurrences: ldr r0, [sp] -> ldr r1, [sp, #4]
12 occurrences: add sp, sp, #8 -> bx r0
12 occurrences: mov r2, r6 -> ldr r1, [r5, #48]
12 occurrences: cmp r2, ip -> bhi 0x2bd0
12 occurrences: ldr r1, [r4] -> ldr r0, [r5, #48]
12 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48]
12 occurrences: ldr r1, [r6, r7] -> mov r6, r1
12 occurrences: mov r6, r1 -> add r1, r1, #4
12 occurrences: add r1, r1, #4 -> mov r8, r2
11 occurrences: str r0, [sp] -> ldr r6, [r4]
11 occurrences: ldr r0, [r4] -> ldr r1, [r4, #4]
11 occurrences: ldr r2, [r5, #48] -> adds r3, r3, #48
11 occurrences: bic ip, ip, #16646144 -> cmp r6, ip
11 occurrences: cmp r1, ip -> bhi 0x7288
11 occurrences: cmp r3, ip -> bhi 0x7ab8
10 occurrences: cmp r9, ip -> bhi 0x1554
10 occurrences: ldr r2, [r4] -> ldr r1, [r5, #48]
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432
10 occurrences: adds r3, r3, #48 -> bcs 0x4554
175 occurrences: blx ip
161 occurrences: cmp r0, #0
119 occurrences: mov r1, r4
119 occurrences: ldr r2, [sp]
112 occurrences: add sp, sp, #4
111 occurrences: @ <UNDEFINED> instruction: 0x000487b4
85 occurrences: ldr r1, [r5, #48]
83 occurrences: mvn ip, #-33554432
83 occurrences: bic ip, ip, #16646144
81 occurrences: cmp r3, ip
78 occurrences: bhi 0x4554
77 occurrences: ldr r2, [r5, #48]
73 occurrences: str r0, [sp]
70 occurrences: mov lr, #0
68 occurrences: bhi 0x5030
63 occurrences: sub sp, sp, #4
62 occurrences: cmp r2, ip
61 occurrences: cmp r1, ip
52 occurrences: bhi 0x7288
51 occurrences: ldr r0, [r5, #48]
51 occurrences: ldr r6, [r5, #48]
48 occurrences: cmp r6, ip
46 occurrences: bhi 0x1554
46 occurrences: bcs 0x4554
45 occurrences: ldr r0, [sp]
45 occurrences: bx r0
45 occurrences: andeq r7, r4, ip, lsr #29
45 occurrences: cmp r8, ip
41 occurrences: cmp r7, ip
40 occurrences: push {lr}
40 occurrences: pop {pc}
39 occurrences: ldr r3, [r5, #48]
39 occurrences: cmp fp, ip
36 occurrences: ldr r1, [sp]
36 occurrences: str r0, [r1, #16]
36 occurrences: ldr sl, [r5, #48]
36 occurrences: bcs 0x1554
34 occurrences: mov r1, r0
33 occurrences: cmp ip, #0
33 occurrences: ldr r8, [r5, #48]
32 occurrences: mov r0, #8
32 occurrences: ldr r7, [r5, #48]
32 occurrences: bne 0x7294
31 occurrences: ldr ip, [r4, #28]
28 occurrences: ldr r0, [r1, r2]
26 occurrences: str r0, [r4]
26 occurrences: bhi 0x1980
25 occurrences: add sp, sp, #8
24 occurrences: bhi 0xb8c
24 occurrences: cmp r0, ip
24 occurrences: mov r7, r2
24 occurrences: mov r8, r0
23 occurrences: ldr ip, [r4, #20]
23 occurrences: bne 0x4560
22 occurrences: cmp r9, ip
22 occurrences: str lr, [r4, #4]
22 occurrences: ldr ip, [r4, #64]
21 occurrences: ldr r0, [r4]
21 occurrences: mov ip, #0
21 occurrences: bhi 0x2bd0
20 occurrences: mov r6, r0
20 occurrences: mov fp, r1
19 occurrences: ldr r1, [r2, r3]
19 occurrences: mov r2, r0
19 occurrences: mov r8, r2
19 occurrences: ldr ip, [r4, #80]
19 occurrences: ldr ip, [r4, #84]
18 occurrences: mov r3, r1
18 occurrences: bcs 0xb8c
18 occurrences: mov lr, #1
18 occurrences: ldr ip, [r4, #16]
18 occurrences: str r1, [ip]
18 occurrences: mov r6, r1
17 occurrences: mov r2, r6
17 occurrences: mov lr, #64, 22
17 occurrences: mov r2, r1
17 occurrences: mov r3, r0
17 occurrences: cmp r1, #0
17 occurrences: mov fp, r6
17 occurrences: mov r1, #0
17 occurrences: bcs 0x2bd0
17 occurrences: ldr r1, [r6, r7]
17 occurrences: str r1, [r7, r8]
17 occurrences: b 0x5028
16 occurrences: ldr r8, [sl, fp]
16 occurrences: str r8, [sl, fp]
16 occurrences: add ip, r6, r8
16 occurrences: str r7, [ip, #4]
15 occurrences: mov r3, r6
15 occurrences: mov r7, #0
15 occurrences: str lr, [r4, #92]
14 occurrences: mov r0, #0
14 occurrences: add r1, r1, #4
14 occurrences: str lr, [r4, #52]
14 occurrences: ldr r3, [r4, #28]
14 occurrences: str lr, [r4, #84]
14 occurrences: ldr r2, [r4, #28]
14 occurrences: ldr ip, [r4, #72]
14 occurrences: mov lr, #48
14 occurrences: bhi 0x7ab8
13 occurrences: ldr r1, [sp, #12]
13 occurrences: cmp r6, #0
13 occurrences: ldr ip, [r4, #12]
13 occurrences: mov r3, #0
13 occurrences: mov r6, r7
13 occurrences: str lr, [r4, #40]
13 occurrences: str lr, [r4, #164]
12 occurrences: ldr r1, [sp, #4]
12 occurrences: ldr lr, [r5, #60]
12 occurrences: str r6, [r4]
12 occurrences: ldr r1, [r4, #4]
12 occurrences: mov r0, r1
12 occurrences: mov r2, #0
12 occurrences: bcs 0x1980
12 occurrences: ldr r1, [r4]
12 occurrences: ldr ip, [r4, #44]
12 occurrences: bcs 0x7288
11 occurrences: ldr r0, [r2, r3]
11 occurrences: mov r6, #0
11 occurrences: ldr r6, [r4]
11 occurrences: str lr, [r4, #44]
11 occurrences: adds r3, r3, #48
11 occurrences: cmp r2, #0
11 occurrences: mov sl, r1
11 occurrences: ldr r2, [r4]
11 occurrences: mvn lr, #0
11 occurrences: mov r7, r0
11 occurrences: str lr, [r4, #36]
11 occurrences: mov lr, #32
10 occurrences: ldr r1, [r5, #60]
10 occurrences: ldr r0, [r4, #4]
10 occurrences: str lr, [r4, #16]
10 occurrences: str lr, [r4]
10 occurrences: ldr r2, [r4, #8]
10 occurrences: bhi 0x1f44
10 occurrences: bhi 0x2698
10 occurrences: ldr ip, [r4, #24]
10 occurrences: ldr ip, [r4]
10 occurrences: ldr r1, [ip]
[END] Finished processing log file: square-2026-04-28-21:54:02.bin.log

12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
10 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
32 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
12 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
11 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
10 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #20]
38 occurrences: push {lr} -> sub sp, sp, #4 -> str r0, [sp]
36 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
32 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16]
16 occurrences: @ <UNDEFINED> instruction: 0xe7e8abf4 -> mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip] -> str r7, [ip, #4]
15 occurrences: @ <UNDEFINED> instruction: 0xe7d8abf4 -> mov fp, r1 -> ldr sl, [r5, #48]
14 occurrences: sub sp, sp, #4 -> str r0, [sp] -> ldr r0, [r4]
14 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r3, ip
12 occurrences: str r0, [sp] -> ldr r0, [r4] -> ldr r1, [r4, #4]
12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1 -> add r1, r1, #4
12 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
12 occurrences: add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
11 occurrences: str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
10 occurrences: str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #20]
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432 -> bic ip, ip, #16646144
120 occurrences: mov r1, r4 -> ldr r2, [sp]
58 occurrences: sub sp, sp, #4 -> str r0, [sp]
53 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144
39 occurrences: push {lr} -> sub sp, sp, #4
39 occurrences: add sp, sp, #4 -> pop {pc}
36 occurrences: ldr r1, [sp] -> str r0, [r1, #16]
36 occurrences: str r0, [r1, #16] -> ldr r0, [sp]
33 occurrences: cmp r8, ip -> bhi 0x4cd8
32 occurrences: mov r0, #8 -> ldr r1, [sp]
32 occurrences: cmp r0, #0 -> bne 0x6e90
31 occurrences: mvn lr, #-33554432 -> bic lr, lr, #16646144
28 occurrences: add sp, sp, #4 -> bx r0
23 occurrences: cmp r0, #0 -> bne 0x412c
21 occurrences: mov r3, r6 -> ldr r2, [r5, #48]
20 occurrences: str r0, [sp] -> ldr r0, [r4]
19 occurrences: cmp r7, ip -> bhi 0x4cd8
18 occurrences: mov r7, r2 -> ldr r6, [r5, #48]
17 occurrences: mov fp, r1 -> ldr sl, [r5, #48]
17 occurrences: mov r8, r2 -> ldr r7, [r5, #48]
16 occurrences: @ <UNDEFINED> instruction: 0xe7e8abf4 -> mov fp, r6
16 occurrences: mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: @ <UNDEFINED> instruction: 0xe7d178f4 -> ldr r8, [r5, #48]
16 occurrences: cmp r6, ip -> bhi 0x4cd8
16 occurrences: mov r8, r0 -> ldr r6, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip]
16 occurrences: str r1, [ip] -> str r7, [ip, #4]
15 occurrences: @ <UNDEFINED> instruction: 0xe7d8abf4 -> mov fp, r1
14 occurrences: bic ip, ip, #16646144 -> cmp r3, ip
12 occurrences: ldr r0, [r4] -> ldr r1, [r4, #4]
12 occurrences: ldr r0, [sp] -> ldr r1, [sp, #12]
12 occurrences: ldr r1, [r4] -> ldr r0, [r5, #48]
12 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48]
12 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4 -> mov r6, r1
12 occurrences: mov r6, r1 -> add r1, r1, #4
12 occurrences: add r1, r1, #4 -> mov r8, r2
11 occurrences: ldr r0, [sp] -> ldr r1, [sp, #4]
11 occurrences: add sp, sp, #8 -> bx r0
11 occurrences: sub sp, sp, #8 -> str r0, [sp]
11 occurrences: ldr r0, [sp] -> ldr r1, [sp, #20]
11 occurrences: str r0, [sp] -> ldr r6, [r4]
11 occurrences: cmp r1, ip -> bhi 0x4120
10 occurrences: mov r2, r6 -> ldr r1, [r5, #48]
10 occurrences: ldr r2, [r4] -> ldr r1, [r5, #48]
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432
10 occurrences: cmp r3, ip -> bhi 0x4120
10 occurrences: udf #15920 -> bcs 0x4120
10 occurrences: cmp r1, ip -> bhi 0x6e84
176 occurrences: blx ip
162 occurrences: cmp r0, #0
120 occurrences: mov r1, r4
120 occurrences: ldr r2, [sp]
112 occurrences: andeq r8, r4, ip, lsl #18
110 occurrences: add sp, sp, #4
83 occurrences: ldr r1, [r5, #48]
80 occurrences: ldr r2, [r5, #48]
73 occurrences: str r0, [sp]
68 occurrences: bhi 0x4cd8
61 occurrences: sub sp, sp, #4
61 occurrences: mov lr, #0
54 occurrences: ldr r0, [r5, #48]
53 occurrences: mvn ip, #-33554432
53 occurrences: bic ip, ip, #16646144
51 occurrences: ldr r6, [r5, #48]
46 occurrences: bcs 0x4120
45 occurrences: ldr r0, [sp]
45 occurrences: bx r0
45 occurrences: andeq r8, r4, r4
42 occurrences: cmp r3, ip
40 occurrences: bhi 0x6e84
39 occurrences: push {lr}
39 occurrences: pop {pc}
39 occurrences: ldr r3, [r5, #48]
39 occurrences: cmp r8, ip
38 occurrences: cmp r1, ip
36 occurrences: ldr r1, [sp]
36 occurrences: str r0, [r1, #16]
36 occurrences: ldr sl, [r5, #48]
36 occurrences: bcs 0x14c8
34 occurrences: mov r1, r0
34 occurrences: cmp r7, ip
33 occurrences: cmp ip, #0
33 occurrences: ldr r8, [r5, #48]
32 occurrences: mov r0, #8
32 occurrences: ldr r7, [r5, #48]
32 occurrences: bhi 0x4120
32 occurrences: bne 0x6e90
31 occurrences: ldr ip, [r4, #28]
31 occurrences: mvn lr, #-33554432
31 occurrences: bic lr, lr, #16646144
30 occurrences: cmp r6, ip
28 occurrences: add sp, sp, #8
27 occurrences: @ <UNDEFINED> instruction: 0xe7e012f4
26 occurrences: str r0, [r4]
24 occurrences: mov r7, r2
24 occurrences: mov r8, r0
23 occurrences: ldr ip, [r4, #20]
23 occurrences: bne 0x412c
22 occurrences: cmp r0, ip
22 occurrences: str lr, [r4, #4]
22 occurrences: ldr ip, [r4, #64]
21 occurrences: ldr r0, [r4]
21 occurrences: mov r3, r6
21 occurrences: mov ip, #0
20 occurrences: mov r8, r2
20 occurrences: mov r6, r0
20 occurrences: mov fp, r1
19 occurrences: mov r1, #0
19 occurrences: mov r2, #0
19 occurrences: mov r2, r0
19 occurrences: ldr ip, [r4, #80]
19 occurrences: ldr ip, [r4, #84]
18 occurrences: bcs 0xc10
18 occurrences: @ <UNDEFINED> instruction: 0xe7e123f4
18 occurrences: mov lr, #1
18 occurrences: ldr ip, [r4, #16]
18 occurrences: str r1, [ip]
18 occurrences: mov r6, r1
17 occurrences: mov lr, #64, 22
17 occurrences: cmp r2, ip
17 occurrences: mov r2, r1
17 occurrences: mov r3, r0
17 occurrences: cmp r1, #0
17 occurrences: mov fp, r6
17 occurrences: bcs 0x29b0
17 occurrences: @ <UNDEFINED> instruction: 0xe7e167f4
17 occurrences: @ <UNDEFINED> instruction: 0xe7d178f4
17 occurrences: b 0x4cd0
16 occurrences: mov r0, #0
16 occurrences: @ <UNDEFINED> instruction: 0xe7e8abf4
16 occurrences: @ <UNDEFINED> instruction: 0xe7d8abf4
16 occurrences: add ip, r6, r8
16 occurrences: str r7, [ip, #4]
15 occurrences: mov r2, r6
15 occurrences: mov r3, r1
15 occurrences: mov r7, #0
15 occurrences: str lr, [r4, #92]
14 occurrences: mov r3, #0
14 occurrences: add r1, r1, #4
14 occurrences: bhi 0x1894
14 occurrences: str lr, [r4, #52]
14 occurrences: ldr r3, [r4, #28]
14 occurrences: str lr, [r4, #84]
14 occurrences: ldr r2, [r4, #28]
14 occurrences: ldr ip, [r4, #72]
13 occurrences: ldr r1, [r4, #4]
13 occurrences: cmp r6, #0
13 occurrences: ldr ip, [r4, #12]
13 occurrences: mov r6, r7
13 occurrences: str lr, [r4, #40]
13 occurrences: str lr, [r4, #164]
12 occurrences: ldr lr, [r5, #60]
12 occurrences: mov r7, r0
12 occurrences: str r6, [r4]
12 occurrences: ldr r1, [sp, #12]
12 occurrences: mov r0, r1
12 occurrences: bcs 0x1894
12 occurrences: ldr r1, [r4]
12 occurrences: ldr ip, [r4, #44]
12 occurrences: bcs 0x6e84
11 occurrences: ldr r1, [sp, #4]
11 occurrences: sub sp, sp, #8
11 occurrences: add r0, r0, r1
11 occurrences: ldr r1, [sp, #20]
11 occurrences: mov r6, #0
11 occurrences: ldr r6, [r4]
11 occurrences: str lr, [r4, #44]
11 occurrences: udf #15920
11 occurrences: cmp r2, #0
11 occurrences: mov sl, r1
11 occurrences: ldr r2, [r4]
11 occurrences: mvn lr, #0
11 occurrences: str lr, [r4, #36]
11 occurrences: mov lr, #32
10 occurrences: ldr r1, [r5, #60]
10 occurrences: str r0, [r4, #4]
10 occurrences: ldr r0, [r4, #4]
10 occurrences: str lr, [r4, #16]
10 occurrences: str lr, [r4]
10 occurrences: ldr r2, [r4, #8]
10 occurrences: cmp r9, ip
10 occurrences: bhi 0x14c8
10 occurrences: ldr ip, [r4, #24]
10 occurrences: ldr ip, [r4]
10 occurrences: ldr r1, [ip]
[END] Finished processing log file: factorial-2026-04-28-21:54:05.bin.log

12 occurrences: ldr r1, [r6, r7] -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
11 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
31 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
12 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
12 occurrences: ldr r1, [r6, r7] -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
12 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
10 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r9, ip -> bhi 0x13c4
10 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48] -> adds r3, r3, #48 -> bcs 0x43c4
39 occurrences: push {lr} -> sub sp, sp, #4 -> str r0, [sp]
35 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
31 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16]
23 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r3, ip
16 occurrences: ldr r8, [sl, fp] -> mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip] -> str r7, [ip, #4]
15 occurrences: sub sp, sp, #4 -> str r0, [sp] -> ldr r0, [r4]
15 occurrences: str r8, [sl, fp] -> mov fp, r1 -> ldr sl, [r5, #48]
13 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r9, ip
12 occurrences: str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
12 occurrences: ldr r1, [r6, r7] -> mov r6, r1 -> add r1, r1, #4
12 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
12 occurrences: add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
11 occurrences: str r0, [sp] -> ldr r0, [r4] -> ldr r1, [r4, #4]
11 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r6, ip
10 occurrences: bic ip, ip, #16646144 -> cmp r9, ip -> bhi 0x13c4
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432 -> bic ip, ip, #16646144
10 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48] -> adds r3, r3, #48
10 occurrences: ldr r2, [r5, #48] -> adds r3, r3, #48 -> bcs 0x43c4
117 occurrences: mov r1, r4 -> ldr r2, [sp]
83 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144
59 occurrences: sub sp, sp, #4 -> str r0, [sp]
39 occurrences: push {lr} -> sub sp, sp, #4
39 occurrences: add sp, sp, #4 -> pop {pc}
35 occurrences: ldr r1, [sp] -> str r0, [r1, #16]
35 occurrences: str r0, [r1, #16] -> ldr r0, [sp]
33 occurrences: cmp r8, ip -> bhi 0x4ea4
32 occurrences: cmp fp, ip -> bhi 0x13c4
32 occurrences: cmp r0, #0 -> bne 0x70f4
31 occurrences: mov r0, #8 -> ldr r1, [sp]
26 occurrences: add sp, sp, #4 -> bx r0
25 occurrences: cmp r3, ip -> bhi 0x43c4
23 occurrences: bic ip, ip, #16646144 -> cmp r3, ip
23 occurrences: cmp r0, #0 -> bne 0x43d0
19 occurrences: str r0, [sp] -> ldr r0, [r4]
19 occurrences: cmp r1, ip -> bhi 0x43c4
19 occurrences: cmp r7, ip -> bhi 0x4ea4
18 occurrences: mov r7, r2 -> ldr r6, [r5, #48]
17 occurrences: mov fp, r1 -> ldr sl, [r5, #48]
17 occurrences: mov r8, r2 -> ldr r7, [r5, #48]
16 occurrences: ldr r8, [sl, fp] -> mov fp, r6
16 occurrences: mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: str r1, [r7, r8] -> ldr r8, [r5, #48]
16 occurrences: cmp r6, ip -> bhi 0x4ea4
16 occurrences: mov r8, r0 -> ldr r6, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip]
16 occurrences: str r1, [ip] -> str r7, [ip, #4]
15 occurrences: mov r3, r6 -> ldr r2, [r5, #48]
15 occurrences: str r8, [sl, fp] -> mov fp, r1
14 occurrences: cmp r2, ip -> bhi 0x70e8
13 occurrences: ldr r0, [sp] -> ldr r1, [sp, #12]
13 occurrences: bic ip, ip, #16646144 -> cmp r9, ip
12 occurrences: cmp r2, ip -> bhi 0x2a50
12 occurrences: ldr r1, [r4] -> ldr r0, [r5, #48]
12 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48]
12 occurrences: ldr r1, [r6, r7] -> mov r6, r1
12 occurrences: mov r6, r1 -> add r1, r1, #4
12 occurrences: add r1, r1, #4 -> mov r8, r2
11 occurrences: ldr r0, [sp] -> ldr r1, [sp, #4]
11 occurrences: add sp, sp, #8 -> bx r0
11 occurrences: str r0, [sp] -> ldr r6, [r4]
11 occurrences: ldr r0, [r4] -> ldr r1, [r4, #4]
11 occurrences: ldr r2, [r5, #48] -> adds r3, r3, #48
11 occurrences: bic ip, ip, #16646144 -> cmp r6, ip
11 occurrences: cmp r1, ip -> bhi 0x70e8
11 occurrences: cmp r3, ip -> bhi 0x792c
10 occurrences: sub sp, sp, #8 -> str r0, [sp]
10 occurrences: mov r2, r6 -> ldr r1, [r5, #48]
10 occurrences: cmp r9, ip -> bhi 0x13c4
10 occurrences: ldr r2, [r4] -> ldr r1, [r5, #48]
10 occurrences: ldr r2, [r5, #48] -> mvn ip, #-33554432
10 occurrences: adds r3, r3, #48 -> bcs 0x43c4
173 occurrences: blx ip
160 occurrences: cmp r0, #0
118 occurrences: mov r1, r4
118 occurrences: ldr r2, [sp]
110 occurrences: @ <UNDEFINED> instruction: 0x000487b4
108 occurrences: add sp, sp, #4
83 occurrences: ldr r1, [r5, #48]
83 occurrences: mvn ip, #-33554432
83 occurrences: bic ip, ip, #16646144
78 occurrences: cmp r3, ip
78 occurrences: bhi 0x43c4
74 occurrences: ldr r2, [r5, #48]
72 occurrences: str r0, [sp]
71 occurrences: mov lr, #0
68 occurrences: bhi 0x4ea4
61 occurrences: sub sp, sp, #4
60 occurrences: cmp r2, ip
58 occurrences: cmp r1, ip
52 occurrences: bhi 0x70e8
51 occurrences: ldr r6, [r5, #48]
48 occurrences: ldr r0, [r5, #48]
48 occurrences: cmp r6, ip
46 occurrences: bhi 0x13c4
46 occurrences: bcs 0x43c4
45 occurrences: cmp r8, ip
44 occurrences: ldr r0, [sp]
44 occurrences: bx r0
44 occurrences: andeq r7, r4, ip, lsr #29
41 occurrences: cmp r7, ip
39 occurrences: push {lr}
39 occurrences: pop {pc}
39 occurrences: ldr r3, [r5, #48]
39 occurrences: cmp fp, ip
36 occurrences: ldr sl, [r5, #48]
36 occurrences: bcs 0x13c4
35 occurrences: ldr r1, [sp]
35 occurrences: str r0, [r1, #16]
34 occurrences: mov r1, r0
33 occurrences: cmp ip, #0
33 occurrences: ldr r8, [r5, #48]
32 occurrences: ldr r7, [r5, #48]
32 occurrences: bne 0x70f4
31 occurrences: mov r0, #8
31 occurrences: ldr ip, [r4, #28]
27 occurrences: ldr r0, [r1, r2]
26 occurrences: str r0, [r4]
26 occurrences: bhi 0x17f0
25 occurrences: add sp, sp, #8
24 occurrences: bhi 0x9fc
24 occurrences: cmp r0, ip
24 occurrences: mov r7, r2
24 occurrences: mov r8, r0
23 occurrences: ldr ip, [r4, #20]
23 occurrences: bne 0x43d0
22 occurrences: cmp r9, ip
22 occurrences: str lr, [r4, #4]
22 occurrences: ldr ip, [r4, #64]
21 occurrences: mov ip, #0
21 occurrences: bhi 0x2a50
20 occurrences: mov r6, r0
20 occurrences: ldr r0, [r4]
20 occurrences: mov fp, r1
19 occurrences: mov r2, r0
19 occurrences: mov r8, r2
19 occurrences: ldr ip, [r4, #80]
19 occurrences: ldr ip, [r4, #84]
18 occurrences: bcs 0x9fc
18 occurrences: ldr r1, [r2, r3]
18 occurrences: mov lr, #1
18 occurrences: ldr ip, [r4, #16]
18 occurrences: str r1, [ip]
18 occurrences: mov r6, r1
17 occurrences: mov lr, #64, 22
17 occurrences: mov r2, r1
17 occurrences: mov r3, r0
17 occurrences: cmp r1, #0
17 occurrences: mov fp, r6
17 occurrences: mov r1, #0
17 occurrences: bcs 0x2a50
17 occurrences: ldr r1, [r6, r7]
17 occurrences: str r1, [r7, r8]
17 occurrences: b 0x4e9c
16 occurrences: ldr r8, [sl, fp]
16 occurrences: str r8, [sl, fp]
16 occurrences: add ip, r6, r8
16 occurrences: str r7, [ip, #4]
15 occurrences: mov r3, r6
15 occurrences: mov r2, r6
15 occurrences: mov r3, r1
15 occurrences: mov r7, #0
15 occurrences: str lr, [r4, #92]
14 occurrences: mov r0, #0
14 occurrences: add r1, r1, #4
14 occurrences: str lr, [r4, #52]
14 occurrences: ldr r3, [r4, #28]
14 occurrences: str lr, [r4, #84]
14 occurrences: ldr r2, [r4, #28]
14 occurrences: ldr ip, [r4, #72]
14 occurrences: mov lr, #48
14 occurrences: bhi 0x792c
13 occurrences: ldr r1, [sp, #12]
13 occurrences: cmp r6, #0
13 occurrences: ldr ip, [r4, #12]
13 occurrences: mov r3, #0
13 occurrences: mov r6, r7
13 occurrences: str lr, [r4, #40]
13 occurrences: str lr, [r4, #164]
12 occurrences: ldr r1, [r4, #4]
12 occurrences: mov r0, r1
12 occurrences: mov r2, #0
12 occurrences: bcs 0x17f0
12 occurrences: ldr r1, [r4]
12 occurrences: ldr ip, [r4, #44]
12 occurrences: bcs 0x70e8
11 occurrences: ldr r1, [sp, #4]
11 occurrences: ldr lr, [r5, #60]
11 occurrences: str lr, [r4, #16]
11 occurrences: mov r6, #0
11 occurrences: ldr r6, [r4]
11 occurrences: str r6, [r4]
11 occurrences: str lr, [r4, #44]
11 occurrences: adds r3, r3, #48
11 occurrences: cmp r2, #0
11 occurrences: mov sl, r1
11 occurrences: ldr r2, [r4]
11 occurrences: mvn lr, #0
11 occurrences: mov r7, r0
11 occurrences: str lr, [r4, #36]
11 occurrences: mov lr, #32
10 occurrences: sub sp, sp, #8
10 occurrences: ldr r1, [r5, #60]
10 occurrences: str r0, [r4, #4]
10 occurrences: ldr r0, [r4, #4]
10 occurrences: ldr r0, [r2, r3]
10 occurrences: str lr, [r4]
10 occurrences: ldr r2, [r4, #8]
10 occurrences: bhi 0x1dc4
10 occurrences: bhi 0x2510
10 occurrences: ldr ip, [r4, #24]
10 occurrences: ldr ip, [r4]
10 occurrences: ldr r1, [ip]
[END] Finished processing log file: helloworld-2026-04-28-21:54:02.bin.log

12 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
11 occurrences: ldr r1, [r6, r7] -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
34 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
13 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
11 occurrences: sub sp, sp, #4 -> str r0, [sp] -> ldr r0, [r4] -> ldr r1, [r4, #4]
11 occurrences: ldr r1, [r6, r7] -> mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
11 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
10 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #20]
10 occurrences: str r0, [sp] -> ldr r0, [r4] -> ldr r1, [r4, #4] -> ldr r2, [r4, #8]
10 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r9, ip -> bhi 0x2058
10 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48] -> adds r3, r3, #48 -> bcs 0x5058
40 occurrences: push {lr} -> sub sp, sp, #4 -> str r0, [sp]
38 occurrences: ldr r1, [sp] -> str r0, [r1, #16] -> ldr r0, [sp]
34 occurrences: mov r0, #8 -> ldr r1, [sp] -> str r0, [r1, #16]
23 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r3, ip
18 occurrences: sub sp, sp, #4 -> str r0, [sp] -> ldr r0, [r4]
16 occurrences: ldr r8, [sl, fp] -> mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip] -> str r7, [ip, #4]
15 occurrences: str r8, [sl, fp] -> mov fp, r1 -> ldr sl, [r5, #48]
13 occurrences: str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #12]
13 occurrences: str r0, [sp] -> ldr r0, [r4] -> ldr r1, [r4, #4]
13 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r9, ip
12 occurrences: ldr r1, [r6, r7] -> mov r6, r1 -> add r1, r1, #4
11 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144 -> cmp r6, ip
11 occurrences: mov r6, r1 -> add r1, r1, #4 -> mov r8, r2
11 occurrences: add r1, r1, #4 -> mov r8, r2 -> ldr r7, [r5, #48]
10 occurrences: str r0, [r1, #16] -> ldr r0, [sp] -> ldr r1, [sp, #20]
10 occurrences: ldr r0, [r4] -> ldr r1, [r4, #4] -> ldr r2, [r4, #8]
10 occurrences: bic ip, ip, #16646144 -> cmp r9, ip -> bhi 0x2058
10 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48] -> adds r3, r3, #48
10 occurrences: ldr r2, [r5, #48] -> adds r3, r3, #48 -> bcs 0x5058
125 occurrences: mov r1, r4 -> ldr r2, [sp]
83 occurrences: mvn ip, #-33554432 -> bic ip, ip, #16646144
63 occurrences: sub sp, sp, #4 -> str r0, [sp]
40 occurrences: push {lr} -> sub sp, sp, #4
40 occurrences: add sp, sp, #4 -> pop {pc}
38 occurrences: ldr r1, [sp] -> str r0, [r1, #16]
38 occurrences: str r0, [r1, #16] -> ldr r0, [sp]
34 occurrences: mov r0, #8 -> ldr r1, [sp]
33 occurrences: cmp r8, ip -> bhi 0x5c28
32 occurrences: cmp fp, ip -> bhi 0x2058
32 occurrences: cmp r0, #0 -> bne 0x7e60
29 occurrences: add sp, sp, #4 -> bx r0
25 occurrences: mov r3, r6 -> ldr r2, [r5, #48]
25 occurrences: cmp r3, ip -> bhi 0x5058
23 occurrences: mov r2, r6 -> ldr r1, [r5, #48]
23 occurrences: bic ip, ip, #16646144 -> cmp r3, ip
23 occurrences: cmp r0, #0 -> bne 0x5064
22 occurrences: str r0, [sp] -> ldr r0, [r4]
19 occurrences: cmp r1, ip -> bhi 0x5058
19 occurrences: cmp r7, ip -> bhi 0x5c28
18 occurrences: mov r7, r2 -> ldr r6, [r5, #48]
17 occurrences: mov fp, r1 -> ldr sl, [r5, #48]
17 occurrences: mov r8, r2 -> ldr r7, [r5, #48]
16 occurrences: ldr r8, [sl, fp] -> mov fp, r6
16 occurrences: mov fp, r6 -> ldr sl, [r5, #48]
16 occurrences: str r1, [r7, r8] -> ldr r8, [r5, #48]
16 occurrences: cmp r6, ip -> bhi 0x5c28
16 occurrences: mov r8, r0 -> ldr r6, [r5, #48]
16 occurrences: add ip, r6, r8 -> str r1, [ip]
16 occurrences: str r1, [ip] -> str r7, [ip, #4]
15 occurrences: str r8, [sl, fp] -> mov fp, r1
14 occurrences: ldr r0, [sp] -> ldr r1, [sp, #12]
14 occurrences: cmp r2, ip -> bhi 0x7e54
13 occurrences: ldr r0, [r4] -> ldr r1, [r4, #4]
13 occurrences: bic ip, ip, #16646144 -> cmp r9, ip
12 occurrences: ldr r2, [r5, #48] -> adds r3, r3, #48
12 occurrences: cmp r2, ip -> bhi 0x37b4
12 occurrences: ldr r1, [r4] -> ldr r0, [r5, #48]
12 occurrences: ldr r3, [r4, #28] -> ldr r2, [r5, #48]
12 occurrences: ldr r1, [r6, r7] -> mov r6, r1
12 occurrences: mov r6, r1 -> add r1, r1, #4
11 occurrences: ldr r0, [sp] -> ldr r1, [sp, #4]
11 occurrences: add sp, sp, #8 -> bx r0
11 occurrences: sub sp, sp, #8 -> str r0, [sp]
11 occurrences: ldr r0, [sp] -> ldr r1, [sp, #20]
11 occurrences: cmp r2, ip -> bhi 0xcf8
11 occurrences: str r0, [sp] -> ldr r6, [r4]
11 occurrences: bic ip, ip, #16646144 -> cmp r6, ip
11 occurrences: add r1, r1, #4 -> mov r8, r2
11 occurrences: cmp r1, ip -> bhi 0x7e54
11 occurrences: cmp r3, ip -> bhi 0x8698
10 occurrences: ldr r1, [r4, #4] -> ldr r2, [r4, #8]
10 occurrences: cmp r9, ip -> bhi 0x2058
10 occurrences: ldr r2, [r4] -> ldr r1, [r5, #48]
10 occurrences: adds r3, r3, #48 -> bcs 0x5058
184 occurrences: blx ip
169 occurrences: cmp r0, #0
125 occurrences: mov r1, r4
125 occurrences: ldr r2, [sp]
117 occurrences: add sp, sp, #4
117 occurrences: @ <UNDEFINED> instruction: 0x000487b4
106 occurrences: ldr r1, [r5, #48]
96 occurrences: ldr r2, [r5, #48]
96 occurrences: cmp r3, ip
85 occurrences: cmp r2, ip
83 occurrences: mvn ip, #-33554432
83 occurrences: bic ip, ip, #16646144
78 occurrences: bhi 0x5058
77 occurrences: str r0, [sp]
73 occurrences: mov lr, #0
72 occurrences: cmp r1, ip
68 occurrences: bhi 0x5c28
65 occurrences: sub sp, sp, #4
62 occurrences: ldr r0, [r5, #48]
53 occurrences: ldr r6, [r5, #48]
52 occurrences: bhi 0x7e54
50 occurrences: cmp r6, ip
49 occurrences: cmp r8, ip
47 occurrences: ldr r0, [sp]
47 occurrences: bx r0
47 occurrences: andeq r7, r4, ip, lsr #29
46 occurrences: bhi 0x2058
46 occurrences: bcs 0x5058
44 occurrences: ldr r3, [r5, #48]
43 occurrences: ldr r0, [r1, r2]
42 occurrences: cmp r7, ip
40 occurrences: push {lr}
40 occurrences: pop {pc}
39 occurrences: cmp fp, ip
38 occurrences: ldr r1, [sp]
38 occurrences: str r0, [r1, #16]
36 occurrences: ldr sl, [r5, #48]
36 occurrences: bcs 0x2058
34 occurrences: ldr r7, [r5, #48]
34 occurrences: mov r0, #8
34 occurrences: ldr r8, [r5, #48]
34 occurrences: bhi 0xcf8
34 occurrences: mov r1, r0
33 occurrences: cmp ip, #0
32 occurrences: bne 0x7e60
31 occurrences: ldr ip, [r4, #28]
29 occurrences: mov r2, r6
28 occurrences: ldr r1, [r2, r3]
28 occurrences: bcs 0xcf8
27 occurrences: add sp, sp, #8
26 occurrences: str r0, [r4]
26 occurrences: bhi 0x251c
25 occurrences: mov r3, r6
25 occurrences: cmp r0, ip
24 occurrences: bhi 0x1790
24 occurrences: mov r7, r2
24 occurrences: mov r8, r0
23 occurrences: ldr r0, [r4]
23 occurrences: cmp r9, ip
23 occurrences: ldr ip, [r4, #20]
23 occurrences: bne 0x5064
22 occurrences: mov r1, #0
22 occurrences: mov r2, r0
22 occurrences: str lr, [r4, #4]
22 occurrences: ldr ip, [r4, #64]
21 occurrences: mov ip, #0
21 occurrences: bhi 0x37b4
20 occurrences: mov r6, r0
20 occurrences: mov fp, r1
19 occurrences: mov r8, r2
19 occurrences: ldr ip, [r4, #80]
19 occurrences: ldr ip, [r4, #84]
18 occurrences: mov lr, #64, 22
18 occurrences: cmp r1, #0
18 occurrences: mov r2, r1
18 occurrences: bcs 0x1790
18 occurrences: mov lr, #1
18 occurrences: ldr ip, [r4, #16]
18 occurrences: str r1, [ip]
18 occurrences: mov r6, r1
17 occurrences: mov r0, #0
17 occurrences: add ip, r6, r8
17 occurrences: mov r3, r0
17 occurrences: mov fp, r6
17 occurrences: bcs 0x37b4
17 occurrences: ldr r1, [r6, r7]
17 occurrences: str r1, [r7, r8]
17 occurrences: b 0x5c20
16 occurrences: bhi 0x434
16 occurrences: mov r3, r1
16 occurrences: ldr r8, [sl, fp]
16 occurrences: str r8, [sl, fp]
16 occurrences: str r7, [ip, #4]
15 occurrences: bcs 0x434
15 occurrences: bhi 0x7e0
15 occurrences: mov r6, r7
15 occurrences: mov r7, #0
15 occurrences: str lr, [r4, #92]
14 occurrences: ldr lr, [r5, #60]
14 occurrences: mvn lr, #0
14 occurrences: mov r2, #0
14 occurrences: ldr r1, [sp, #12]
14 occurrences: ldr r1, [r4, #4]
14 occurrences: mov r0, r1
14 occurrences: mov r3, #0
14 occurrences: add r1, r1, #4
14 occurrences: str lr, [r4, #52]
14 occurrences: ldr r3, [r4, #28]
14 occurrences: str lr, [r4, #84]
14 occurrences: ldr r2, [r4, #28]
14 occurrences: ldr ip, [r4, #72]
14 occurrences: mov lr, #48
14 occurrences: bhi 0x8698
13 occurrences: str lr, [r0, r1]
13 occurrences: add r0, r0, r1
13 occurrences: cmp r6, #0
13 occurrences: ldr ip, [r4, #12]
13 occurrences: str lr, [r4, #40]
13 occurrences: str lr, [r4, #164]
12 occurrences: adds r2, r2, #44
12 occurrences: adds r3, r3, #48
12 occurrences: str r6, [r4]
12 occurrences: bcs 0x251c
12 occurrences: ldr r1, [r4]
12 occurrences: ldr ip, [r4, #44]
12 occurrences: bcs 0x7e54
11 occurrences: ldr r1, [sp, #4]
11 occurrences: sub sp, sp, #8
11 occurrences: str r0, [r1, r2]
11 occurrences: ldr r1, [sp, #20]
11 occurrences: ldr r2, [r4, #8]
11 occurrences: mov r6, #0
11 occurrences: ldr r6, [r4]
11 occurrences: str lr, [r4, #44]
11 occurrences: cmp r2, #0
11 occurrences: mov sl, r1
11 occurrences: ldr r2, [r4]
11 occurrences: mov r7, r0
11 occurrences: str lr, [r4, #36]
11 occurrences: mov lr, #32
10 occurrences: ldr r1, [r5, #60]
10 occurrences: mov r8, r7
10 occurrences: mov r3, r7
10 occurrences: ldr r0, [r4, #4]
10 occurrences: str lr, [r4, #16]
10 occurrences: ldr r0, [r2, r3]
10 occurrences: str lr, [r4]
10 occurrences: bhi 0x2ae8
10 occurrences: bhi 0x3188
10 occurrences: ldr ip, [r4, #24]
10 occurrences: ldr ip, [r4]
10 occurrences: ldr r1, [ip]
[END] Finished processing log file: guarded_sum-2026-04-28-21:54:01.bin.log
```

```
program,baseline_time_ns,emu_time_ns,emu_overhead_ns,wasmbchk_count,wasmld_count,wasmstr_count,total_count,baseline_stem,emu_stem
dispatcher,190161190,258149248,67988058,26050,22306,10922,59278,dispatcher-2026-04-28-21:54:10,dispatcher-2026-04-28-21:54:16
factorial,186790145,183588829,-3201316,218,225,92,535,factorial-2026-04-28-21:54:10,factorial-2026-04-28-21:54:17
guarded_sum,186367038,208965907,22598869,5470,9442,2376,17288,guarded_sum-2026-04-28-21:54:11,guarded_sum-2026-04-28-21:54:17
helloworld,181050831,181044158,-6673,74,65,20,159,helloworld-2026-04-28-21:54:11,helloworld-2026-04-28-21:54:17
memwalk,183888101,321744356,137856255,54258,45093,18024,117375,memwalk-2026-04-28-21:54:11,memwalk-2026-04-28-21:54:17
polynomial,186509416,269826328,83316912,25937,30835,12280,69052,polynomial-2026-04-28-21:54:11,polynomial-2026-04-28-21:54:18
promote,188342185,260011062,71668877,33046,18807,8351,60204,promote-2026-04-28-21:54:11,promote-2026-04-28-21:54:18
square,180311009,183823290,3512281,151,172,60,383,square-2026-04-28-21:54:12,square-2026-04-28-21:54:18
```