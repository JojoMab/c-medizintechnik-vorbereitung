CC ?= clang
CFLAGS ?= -std=c17 -Wall -Wextra -Wpedantic -g
BUILD_DIR := build

PROGRAMS := \
	$(BUILD_DIR)/day01_medtech_monitor \
	$(BUILD_DIR)/day02_vital_values \
	$(BUILD_DIR)/day03_vital_check

.PHONY: all run-day01 run-day02 run-day03 clean

all: $(PROGRAMS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/day01_medtech_monitor: day01_medtech_monitor.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/day02_vital_values: day02_vital_values.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/day03_vital_check: day03_vital_check.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

run-day01: $(BUILD_DIR)/day01_medtech_monitor
	./$(BUILD_DIR)/day01_medtech_monitor

run-day02: $(BUILD_DIR)/day02_vital_values
	./$(BUILD_DIR)/day02_vital_values

run-day03: $(BUILD_DIR)/day03_vital_check
	./$(BUILD_DIR)/day03_vital_check

clean:
	rm -rf $(BUILD_DIR)
