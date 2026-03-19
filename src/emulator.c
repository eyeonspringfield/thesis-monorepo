#define _GNU_SOURCE
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ucontext.h>

#define WASMBCHK_MASK 0xFFF000F0u
#define WASMBCHK_TAG  0xE7F000F0u
#define CPSR_C_BIT    (1u << 29)

// Forward decl of emulated instructions.
void wasmbchk(ucontext_t *uc, uint32_t payload);

// If handler itself triggers SIGILL, exit instead of looping.
static __thread volatile int in_handler = 0;

static inline uint32_t extract_payload16(uint32_t instr)
{
    return ((instr >> 4) & 0xFFF0u) | (instr & 0x000Fu);
}

static inline unsigned long* reg_ptr(ucontext_t* uc, uint32_t reg)
{
    switch (reg) {
    case 0: return &uc->uc_mcontext.arm_r0;
    case 1: return &uc->uc_mcontext.arm_r1;
    case 2: return &uc->uc_mcontext.arm_r2;
    case 3: return &uc->uc_mcontext.arm_r3;
    case 4: return &uc->uc_mcontext.arm_r4;
    case 5: return &uc->uc_mcontext.arm_r5;
    case 6: return &uc->uc_mcontext.arm_r6;
    case 7: return &uc->uc_mcontext.arm_r7;
    case 8: return &uc->uc_mcontext.arm_r8;
    case 9: return &uc->uc_mcontext.arm_r9;
    case 10: return &uc->uc_mcontext.arm_r10;
    case 11: return &uc->uc_mcontext.arm_fp;
    case 12: return &uc->uc_mcontext.arm_ip;
    case 13: return &uc->uc_mcontext.arm_sp;
    case 14: return &uc->uc_mcontext.arm_lr;
    case 15: return &uc->uc_mcontext.arm_pc;
    default: return NULL;
    }
}

static void sigill_handler(const int sig, siginfo_t *info, void *ucontext) {
    ucontext_t *uc = (ucontext_t *)ucontext;
    (void)sig;
    (void)info;

    if (in_handler) {
        _Exit(128 + SIGILL);
    }
    in_handler = 1;

    uintptr_t pc = (uintptr_t)uc->uc_mcontext.arm_pc;
    uint32_t instr = *(const uint32_t *)pc;
    uint32_t payload = extract_payload16(instr);
    uint32_t tag = instr & WASMBCHK_MASK;

    switch (tag) {
        case WASMBCHK_TAG:
            wasmbchk(uc, payload);
            break;
        default:
            signal(SIGILL, SIG_DFL);
            in_handler = 0;
            return;
    }
    uc->uc_mcontext.arm_pc += 4;
    in_handler = 0;
}

// Install the SIGILL handler.

__attribute__((constructor))
static void emulator_init(void)
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = sigill_handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

	if (sigaction(SIGILL, &sa, NULL) == -1) {
        perror("sigaction");
        return;
    }
}

// Emulated instructions.

void wasmbchk(ucontext_t *uc, uint32_t payload) {
    uint32_t rd = (payload >> 12) & 0xFu;
    uint32_t rlimit = (payload >> 8) & 0xFu;
    uint32_t imm8 = payload & 0xFFu;

    unsigned long* rd_ptr = reg_ptr(uc, rd);
    unsigned long* rlimit_ptr = reg_ptr(uc, rlimit);

    if (rd_ptr == NULL || rlimit_ptr == NULL) {
        _Exit(128 + SIGILL);
    }

    uint32_t rd_val = (uint32_t)(*rd_ptr);
    uint32_t limit_val = (uint32_t)(*rlimit_ptr);
    uint64_t sum = (uint64_t)rd_val + (uint64_t)imm8;

    unsigned long cpsr = uc->uc_mcontext.arm_cpsr;
    if ((sum >> 32) != 0 || (uint32_t)sum > limit_val) {
        cpsr |= (unsigned long)CPSR_C_BIT;
    } else {
        cpsr &= ~(unsigned long)CPSR_C_BIT;
        *rd_ptr = (unsigned long)((uint32_t)sum);
    }

    uc->uc_mcontext.arm_cpsr = cpsr;
}