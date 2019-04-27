# source files
AVRCSRCS	:= $(shell python $(MK)/pyfind.py avr/$(AVRPROJ) .c)
AVRCXXSRCS	:= $(shell python $(MK)/pyfind.py avr/$(AVRPROJ) .cpp)
AVRSSRCS	:= $(shell python $(MK)/pyfind.py avr/$(AVRPROJ) .S)

# required object files
AVRCOBJS	:= $(AVRCSRCS:.c=.obj)
AVRCXXOBJS	:= $(AVRCXXSRCS:.cpp=.obj)
AVRSOBJS	:= $(AVRSSRCS:.S=.obj)
AVROBJS		:= $(AVRCOBJS) $(AVRCXXOBJS) $(AVRSOBJS)
AVRLST		:= $(AVRPROJ).lst
