main.elf: pwm_light_2.c
	avr-gcc -mmcu=atmega328p -o main.elf pwm_light_2.c

main.hex: main.elf
	avr-objcopy -O ihex -R .eeprom main.elf main.hex

prg: main.hex
	avrdude -p m328p -c arduino -b 115200 -P /dev/ttyACM0 -U flash:w:main.hex

pmi: code_PMI_1.c
	avr-gcc -mmcu=atmega32 -o main.elf code_PMI_1.c