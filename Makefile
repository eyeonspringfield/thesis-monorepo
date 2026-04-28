SHELL := /bin/bash
EMSDK = $(CURDIR)/toolchain/emsdk
SRC_DIR = $(CURDIR)/src/programs
BUILD_DIR = $(CURDIR)/build
WASM_DIR = $(BUILD_DIR)/wasm
WAT_DIR  = $(BUILD_DIR)/wat
EMCC = $(EMSDK)/upstream/emscripten/emcc
WASM2WAT = $(CURDIR)/toolchain/wabt/build/wasm2wat
WALRUS = $(CURDIR)/walrus/out/release/arm/walrus
WALRUS_CUSTOM = $(CURDIR)/walrus/out/release/arm-emu/walrus
LOG_DIR  = $(CURDIR)/logs
METRICS_DIR = $(LOG_DIR)/metrics
QEMU = qemu-arm
OBJDUMP = arm-linux-gnueabi-objdump

CFLAGS = -O0 -s STANDALONE_WASM -s WASM_BIGINT=0 -s ERROR_ON_UNDEFINED_SYMBOLS=0

SRC = $(wildcard $(SRC_DIR)/*.c)
WASM = $(SRC:$(SRC_DIR)/%.c=$(WASM_DIR)/%.wasm)
WAT  = $(SRC:$(SRC_DIR)/%.c=$(WAT_DIR)/%.wat)

all: $(WASM) $(WAT)

$(WASM_DIR)/%.wasm: $(SRC_DIR)/%.c
	@mkdir -p $(WASM_DIR)
	source $(EMSDK)/emsdk_env.sh && \
		$(EMCC) $< $(CFLAGS) -o $@

$(WAT_DIR)/%.wat: $(WASM_DIR)/%.wasm
	@mkdir -p $(WAT_DIR)
	$(WASM2WAT) $< -o $@

run: $(WASM) $(WAT)
	@mkdir -p $(LOG_DIR)
	@for f in $(WASM); do \
		base=$$(basename $$f .wasm); \
		ts=$$(date +"%Y-%m-%d-%H:%M:%S"); \
		log_file=$(LOG_DIR)/$${base}-$${ts}.log; \
		bin_log_file=$(LOG_DIR)/$${base}-$${ts}.bin.log; \
		echo "Running $$f in Walrus under QEMU..."; \
		$(QEMU) -d in_asm,nochain -D $$log_file $(WALRUS) --jit $$f; \
		echo "Log saved to $$log_file"; \
		$(OBJDUMP) -D -b binary -m arm /tmp/jit_dump.bin >> $$bin_log_file; \
		echo "Binary dump saved to $$bin_log_file"; \
	done

clean:
	rm -rf $(BUILD_DIR)

run-emu: $(WASM) $(WAT)
	@mkdir -p $(LOG_DIR)
	@for f in $(WASM); do \
		base=$$(basename $$f .wasm); \
		ts=$$(date +"%Y-%m-%d-%H:%M:%S"); \
		log_file=$(LOG_DIR)/$${base}-$${ts}.log; \
		bin_log_file=$(LOG_DIR)/$${base}-$${ts}.bin.log; \
		echo "Running $$f in Walrus (custom) under QEMU..."; \
		$(QEMU) -d in_asm,nochain -D $$log_file $(WALRUS_CUSTOM) --jit $$f; \
		echo "Log saved to $$log_file"; \
		$(OBJDUMP) -D -b binary -m arm /tmp/jit_dump.bin >> $$bin_log_file; \
		echo "Binary dump saved to $$bin_log_file"; \
	done

clean-logs:
	rm -rf $(LOG_DIR)

run-metrics: $(WASM) $(WAT)
	@mkdir -p $(METRICS_DIR)
	@for f in $(WASM); do \
		base=$$(basename $$f .wasm); \
		ts=$$(date +"%Y-%m-%d-%H:%M:%S"); \
		prefix=$(METRICS_DIR)/$${base}-$${ts}; \
		echo "baseline" > $${prefix}.mode; \
		echo "Running $$f (baseline) with metrics artifacts..."; \
		taskset -c 0 perf stat -e duration_time -o $${prefix}.time \
			$(QEMU) -d in_asm,nochain -D $${prefix}.qemu.log $(WALRUS) --jit $$f \
			>$${prefix}.stdout 2>$${prefix}.stderr; \
		$(OBJDUMP) -D -b binary -m arm /tmp/jit_dump.bin > $${prefix}.bin.log; \
		echo "Artifacts saved with prefix $${prefix}"; \
	done

run-emu-metrics: $(WASM) $(WAT)
	@mkdir -p $(METRICS_DIR)
	@for f in $(WASM); do \
		base=$$(basename $$f .wasm); \
		ts=$$(date +"%Y-%m-%d-%H:%M:%S"); \
		prefix=$(METRICS_DIR)/$${base}-$${ts}; \
		echo "emu" > $${prefix}.mode; \
		echo "Running $$f (custom emu) with metrics artifacts..."; \
		taskset -c 0 perf stat -e duration_time -o $${prefix}.time \
			$(QEMU) -d in_asm,nochain -D $${prefix}.qemu.log $(WALRUS_CUSTOM) --jit $$f \
			>$${prefix}.stdout 2>$${prefix}.stderr; \
		$(OBJDUMP) -D -b binary -m arm /tmp/jit_dump.bin > $${prefix}.bin.log; \
		echo "Artifacts saved with prefix $${prefix}"; \
	done
