OUTPUT=firmware.elf
CC=avr-gcc
MCU=attiny441 #programmer's MCU
MCU_CLOCK=8000000UL
CFLAGS=-std=c99 -Os -DF_CPU=$(MCU_CLOCK) -mmcu=$(MCU) -D mcu=$(MCU) -D MCU_CLOCK=$(MCU_CLOCK) -include avrHeader.h

all: avrstat doxygen ctags

$(OUTPUT): clean avr.c
	time $(CC) $(CFLAGS) avr.c -o $@

.PHONY: avrstat
avrstat: $(OUTPUT)
	avr-size -C --mcu=$(MCU) $(OUTPUT)

.PHONY: clean
clean:
	rm -rf $(OUTPUT) doc/html/* TAGS readavrfirmware.hex

.PHONY: doxygen
doxygen:
	cd doc/ && echo "Making documentation\n" && \
  doxygen .config > /dev/null && \
  echo "Documentation ready\n"

.PHONY: ctags
ctags: doxygen
	echo "Making ctags\n" && \
	ctags -e -R . && \
	echo "Ctags ready\n"

.PHONY: avrflash
avrflash: avrstat doxygen ctags
	avrdude -c avrisp2 -p $(MCU) -P /dev/ttyUSB0 -U flash:w:$(OUTPUT)

readavrfirmware.hex: clean
	avrdude -c avrisp2 -p $(MCU) -P /dev/ttyUSB0 -U flash:r:$@:i

.PHONY: avrerase
avrerase:
	avrdude -c avrisp2 -p $(MCU) -P /dev/ttyUSB0 -e
