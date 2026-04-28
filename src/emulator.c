#define _GNU_SOURCE
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ucontext.h>

#define WASMBCHK_MASK 0xFFF000F0u
#define WASMBCHK_TAG  0xE7F000F0u
#define WASMLD_TAG    0xE7E000F0u
#define WASMSTR_TAG   0xE7D000F0u
#define CPSR_C_BIT    (1u << 29)

// Forward decl of emulated instructions.
void wasmbchk(ucontext_t *uc, uint32_t payload);
void wasmld(ucontext_t *uc, uint32_t payload);
void wasmstr(ucontext_t *uc, uint32_t payload);

// If handler itself triggers SIGILL, exit instead of looping.
static __thread volatile int in_handler = 0;

typedef struct {
    uint64_t sigill_count;
    uint64_t wasmbchk_count;
    uint64_t wasmld_count;
    uint64_t wasmstr_count;
} emu_metrics_t;

static emu_metrics_t g_metrics;

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

static inline uint16_t load_u16_unaligned(const void* ptr)
{
    uint16_t value;
    memcpy(&value, ptr, sizeof(value));
    return value;
}

static inline uint32_t load_u32_unaligned(const void* ptr)
{
    uint32_t value;
    memcpy(&value, ptr, sizeof(value));
    return value;
}

static inline void store_u16_unaligned(void* ptr, uint16_t value)
{
    memcpy(ptr, &value, sizeof(value));
}

static inline void store_u32_unaligned(void* ptr, uint32_t value)
{
    memcpy(ptr, &value, sizeof(value));
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

    g_metrics.sigill_count++;

    switch (tag) {
        case WASMBCHK_TAG:
            g_metrics.wasmbchk_count++;
            wasmbchk(uc, payload);
            break;
        case WASMLD_TAG:
            g_metrics.wasmld_count++;
            wasmld(uc, payload);
            break;
        case WASMSTR_TAG:
            g_metrics.wasmstr_count++;
            wasmstr(uc, payload);
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

__attribute__((destructor))
static void emulator_fini(void)
{
    fprintf(stderr, "EMU_METRIC version=1\n");
    fprintf(stderr, "EMU_METRIC sigill_count=%llu\n", (unsigned long long)g_metrics.sigill_count);
    fprintf(stderr, "EMU_METRIC wasmbchk_count=%llu\n", (unsigned long long)g_metrics.wasmbchk_count);
    fprintf(stderr, "EMU_METRIC wasmld_count=%llu\n", (unsigned long long)g_metrics.wasmld_count);
    fprintf(stderr, "EMU_METRIC wasmstr_count=%llu\n", (unsigned long long)g_metrics.wasmstr_count);
    fprintf(stderr, "EMU_METRIC total_count=%llu\n", (unsigned long long)g_metrics.wasmbchk_count + g_metrics.wasmld_count + g_metrics.wasmstr_count);
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

void wasmld(ucontext_t *uc, uint32_t payload)
{
    uint32_t rd = (payload >> 12) & 0xFu;
    uint32_t rbase = (payload >> 8) & 0xFu;
    uint32_t roffset = (payload >> 4) & 0xFu;
    uint32_t mode = payload & 0xFu;

    unsigned long* rd_ptr = reg_ptr(uc, rd);
    unsigned long* rbase_ptr = reg_ptr(uc, rbase);
    unsigned long* roffset_ptr = reg_ptr(uc, roffset);

    if (rd_ptr == NULL || rbase_ptr == NULL || roffset_ptr == NULL) {
        _Exit(128 + SIGILL);
    }

    uintptr_t addr = (uintptr_t)(*rbase_ptr) + (uintptr_t)((uint32_t)(*roffset_ptr));

    switch (mode) {
    case 0:
        *rd_ptr = (unsigned long)(*(const uint8_t*)addr);
        break;
    case 1:
        *rd_ptr = (unsigned long)(uint32_t)(int32_t)(*(const int8_t*)addr);
        break;
    case 2:
        *rd_ptr = (unsigned long)(load_u16_unaligned((const void*)addr));
        break;
    case 3:
        *rd_ptr = (unsigned long)(uint32_t)(int32_t)(int16_t)load_u16_unaligned((const void*)addr);
        break;
    case 4:
        *rd_ptr = (unsigned long)load_u32_unaligned((const void*)addr);
        break;
    default:
        _Exit(128 + SIGILL);
    }
}

void wasmstr(ucontext_t *uc, uint32_t payload)
{
    uint32_t rs = (payload >> 12) & 0xFu;
    uint32_t rbase = (payload >> 8) & 0xFu;
    uint32_t roffset = (payload >> 4) & 0xFu;
    uint32_t mode = payload & 0xFu;

    unsigned long* rs_ptr = reg_ptr(uc, rs);
    unsigned long* rbase_ptr = reg_ptr(uc, rbase);
    unsigned long* roffset_ptr = reg_ptr(uc, roffset);

    if (rs_ptr == NULL || rbase_ptr == NULL || roffset_ptr == NULL) {
        _Exit(128 + SIGILL);
    }

    uintptr_t addr = (uintptr_t)(*rbase_ptr) + (uintptr_t)((uint32_t)(*roffset_ptr));
    uint32_t value = (uint32_t)(*rs_ptr);

    switch (mode) {
    case 0:
        *(uint8_t*)addr = (uint8_t)value;
        break;
    case 2:
        store_u16_unaligned((void*)addr, (uint16_t)value);
        break;
    case 4:
        store_u32_unaligned((void*)addr, value);
        break;
    default:
        _Exit(128 + SIGILL);
    }
}
