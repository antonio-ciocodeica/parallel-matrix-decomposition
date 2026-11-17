.PHONY: build run_serial clean

CC = gcc
CFLAGS = -Wall -Wextra -O2
INCLUDE_DIRS = -I./utils
LDLIBS = -lm

UTILS_DIR = ./utils
SERIAL_DIR = ./serial
BIN_DIR = ../bin

INPUT_FILE ?= ../input/matrix.txt
OUTPUT_DIR ?= ../output/serial

build: $(BIN_DIR)/serial

$(BIN_DIR)/serial: $(SERIAL_DIR)/main.o $(SERIAL_DIR)/cholesky.o $(SERIAL_DIR)/crout.o $(UTILS_DIR)/utils.o
	mkdir -p "$(BIN_DIR)"
	$(CC) $^ -o $@ $(LDLIBS)

$(SERIAL_DIR)/main.o: $(SERIAL_DIR)/cholesky.h $(SERIAL_DIR)/crout.h $(UTILS_DIR)/utils.h
$(SERIAL_DIR)/cholesky.o: $(SERIAL_DIR)/cholesky.h $(UTILS_DIR)/utils.h
$(SERIAL_DIR)/crout.o: $(SERIAL_DIR)/crout.h $(UTILS_DIR)/utils.h
$(UTILS_DIR)/utils.o: $(UTILS_DIR)/utils.h

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

run_serial: $(BIN_DIR)/serial
	mkdir -p "$(OUTPUT_DIR)"
	$(BIN_DIR)/serial "$(INPUT_FILE)" "$(OUTPUT_DIR)"

clean:
	rm -f $(BIN_DIR)/serial $(SERIAL_DIR)/*.o $(UTILS_DIR)/*.o