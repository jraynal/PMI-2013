all: code_PMI_1_Ard.c
	avr-gcc -mmcu=atmega328p -o main.elf code_PMI_1_Ard.c

prg:
	avr-objcopy -O ihex -R .eeprom main.elf main.hex
	avrdude -p m328p -c arduino -b 115200 -P /dev/ttyACM0 flash:w:main.hex