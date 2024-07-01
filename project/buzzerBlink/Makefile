# makfile configuration
COMMON_OBJECTS  = main.o buzzer.o song.o
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



load: lightBuzzer.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf

buzzer.c: buzzer.h
main.c: buzzer.h song.h main.h
song.c: song.h buzzer.h
