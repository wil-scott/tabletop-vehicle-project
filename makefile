#AVR-GCC Tool Paths
AVR_TOOLS_DIR=/home/wil/snap/arduino/71/.arduino15/packages/arduino/tools
BIN_DIR=$(AVR_TOOLS_DIR)/avr-gcc/7.3.0-atmel3.6.1-arduino5/bin
AVRDUDE_DIR=$(AVR_TOOLS_DIR)/avrdude/6.3.0-arduino17

#AVR Toolchain
CONFDIR?=$(AVRDUDE_DIR)/etc/avrdude.conf
AVRDUDE=$(AVRDUDE_DIR)/bin/avrdude
CC=$(BIN_DIR)/avr-gcc
OBJCOPY=$(BIN_DIR)/avr-objcopy

# compiler-related vars
TARGET=main
MCU=atmega328p
F_CPU=16000000UL
BAUDR=115200

PROGRAMMER = arduino
PORT=/dev/ttyACM0

# Build directory
BUILD_DIR = build

# Source directories
SRC_DIR = Core/src
INC_DIR = Core/inc
LIB_DIR = Core/lib

# Build target
all: $(BUILD_DIR)/main.hex

# Compiler flags
CFLAGS = -Os -DF_CPU=${F_CPU} -mmcu=${MCU} -I$(INC_DIR) -Wall

# Linker flags
LDFLAGS = -L$(LIB_DIR)

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.c)
LIB_SRCS := $(wildcard $(LIB_DIR)/*.c)

# Object files
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
LIB_OBJS := $(LIB_SRCS:$(LIB_DIR)/%.c=$(BUILD_DIR)/%.o)

$(BUILD_DIR)/main.hex: $(BUILD_DIR)/main.elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

$(BUILD_DIR)/main.elf: $(OBJS) $(LIB_OBJS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(LIB_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Flash the program
flash: $(BUILD_DIR)/main.hex
	sudo $(AVRDUDE) -C$(CONFDIR) -F -V -c arduino -p atmega328p -P /dev/ttyACM0 -b 115200 -U flash:w:$<:i

# Clean up
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all flash clean






