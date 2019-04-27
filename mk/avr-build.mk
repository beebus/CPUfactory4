# loader flags
UFLAGS	:=  -v -D -p$(MCU) -c$(PGMR)
UFLAGS		+= -P$(PORT)
UFLAGS		+= -b115200

# c compiler flags
AVRCFLAGS	:=  -Iinclude
AVRCFLAGS	+= -c -Os -mmcu=$(MCU)
AVRCFLAGS	+= -DF_CPU=$(FREQ)

# link flags
AVRLFLAGS	:= -mmcu=$(MCU)
AVRLFLAGS	+= -nostartfiles

# build targets
.PHONY avr-build:
avr-build:	$(AVRPROJ).hex $(AVRLST) ## Build AVR project
	echo $(AVROBJS)

# implicit build rules
%.hex:	%.elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

%.elf:	$(AVROBJS)
	$(AVRGCC) $(AVRLFLAGS) -o $@ $(AVROBJS)

%.obj:	%.cpp
	$(AVRGXX) -c $(AVRCFLAGS) -o $@ $<

%.obj:	%.c
	$(AVRGCC) -c $(AVRCFLAGS) -o $@ $<

%.obj:	%.S
	$(AVRGCC) -c $(AVRCFLAGS) -o $@ $<

%.lst:	%.elf
	$(OBJDUMP) -C -d $< > $@
