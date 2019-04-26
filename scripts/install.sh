#!/usr/bin/env bash
mkdir -p deps

# install g3log ======================================
if [ ! -d "deps/g3log" ]; then
	cd deps && \
	git clone https://github.com/KjellKod/g3log.git
fi
#cd deps/g3log-1.3.2 && \
#rm -f build && \
#mkdir -p build && \
#cd ./build && \
#cmake -DCMAKE_BUILD_TYPE=Release -DUSE_DYNAMIC_LOGGING_LEVELS=ON .. && \
#make

#cp -r deps/g3log-1.3.2/src/g3log /usr/local/include
#cp dep/lib* /usr/local/lib

# install glui ==================================
if [ ! -d "deps/glui" ]; then
	cd deps && \
	git clone https://github.com/libglui/glui
fi
#cd deps/glui && \
#make clean && \
#make
#cp deps/glui/lib/libglui.a /usr/local/lib
#cp deps/glui/include/GL/glui.h /usr/local/include
