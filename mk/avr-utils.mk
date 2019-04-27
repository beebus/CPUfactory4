# utility targets
.PHONY:	avr-load
avr-load:	$(TARGET).hex ## Load hex file using avrdude
	$(DUDE) $(DUDECONF) $(UFLAGS) -Uflash:w:$(AVRTARGET).hex:i

.PHONY:	avr-clean
avr-clean: ## remove build artifacts
	$(RM) *.hex *.lst  *.elf $(AVROBJS)
