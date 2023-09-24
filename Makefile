MCU=atmega4809
F_CPU=16000000L
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-std=gnu11 -Wall -g -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU) -I. -c -w -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto

AVR_TOOLS_DIR=/home/wil/snap/arduino/71/.arduino15/packages/arduino/tools

BIN_DIR?=$(AVR_TOOLS_DIR)/avr-gcc/7.3.0-atmel3.6.1-arduino5/bin
AVRDUDE_DIR?=$(AVR_TOOLS_DIR)/avrdude/6.3.0-arduino17
AVRDUDE?=$(AVRDUDE_DIR)/bin/avrdude
CONFDIR?=$(AVRDUDE_DIR)/etc/avrdude.conf
AVR_AR?=$(BIN_DIR)/avr-gcc-ar

# project-specific paths
LIBS_DIR=/home/wil/Workbench/autonomous-vehicle-project/Core/Libs
SRC_DIR=/home/wil/Workbench/autonomous-vehicle-project/Core/Src
INC_DIR=/home/wil/Workbench/autonomous-vehicle-project/Core/Inc

PORT=/dev/ttyACM0
TARGET=main
LIB1=twi

do: 
	make twi.o 
	make SSD1306.o 
	make HCSR04.o
	make $(TARGET).o
	make library
	make core
	make flash

twi.o: $(LIBS_DIR)/twi.c
	$(BIN_DIR)/$(CC) -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=$(MCU) -DF_CPU=$(F_CPU) -I$(LIBS_DIR) $< -o $@
	
SSD1306.o: $(SRC_DIR)/SSD1306.c
	$(BIN_DIR)/$(CC) -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=$(MCU) -DF_CPU=$(F_CPU) -I$(INC_DIR) $< -o $@

HCSR04.o: $(SRC_DIR)/HCSR04.c
	$(BIN_DIR)/$(CC) -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=$(MCU) -DF_CPU=$(F_CPU) -I$(INC_DIR) $< -o $@

$(TARGET).o: $(SRC_DIR)/$(TARGET).c
	$(BIN_DIR)/$(CC) -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=$(MCU) -DF_CPU=$(F_CPU) -I$(LIBS_DIR) $< -o $@

library:
	rm -f libmain.a
	$(AVR_AR) rcs libmain.a twi.o
	$(AVR_AR) rcs libmain.a SSD1306.o
	$(AVR_AR) rcs libmain.a HCSR04.o

core:
	$(BIN_DIR)/$(CC) -w -Os -g -flto -Wl,--gc-sections -Wl,--section-start=.text=0x0 -mmcu=$(MCU) -Wl,-Map,avr.map -o $(TARGET).elf $(TARGET).o -L/home/wil/Workbench/autonomous-vehicle-project -lmain
	$(BIN_DIR)/$(OBJCOPY) -O binary -R .eeprom $(TARGET).elf $(TARGET).bin # this line doesn't seem to change outcome
	$(BIN_DIR)/$(OBJCOPY) -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 $(TARGET).elf $(TARGET).eep
	$(BIN_DIR)/$(OBJCOPY) -O ihex -R .eeprom $(TARGET).elf $(TARGET).hex
	$(BIN_DIR)/avr-size -C $(TARGET).elf

flash:
	python3 ./reset_nano.py "/dev/ttyACM0"
	avrdude -C$(CONFDIR) -v -p$(MCU) -cjtag2updi -Uflash:w:$(TARGET).hex:i -Ufuse2:w:0x01:m -Ufuse5:w:0xC9:m -Ufuse8:w:0x00:m -P$(PORT) -b115200 -e -D

clean:
	rm -f *.bin *.hex *.eep *.d *.o *.elf *.map
