# boot_base
# compile template for S3C2440
#
VERSION=1
PATCHLEVEL=1
NAME=boot_interrupt_template

COMPILE ?= arm-linux-
CC := $(COMPILE)gcc
LD := $(COMPILE)ld
OBJCOPY := $(COMPILE)objcopy
MAKE = make
BUILD_FLAGS = --start-group -lgcc -lgcc_eh -lgcov -lc --end-group \
	      -L/usr/local/arm/4.6.3/lib/gcc/arm-none-linux-gnueabi/4.6.3 \
	      -L/usr/local/arm/4.6.3/arm-none-linux-gnueabi/lib \

VPATH = boot:source

LDS ?= boot/boot.lds

include boot/Makefile
include source/Makefile

boot.bin: $(objs)
	echo $(objs)
	$(LD) -Bstatic -T$(LDS) $(objs) -Map boot.map $(BUILD_FLAGS) \
	-o boot.elf  
	$(OBJCOPY) -O binary -S boot.elf $@
	
%.o:%.c
	$(CC) -Wall -I$(CURDIR)/include  -c -o $@ $<

%.o:%.S
	$(CC) -Wall  -c -o $@ $<


.PHONY:clean
clean:
	rm -f *.elf *.o *.bin *.map
