ifeq ($(OS), Windows_NT)
	EXT := .exe
	PREFIX :=
	RM	:= del
	WHICH := where
	PROJPATH := $(CURDIR)
	PROJNAME := $(notdir $(PROJPATH))
	PLATFORM := Windows
else
	EXT :=
	PREFIX := ./
	RM 	:= rm -f
	WHICH := which
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S), Linux)
		PLATFORM := Linux
	endif
	ifeq ($(UNAME_S), Darwin)
		PLATFORM := Mac
	endif
endif

# C++ projects
-include $(MK)/cpp-project.mk
-include $(MK)/cpp-graphics.mk
-include $(MK)/cpp-lint.mk
-include $(MK)/cpp-test.mk

# modular utilities
-include $(MK)/help.mk
-include $(MK)/debug.mk

# avr projects
-include $(MK)/avr-files.mk
-include $(MK)/avr-tools.mk
-include $(MK)/avr-utils.mk
-include $(MK)/avr-build.mk

# docs
-include $(MK)/sphinx.mk
