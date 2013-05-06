CC = avr-gcc
CFLAGS = -W -Wall -Wextra -mmcu=atmega32
LDFLAGS = -lm
SRC = couche_hardware.c gest_trajectoire.c
OBJ = $(SRC:.c=.o)
EXEC= main.elf

all: $(EXEC) 

$(EXEC): code_PMI_1.c $(OBJ)
	@echo "==================================================="
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o : %.c
	@echo "==================================================="
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< $(LDFLAGS)

main.hex: $(EXEC)
	@echo "==================================================="
	@echo "Make $<"
	@avr-objcopy -O ihex -R .eeprom main.elf main.hex

prgdam: main.hex
	avrdude -p m32 -c ponyser -b 115200 -P usb -U flash:w:main.hex

prgeirbot: main.hex
	avrdude -p m32 -c usbasp -P usb -U flash:w:main.hex

clean:
	@rm -rf *.o
	@rm -rf *~
	@rm -rf *.gch
	@rm -rf $(EXEC)
	@rm -rf main.hex