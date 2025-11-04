TARGET = telemetry_app
CFLAGS = -Wall -Wextra -g -Iinclude -std=c99
CC = gcc

SRC_DIR = src
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/coordinates_decoder/*.c) \
       $(wildcard $(SRC_DIR)/telemetry_analyzer/*.c) \
       $(SRC_DIR)/main.c
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

SUBDIRS = $(sort $(dir $(SRCS)))
SUBDIRS := $(patsubst $(SRC_DIR)/%, %, $(SUBDIRS))
SUBDIRS_TO_CREATE = $(addprefix  $(BUILD_DIR)/, $(SUBDIRS))

all: $(BUILD_DIR) $(TARGET)

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

clean:
	@$(RM) -r $(BUILD_DIR) $(TARGET)

.PHONY: all clean
