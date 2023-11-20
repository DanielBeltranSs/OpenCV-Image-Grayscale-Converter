CXX = g++
CXXFLAGS = -Wall -std=c++11 -pthread `pkg-config --cflags opencv4`
LIBS = `pkg-config --libs opencv4`

programa2: programa2.cpp
	$(CXX) $(CXXFLAGS) -o programa2 programa2.cpp $(LIBS)

