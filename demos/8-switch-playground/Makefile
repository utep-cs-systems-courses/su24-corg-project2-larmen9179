# makfile configuration
COMMON_OBJECTS  = main.o buzzer.o
COMMON_OBJECTSB = 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: lightBuzzer.elf

#additional rules for files
lightBuzzer.elf: ${COMMON_OBJECTS} ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

buzzer.elf: ${COMMON_OBJECTSB} buzzer.o main.o ../lib/libTimer.a



load: lightBuzzer.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf

buzzer.c: buzzer.h
main.c: buzzer.h
