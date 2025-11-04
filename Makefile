CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
LDFLAGS = 
TARGET = telemetry_app

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Все исходные файлы (.c)
SRCS = $(wildcard $(SRC_DIR)/coordinates_decoder/*.c) \
       $(wildcard $(SRC_DIR)/telemetry_analyzer/*.c) \
       $(SRC_DIR)/main.c

# Соответствующие объектные файлы (.o)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Каталоги, которые нужно создать внутри BUILD_DIR (например, build/coordinates_decoder/)
SUBDIRS = $(sort $(dir $(SRCS)))
SUBDIRS := $(patsubst $(SRC_DIR)/%, %, $(SUBDIRS))
SUBDIRS_TO_CREATE = $(addprefix $(BUILD_DIR)/, $(SUBDIRS))

# --- Основные цели ---

all: $(BUILD_DIR) $(TARGET)

$(TARGET): $(OBJS)
	@echo "🔗 Линковка $@"
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Цель для создания каталога сборки и всех необходимых подкаталогов
$(BUILD_DIR): $(SUBDIRS_TO_CREATE)
	@echo "📁 Создание каталога сборки: $(BUILD_DIR)"
	@mkdir -p $(BUILD_DIR)

# Шаблонное правило для создания подкаталогов внутри BUILD_DIR (например, build/coordinates_decoder/)
$(BUILD_DIR)/%/:
	@echo "📁 Создание подкаталога: $@"
	@mkdir -p $@

# Общее правило для компиляции:
# Создает объектный файл в BUILD_DIR из исходного файла в SRC_DIR
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "🔨 Компиляция $<"
	$(CC) $(CFLAGS) -c $< -o $@

# --- Вспомогательные цели ---

clean:
	@echo "🧹 Очистка..."
	$(RM) -r $(BUILD_DIR) $(TARGET)

.PHONY: all clean
