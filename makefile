CC = gcc
CFLAGS = -Iinc
SRC_FILES = src/main.c src/list.c src/tree.c src/encode.c src/decode.c
BUILD_DIR = build

TARGET = $(BUILD_DIR)/Szip.exe

$(TARGET): $(SRC_FILES)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: clean
