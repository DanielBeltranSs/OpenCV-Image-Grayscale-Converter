CXX = g++
CXXFLAGS = -Wall -std=c++11 -fopenmp `pkg-config --cflags opencv4`
LIBS = `pkg-config --libs opencv4`
DESTDIR = /usr/local/bin
EXECUTABLE = programa3

# Por defecto construye el ejecutable
all: $(EXECUTABLE)

# Compila el programa
$(EXECUTABLE): programa3.cpp
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) programa3.cpp $(LIBS)

# Instala el programa en el sistema
install:
	cp $(EXECUTABLE) $(DESTDIR)

# Limpia los archivos compilados
clean:
	rm -f $(EXECUTABLE)

.PHONY: all install clean
