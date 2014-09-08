
MKPATH   := mkdir -p 

SRCDIR   := src
INCDIR   := inc
BUILDDIR := build
TARGETDIR   := bin/$(TARGET)

MAPFILE := $(TARGETDIR)/$(TARGET).map
DESIRED_EXEFILE := $(TARGETDIR)/$(TARGET).hex

CXXFLAGS := -g

# Create build environment depending on functionality build
ifeq ($(TARGET),sim)
	ENV := x86
	DEFINES := -DTARGET=SIM
	SOURCES_DIR += $(SRCDIR)/sim/
	INCLUDES += -I "$(INCDIR)/sim/"
endif

ifeq ($(TARGET),server)
	ENV := pic24
	DEFINES := -DTARGET=SERVER
	SOURCES_DIR += $(SRCDIR)/server/
	INCLUDES += -I "$(INCDIR)/server/"
	SOURCES_DIR += $(SRCDIR)/utilities/
endif

ifeq ($(TARGET),client)
	ENV := pic16
	DEFINES := -DTARGET=CLIENT
	SOURCES_DIR += $(SRCDIR)/node/
	INCLUDES += -I"$(INCDIR)/node/"
endif

ifeq ($(TARGET),sniffer)
	ENV := pic24
	DEFINES := -DTARGET=SNIFFER
	SOURCES_DIR += $(SRCDIR)/dbg/
	INCLUDES += -I "$(INCDIR)/dbg/"
endif

# Add C directories accordingly
SOURCES_DIR += $(SRCDIR)/bsp/$(ENV)/
SOURCES_DIR += $(SRCDIR)/bsp/common/

SOURCES_DIR += $(SRCDIR)/devices/
SOURCES_DIR += $(SRCDIR)/rfstack/

INCLUDES += -I"$(INCDIR)/"
INCLUDES += -I"$(INCDIR)/bsp/$(ENV)/"

# Set up compiler environment
ifeq ($(ENV),x86)
	CC := gcc
	OBJEXT := o
else
	ifeq ($(ENV),pic16)

		# Compiler Configuration
		CC := "/opt/microchip/xc8/v1.30/bin/xc8"
		OBJEXT := p1

		CFLAGS = --pass1 --chip=16LF1508 -Q -G  --double=24 --float=24 --opt=default,+asm,-asmfile,-speed,+space,-debug --addrqual=require --mode=pro -P -N255 --warn=0 --ext=IAR --asmlist --summary=default,-psect,-class,+mem,+hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,+download,-stackcall,+clib --output=-mcof,+elf:multilocs
		CFLAGS += $(INCLUDES)

		# Linker configuration
		LFLAGS = --chip=16LF1508 -G -m$(MAPFILE)  --double=24 --float=24 --opt=default,+asm,-asmfile,-speed,+space,-debug --addrqual=require --mode=pro -P -N255 --warn=0 --ext=IAR --asmlist --summary=default,-psect,-class,+mem,+hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,+download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto
		LFLAGS += $(INCLUDES)

		# Elf > hex not needed
		EXEFILE := $(TARGETDIR)/$(TARGET).hex
		BIN2HEX := /dev/null
	else
		ifeq ($(ENV),pic24)
			# Compiler Configuration
			CC := /opt/microchip/xc16/v1.21/bin/xc16-gcc
			CS := /opt/microchip/xc16/v1.21/bin/xc16-as
			OBJEXT := d

			CFLAGS = -c -mcpu=24FJ64GB004  -MMD -g -omf=elf -Os -msmart-io=1 -Wall -msfr-warn=off
			CFLAGS += $(INCLUDES)

			# Linker configuration
			LFLAGS = -mcpu=24FJ64GB004 -omf=elf -Wl,,--defsym=__MPLAB_BUILD=1,,--script=p24FJ64GB004.gld,--heap=0,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map=$(MAPFILE),--report-mem 
			
			# Elf > hex step
			EXEFILE := $(TARGETDIR)/$(TARGET).elf
			BIN2HEX := /opt/microchip/xc16/v1.21/bin/xc16-bin2hex
		else
		endif
	endif
endif

#https://github.com/WellDone/MoMo-Firmware/blob/dev/momo_modules/mainboard/project.yml
#https://github.com/WellDone/MoMo-Firmware/blob/dev/momo_modules/mainboard/rakefile.rb

# Scan Source directories
SRCEXT_CPP := cpp
SRCEXT_C   := c
SRCEXT_ASM := s

SOURCES_CPP := $(shell find $(SOURCES_DIR) -type f -name *.$(SRCEXT_CPP))
SOURCES_C   := $(shell find $(SOURCES_DIR) -type f -name *.$(SRCEXT_C))
SOURCES_ASM := $(shell find $(SOURCES_DIR) -type f -name *.$(SRCEXT_ASM))

OBJECTS_CPP := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES_CPP:.$(SRCEXT_CPP)=.$(OBJEXT)))
OBJECTS_C   := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES_C:.$(SRCEXT_C)=.$(OBJEXT)))
OBJECTS_ASM := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES_ASM:.$(SRCEXT_ASM)=.$(OBJEXT)))

# Make rules

all: $(EXEFILE) $(DESIRED_EXEFILE)

# Some compilers need an extra bin2hex step. If the file is not created during normal compilation,
# it will be now.
$(DESIRED_EXEFILE):
	@echo "$(BIN2HEX) $(EXEFILE) -a  -omf=elf"
	$(BIN2HEX) $(EXEFILE) -a  -omf=elf 

$(EXEFILE): $(OBJECTS_C) $(OBJECTS_ASM)
	@echo "Working directory: $(shell pwd)"
	@echo "Build target $(TARGET), environment $(ENV), compiler $(CC)"	 
	@echo "Sources path: $(SOURCES_DIR)"
	@echo "Includes path: $(INCLUDES)"

	$(MKPATH) $(TARGETDIR) $(BUILDDIR)
	@echo " Linking..."
	@echo " $(CC) $(LFLAGS) $^ -o $(TARGETDIR) $(LIB)"; $(CC) $(LFLAGS) $^ -o$(EXEFILE) $(LIB)
	
	$(RM) -r $(BUILDDIR)

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGETDIR)

build/%.$(OBJEXT) : src/%.$(SRCEXT_C)
	@echo "\r\n\r\n**** Compiling file $^";
	@echo " $(MKPATH) $(shell dirname $@)"; $(MKPATH) $(shell dirname $@)
	@echo " $(CC) $(CFLAGS) $(DEFINES) -o$@ $^ "; $(CC) $(CFLAGS) $(DEFINES) -o$@ $^ 

build/%.$(OBJEXT) : src/%.$(SRCEXT_ASM)
	@echo "\r\n\r\n**** Assembling file $^";
	@echo " $(MKPATH) $(shell dirname $@)"; $(MKPATH) $(shell dirname $@)
	@echo " $(CS) $(CFLAGS) $(DEFINES) -o$@ $^ "; $(CS) $(SFLAGS) -o$@ $^ 
