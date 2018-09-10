CC=avr-gcc
LD=avr-ld
OBJCOPY=avr-objcopy
OBJDUMP=avr-objdump
AVRSIZE=avr-size

MCU=atmega328p

CFLAGS=-Os -Werror -std=gnu99 -DF_CPU=16000000UL -mmcu=${MCU}
LDFLAGS=-mmcu=$(MCU)
PORT=/dev/ttyACM0

BIN=lab01

OUT=${BIN}.elf ${BIN}.hex ${BIN}.lss

SOURCES = \
		  main.c \
		  serial.c \
		  led.c \
		  timer.c

OBJS = $(SOURCES:.c=.o)

all: $(OUT)
$(OBJS): Makefile

#-include $(OBJS:.o=,P)
%.o:%.c
	$(COMPILE.c) -MD -o $@ $<
	@cp $*.d $*.P; \
		sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
		rm -f $*.d

%.lss: %.elf
	$(OBJDUMP) -h -S -s $< > $@

%.elf: $(OBJS)
	$(CC) -Wl,-Map=$(@:.elf=.map) $(LDFLAGS) -o $@ $^
	$(AVRSIZE) $@

%.hex: %.elf
	$(OBJCOPY) -O ihex -R .fuse -R .lock -R .user_signatures -R .comment $< $@

flash: ${BIN}.hex
	avrdude -F -V -c arduino -p ${MCU} -P ${PORT} -b 115200 -U flash:w:$<

clean:
	rm -f $(OUT) $(OBJS) *.map *.P
