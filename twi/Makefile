MCU=atmega4809
F_CPU=16000000L
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-std=gnu11 -Wall -g -Os -mmcu=${MCU} -DF_CPU=${F_CPU} -I. -c -w -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto

TARGET=twi
SRCS=twi.c

AVR_TOOLS_DIR=/home/wil/snap/arduino/71/.arduino15/packages/arduino/tools
BIN_DIR?=${AVR_TOOLS_DIR}/avr-gcc/7.3.0-atmel3.6.1-arduino5/bin

AVRDUDE_DIR?=${AVR_TOOLS_DIR}/avrdude/6.3.0-arduino17
AVRDUDE?=${AVRDUDE_DIR}/bin/avrdude
CONFDIR?=${AVRDUDE_DIR}/etc/avrdude.conf

PORT=/dev/ttyACM0


all:
	${BIN_DIR}/${CC} -c -g -Os -w -std=gnu11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=${MCU} -DF_CPU=${F_CPU} -DARDUINO=10809 -DARDUINO_AVR_NANO_EVERY ${TARGET}.c -o ${TARGET}.o
	${BIN_DIR}/${CC} -w -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections -Wl,--section-start=.text=0x0 -mmcu=${MCU} -o ${TARGET}.elf ${TARGET}.o
	${BIN_DIR}/${OBJCOPY} -O binary -R .eeprom ${TARGET}.elf ${TARGET}.bin
	${BIN_DIR}/${OBJCOPY} -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 ${TARGET}.elf ${TARGET}.eep
	${BIN_DIR}/${OBJCOPY} -O ihex -R .eeprom ${TARGET}.elf ${TARGET}.hex
	${BIN_DIR}/avr-size -C ${TARGET}.elf
	
flash:
	python3 ./reset_nano.py "/dev/ttyACM0"
	avrdude -C${CONFDIR} -v -p${MCU} -cjtag2updi -Uflash:w:${TARGET}.hex:i -Ufuse2:w:0x01:m -Ufuse5:w:0xC9:m -Ufuse8:w:0x00:m -P${PORT} -b115200 -e -D

clean:
	rm -f *.bin *.hex *.eep *.d *.o *.elf
