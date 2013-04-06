gest_trajectoire.o: gest_trajectoire.c
	avr-gcc -mmcu=atmega32 -c gest_trajectoire.c

pwm2: pwm_light_2.c
	rm main.hex
	avr-gcc -mmcu=atmega328p -o main.elf pwm_light_2.c

pwm: pwm_light.c
	avr-gcc -mmcu=atmega328p -o main.elf pwm_light.c

PMI: gest_trajectoire.o code_PMI_1.c
	rm main.hex
	avr-gcc -mmcu=atmega32 -o main.elf gest_trajectoire.o code_PMI_1.c gest_trajectoire.h

PMIard: code_PMI_Ard.c
	avr-gcc -mmcu=atmega328p -o main.elf code_PMI_Ard.c

main.hex:
	avr-objcopy -O ihex -R .eeprom main.elf main.hex

prgArd: main.hex
	avrdude -p m328p -c arduino -b 115200 -P /dev/ttyACM0 -U flash:w:main.hex

prgdam: main.hex
	avrdude -p m32 -c ponyser -b 115200 -P /dev/ttyUSB3 -U flash:w:main.hex


prgeirbot: main.hex
	avrdude -p m32 -c usbasp -P /dev/ttyUSB3 -U flash:w:main.hex