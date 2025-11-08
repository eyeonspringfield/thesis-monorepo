SHELL := /bin/bash
EMSDK = $(CURDIR)/toolchain/emsdk
SRC_DIR = $(CURDIR)/src
BUILD_DIR = $(CURDIR)/build
EMCC = $(EMSDK)/upstream/emscripten/emcc
WALRUS = $(CURDIR)/walrus/out/release/arm/walrus
LOG_DIR  = $(CURDIR)/logs
QEMU = qemu-arm

CFLAGS = -O2 -s STANDALONE_WASM -s WASM_BIGINT=0 -s ERROR_ON_UNDEFINED_SYMBOLS=0

SRC = $(wildcard $(SRC_DIR)/*.c)
WASM = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.wasm)

all: $(WASM)

$(BUILD_DIR)/%.wasm: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	source $(EMSDK)/emsdk_env.sh && $(EMCC) $< $(CFLAGS) -o $@

run: $(WASM)
	@mkdir -p $(LOG_DIR)
	@for f in $(WASM); do \
		base=$$(basename $$f .wasm); \
		ts=$$(date +"%Y-%m-%d-%H:%M:%S"); \
		log_file=$(LOG_DIR)/$${base}-$${ts}.log; \
		echo "Running $$f in Walrus under QEMU..."; \
		$(QEMU) -d in_asm -D $$log_file $(WALRUS) --jit $$f; \
		echo "Log saved to $$log_file"; \
	done

clean:
	rm -rf $(BUILD_DIR)

clean-logs:
	rm -rf $(LOG_DIR)