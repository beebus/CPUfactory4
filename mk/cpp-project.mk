CXX		:= g++
TARGET	:= $(PROJNAME)$(EXT)
LIB		:= libavrsim.a
LIBDIR	:= bin

HDRS	:= $(shell python mk/pyfind.py include .h)

USRCS	:= $(wildcard src/*.cpp)
LSRCS	:= $(shell python mk/pyfind.py lib .cpp)
ALLSRCS := $(USRCS) $(LSRCS)

UOBJS   := $(USRCS:.cpp=.o)
LOBJS   := $(LSRCS:.cpp=.o)

DEPS	:= $(USRCS:.cpp=.d) $(LSRCS:.cpp=.d)

ifeq ($(PLATFORM), Windows)
	DOBJS := $(subst /,\,$(UOBJS)) $(subst /,\,$(LOBJS))
else
	DOBJS := $(UOBJS) $(LOBJS)
endif

CXXFLAGS	:= -std=c++11 -Iinclude -MMD

.PHONY: cpp-build
cpp-build: $(TARGET) ## build C++ application

$(TARGET):	$(UOBJS) $(LIBDIR)/$(PLATFORM)/$(LIB)
	@python $(MK)/pyversion.py inc-build
	g++ -o $@ $^ $(LFLAGS)

%.o:	%.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(LIBDIR)/$(PLATFORM)/$(LIB):	$(LOBJS)
	mkdir -p $(LIBDIR)/$(PLATFORM)
	ar rvs $@ $^
		
.PHONY:	run
run:	$(TARGET)	## launch primary build application
	$(PREFIX)$(TARGET)

.PHONY: clean
clean:	## remove all build artifacts
	$(RM) $(TARGET) $(DOBJS) $(DEPS)

.PHONY:	realclean
realclean:	## delete the library file
	$(RM) $(LIBDIR)/$(PLATFORM)/$(LIB)

-include $(DEPS)

