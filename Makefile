TARGET = telemetry_app
CFLAGS = -Wall -Wextra -g -Iinclude -std=c99
CC = gcc

SRC_DIR = src
BUILD_DIR = build
TEST_DIR = tests

SRCS = $(wildcard $(SRC_DIR)/coordinates_decoder/*.c) \
       $(wildcard $(SRC_DIR)/telemetry_analyzer/*.c) \
       $(SRC_DIR)/main.c
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

SUBDIRS = $(sort $(dir $(SRCS)))
SUBDIRS := $(patsubst $(SRC_DIR)/%, %, $(SUBDIRS))
SUBDIRS_TO_CREATE = $(addprefix  $(BUILD_DIR)/, $(SUBDIRS))

TEST_TARGET = run_tests
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/tests/%.o, $(TEST_SRCS))

all: $(BUILD_DIR) $(TARGET) $(TEST_TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

$(BUILD_DIR): $(SUBDIRS_TO_CREATE)
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%/:
	@mkdir -p $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/tests/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(BUILD_DIR)/coordinates_decoder/coordinates_decoder.o -o $@

test: 
	@./$(TEST_TARGET)

clean:
	@$(RM) -r $(BUILD_DIR) $(TARGET) $(TEST_TARGET)

.PHONY: all clean test
