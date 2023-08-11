MCU=atmega4809
F_CPU=16000000L
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-std=gnu++11 -Wall -g -Os -mmcu=${MCU} -DF_CPU=${F_CPU} -I.
PORT=/dev/ttyACM0
TARGET=twi
SRCS=twi.c

all:
	${CC} ${CFLAGS} -o ${TARGET}.bin ${SRCS}
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.bin ${TARGET}.hex
	
flash:
	python3 ./reset_nano.py "/dev/ttyACM0"
	sudo avrdude -p${MCU} -cjtag2updi -Uflash:w:${TARGET}.hex:i -P${PORT} -C/home/wil/snap/arduino/71/.arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/etc/avrdude.conf -b115200 -e -D

clean:
	rm -f *.bin *.hex
	
	
