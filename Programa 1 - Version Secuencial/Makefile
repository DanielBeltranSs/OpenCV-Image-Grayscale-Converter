# Makefile

CXX = g++
CXXFLAGS = -Wall -std=c++11 `pkg-config --cflags opencv4`
LIBS = `pkg-config --libs opencv4`
DESTDIR = /usr/local/bin
EXECUTABLE = programa1

all: $(EXECUTABLE)

$(EXECUTABLE): programa1.cpp
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) programa1.cpp $(LIBS)

install:
	cp $(EXECUTABLE) $(DESTDIR)

clean:
	rm -f $(EXECUTABLE)

.PHONY: all install clean

