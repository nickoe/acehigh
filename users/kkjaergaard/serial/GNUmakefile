#
# $Id$
#

# Projektnavn
PRJNAME=test

# Navn på MCU, f.eks. atmega16
MCU=atmega328p

# Kildekoder, .c for C, .cc, .cpp eller .C for C++, .S (ikke .s) for
# assambler
PRJSRC=main.c serial.c

# Biblioteker
LIBS=-lm

# CPU frequency in hertz
CPUFREQ=20000000

# id to use with programmer default: PROGRAMMER_MCU=$(MCU) In case the
# programer used, e.g avrdude, doesn't accept the same MCU name as
# avr-gcc (for example for ATmega8s, avr-gcc expects 'atmega8' and
# avrdude requires 'm8')
AVRDUDE_MCU=m328p

# programmer id--check the avrdude for complete list of available
# opts.  These should include stk500, avr910, avrisp, bsd, pony and
# more.  Set this to one of the valid "-c PROGRAMMER-ID" values
# described in the avrdude info page.
AVRDUDE_PROGID=dragon_isp

# port--serial or parallel port to which your hardware programmer is
# attached
AVRDUDE_PORT=usb


##### Flags ####

# HEXFORMAT -- format for .hex file output
HEXFORMAT=ihex

# compiler
CFLAGS=$(INC) -g -mmcu=$(MCU) -Os -DF_CPU=$(CPUFREQ) -fpack-struct	\
-fshort-enums -funsigned-bitfields -funsigned-char -Wall		\
-Wstrict-prototypes -Wa,-ahlms=$(firstword $(filter %.lst,		\
$(<:.c=.lst))) -std=c99

# c++ specific flags
CPPFLAGS=-fno-exceptions -Wa,-ahlms=$(firstword $(filter %.lst,	\
$(<:.cpp=.lst)) $(filter %.lst, $(<:.cc=.lst)) $(filter %.lst,	\
$(<:.C=.lst)))

# assembler
ASMFLAGS =$(INC) -mmcu=$(MCU) -x assembler-with-cpp		\
-Wa,-gstabs,-ahlms=$(firstword $(<:.S=.lst) $(<.s=.lst))


# linker
LDFLAGS=-Wl,-Map,$(TRG).map -mmcu=$(MCU)

##### executables ####
CC=avr-gcc
OBJCOPY=avr-objcopy
OBJDUMP=avr-objdump
SIZE=avr-size
AVRDUDE=avrdude
REMOVE=rm -f

##### automatic target names ####
TRG=$(PRJNAME).out
DUMPTRG=$(PRJNAME).s

HEXROMTRG=$(PRJNAME).hex 
HEXTRG=$(HEXROMTRG) $(PRJNAME).ee.hex
GDBINITFILE=gdbinit-$(PRJNAME)

# Define all object files.

# Start by splitting source files by type
#  C++
CPPFILES=$(filter %.cpp, $(PRJSRC))
CCFILES=$(filter %.cc, $(PRJSRC))
BIGCFILES=$(filter %.C, $(PRJSRC))
#  C
CFILES=$(filter %.c, $(PRJSRC))
#  Assembly
ASMFILES=$(filter %.S, $(PRJSRC))


# List all object files we need to create
OBJDEPS=$(CFILES:.c=.o)    \
	$(CPPFILES:.cpp=.o)\
	$(BIGCFILES:.C=.o) \
	$(CCFILES:.cc=.o)  \
	$(ASMFILES:.S=.o)

# Define all lst files.
LST=$(filter %.lst, $(OBJDEPS:.o=.lst))

# All the possible generated assembly 
# files (.s files)
GENASMFILES=$(filter %.s, $(OBJDEPS:.o=.s)) 


.SUFFIXES : .c .cc .cpp .C .o .out .s .S \
	.hex .ee.hex .h .hh .hpp


.PHONY: writeflash clean stats gdbinit stats

# Make targets:
# all, disasm, stats, hex, writeflash/install, clean
all: $(TRG)

disasm: $(DUMPTRG) stats

stats: $(TRG)
	$(OBJDUMP) -h $(TRG)
	$(SIZE) $(TRG) 

hex: $(HEXTRG)


writeflash: hex
	$(AVRDUDE) -c $(AVRDUDE_PROGID) -p $(AVRDUDE_MCU) -P	\
	$(AVRDUDE_PORT) -e -U flash:w:$(HEXROMTRG)

install: writeflash

$(DUMPTRG): $(TRG) 
	$(OBJDUMP) -S  $< > $@


$(TRG): $(OBJDEPS) 
	$(CC) $(LDFLAGS) -o $(TRG) $(OBJDEPS) $(LIBS)


#### Generating assembly ####
# asm from C
%.s: %.c
	$(CC) -S $(CFLAGS) $< -o $@

# asm from (hand coded) asm
%.s: %.S
	$(CC) -S $(ASMFLAGS) $< > $@


# asm from C++
.cpp.s .cc.s .C.s :
	$(CC) -S $(CFLAGS) $(CPPFLAGS) $< -o $@



#### Generating object files ####
# object from C
.c.o: 
	$(CC) $(CFLAGS) -c $< -o $@


# object from C++ (.cc, .cpp, .C files)
.cc.o .cpp.o .C.o :
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# object from asm
.S.o :
	$(CC) $(ASMFLAGS) -c $< -o $@


#### Generating hex files ####
# hex files from elf
#####  Generating a gdb initialisation file    #####
.out.hex:
	$(OBJCOPY) -j .text                    \
		-j .data                       \
		-O $(HEXFORMAT) $< $@

.out.ee.hex:
	$(OBJCOPY) -j .eeprom                  \
		--change-section-lma .eeprom=0 \
		-O $(HEXFORMAT) $< $@


#####  Generating a gdb initialisation file    #####
##### Use by launching simulavr and avr-gdb:   #####
#####   avr-gdb -x gdbinit-myproject           #####
gdbinit: $(GDBINITFILE)

$(GDBINITFILE): $(TRG)
	@echo "file $(TRG)" > $(GDBINITFILE)
	@echo "target remote localhost:1212" \
		                >> $(GDBINITFILE)
	@echo "load"        >> $(GDBINITFILE) 
	@echo "break main"  >> $(GDBINITFILE)
	@echo "continue"    >> $(GDBINITFILE)
	@echo
	@echo "Use 'avr-gdb -x $(GDBINITFILE)'"


#### Cleanup ####
clean:
	$(REMOVE) $(TRG) $(TRG).map $(DUMPTRG)
	$(REMOVE) $(OBJDEPS)
	$(REMOVE) $(LST) $(GDBINITFILE)
	$(REMOVE) $(GENASMFILES)
	$(REMOVE) $(HEXTRG)
