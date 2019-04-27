ifeq ($(PLATFORM), Mac)
	CXXFLAGS += -I/usr/local/include
    CXXFLAGS += -Wno-deprecated-declarations
	LFLAGS += -framework OpenGL -framework GLUT
	LFLAGS += -Lbin/Mac -lGLUT -lglui
endif
ifeq ($(PLATFORM), Windows)
	CXXFLAGS += -I\tools\freeglut\include -Iinclude
	LFLAGS += -L\tools\freeglut\lib\x64 -L\tools\glui\lib
	LFLAGS += -lfreeglut -lglui -lglu32 -lopengl32 
	LFLAGS += -Wl,--subsystem,windows
endif
ifeq ($(PLATFORM), Linux)
	CXXFLAGS += -I/usr/include -Iinclude
	LFLAGS += -Lbin/Linux -lGL -lGLU -lglut -lglui
endif
