
CC      = arm-linux-gcc
LD      = arm-linux-ld
AR      = arm-linux-ar
OBJCOPY = arm-linux-objcopy
OBJDUMP = arm-linux-objdump

INCLUDEDIR 	:= $(shell pwd)/include
CFLAGS 		:= -Wall -O2  
CPPFLAGS   	:= -nostdinc -I$(INCLUDEDIR)
LDFAGS      :=  -lgcc -L/usr/local/arm/4.3.2/lib/gcc/arm-none-linux-gnueabi/4.3.2/
export 	CC LD OBJCOPY OBJDUMP INCLUDEDIR CFLAGS CPPFLAGS AR

objs := head.o init.o nand.o interrupt.o i2c.o udelay.o gpio_spi.o ds18b20.o crc_8.o spi_flash.o oled.o at24cxx.o serial.o main.o lib/libc.a

i2c.bin: $(objs)
	${LD} ${LDFAGS} -Ti2c.lds -o i2c_elf $^ 
	${OBJCOPY} -O binary -S i2c_elf $@
	${OBJDUMP} -D -m arm i2c_elf > i2c.dis

.PHONY : lib/libc.a
lib/libc.a:
	cd lib; make; cd ..
	
%.o:%.c
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

%.o:%.S
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	make  clean -C lib
	rm -f i2c.bin i2c_elf i2c.dis *.o
	
