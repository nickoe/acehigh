# $Id$
#
# Lad være med at ændre denne fil, med mindre du ved præcis hvad du
# gør


#####     Konfigurerbare variabler

# navn på output
BIN=bin

# mappe til output
BINPATH=build

# liste med kildefiler
SRCS=main.c

# biblioteker til linkeren, angivet som flags
LIBS=-lm

# enheden vi programmerer til
MCU=atmega16

# programmeringsenheden
PROG=avr910

# enheden vi programmerer til som angivet i AVRDUDE
PROGMCU=m16

# frekvensen på MCU'en
CPUFREQ=16000000

# enheden MCU'en sikker på
PROGDEV=/dev/ttyUSB0

INC=-I/usr/avr/include
LIB=-L/usr/avr/lib


#####     Flags til kompiler, linker m.m.

# HEXFORMAT -- format for .hex file output
HEXFORMAT=ihex

# compiler
CFLAGS=-I. $(INC) -g -DF_CPU=$(CPUFREQ) -mmcu=$(MCU) -Os		\
-fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall	\
-Wstrict-prototypes

# c++ specific flags
CPPFLAGS=-fno-exceptions

# assembler
ASMFLAGS =-I. $(INC) -mmcu=$(MCU) -x assembler-with-cpp


# linker
LDFLAGS=-Wl,-Map,$(BINPATH)/$(TRG).map -mmcu=$(MCU) $(LIB) $(LIBS)


#####     Programmer
CC=avr-gcc
OBJCOPY=avr-objcopy
OBJDUMP=avr-objdump
SIZE=avr-size
AVRDUDE=avrdude
REMOVE=rm -f


#####     Navne på automatiske mål

TRG=$(BIN).out
DUMPTRG=$(BIN).s

HEXROMTRG=$(BIN).hex 
HEXTRG=$(HEXROMTRG) $(BIN).ee.hex
GDBINITFILE=gdbinit-$(BIN)

# definer alle objektfiler

# del filerne op efter type
#  C++
CPPFILES=$(filter %.cpp, $(SRCS))
CCFILES=$(filter %.cc, $(SRCS))
BIGCFILES=$(filter %.C, $(SRCS))
#  C
CFILES=$(filter %.c, $(SRCS))
#  Assembly
ASMFILES=$(filter %.S, $(SRCS))


# alle objektfiler vi behøver at lave
OBJDEPS=$(CFILES:.c=.o) $(CPPFILES:.cpp=.o) $(BIGCFILES:.C=.o)	\
$(CCFILES:.cc=.o) $(ASMFILES:.S=.o)

# alle genererede asm-filer (.s-filer, lille s)
GENASMFILES=$(filter %.s, $(OBJDEPS:.o=.s)) 


.SUFFIXES: .c .cc .cpp .C .o .out .s .S .hex .ee.hex .h .hh .hpp


.PHONY: writeflash clean stats gdbinit stats

# Make targets:
# all, disasm, stats, hex, writeflash/install, clean
all: $(TRG)

disasm: $(DUMPTRG) stats

stats: $(TRG)
	$(OBJDUMP) -h $(BINPATH)/$(TRG)
	$(SIZE) $(BINPATH)/$(TRG)

hex: $(HEXTRG)

writeflash: hex
	$(AVRDUDE) -c $(PROG)   \
	 -p $(PROGTARGET) -P $(PROGDEV) -e        \
	 -U flash:w:$(BINPATH)/$(HEXROMTRG)

install: writeflash

$(DUMPTRG): $(TRG) 
	$(OBJDUMP) -S  $(BINPATH)/$< > $(BINPATH)/$@

$(TRG): $(OBJDEPS) 
	$(CC) $(LDFLAGS) $(LIBS) -o $(BINPATH)/$(TRG) $(addprefix $(BINPATH)/,$(notdir $(OBJDEPS)))

#####     Generer assambler-filer til disasm-målet
%.s: %.c
	$(CC) -S $(CFLAGS) $< -o $(BINPATH)/$(notdir $@)
%.s: %.S
	$(CC) -S $(ASMFLAGS) $< > $(BINPATH)/$(notdir $@)
# asm from C++
.cpp.s .cc.s .C.s :
	$(CC) -S $(CFLAGS) $(CPPFLAGS) $< -o $(BINPATH)/$(notdir $@)

#####     Generer alle objektfiler
# fra c
.c.o: 
	$(CC) $(CFLAGS) -c $< -o $(BINPATH)/$(notdir $@)
# fra C++ (.cc, .cpp, .C)
.cc.o .cpp.o .C.o :
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $(BINPATH)/$(notdir $@)
# fra asm
.S.o :
	$(CC) $(ASMFLAGS) -c $< -o $(BINPATH)/$(notdir $@)


#### Generating hex files ####
# hex files from elf
#####  Generating a gdb initialisation file    #####
.out.hex:
	$(OBJCOPY) -j .text                    \
		-j .data                       \
		-O $(HEXFORMAT) $(BINPATH)/$< $(BINPATH)/$@

.out.ee.hex:
	$(OBJCOPY) -j .eeprom                  \
		--change-section-lma .eeprom=0 \
		-O $(HEXFORMAT) $(BINPATH)/$< $(BINPATH)/$@


#####  Generating a gdb initialisation file    #####
##### Use by launching simulavr and avr-gdb:   #####
#####   avr-gdb -x gdbinit-myproject           #####
gdbinit: $(GDBINITFILE)

$(GDBINITFILE): $(TRG)
	@echo "file $(BINPATH)/$(TRG)" > $(GDBINITFILE)
	
	@echo "target remote localhost:1212" \
		                >> $(GDBINITFILE)
	
	@echo "load"        >> $(GDBINITFILE) 
	@echo "break main"  >> $(GDBINITFILE)
	@echo "continue"    >> $(GDBINITFILE)
	@echo
	@echo "Use 'avr-gdb -x $(GDBINITFILE)'"


#### Cleanup ####
clean:
	$(REMOVE) $(addprefix $(BINPATH)/,$(TRG) $(TRG).map $(DUMPTRG))
	$(REMOVE) $(addprefix $(BINPATH)/,$(OBJDEPS))
	$(REMOVE) $(addprefix $(BINPATH)/,$(GENASMFILES))
	$(REMOVE) $(addprefix $(BINPATH)/,$(HEXTRG))
	$(REMOVE) $(GDBINITFILE)
