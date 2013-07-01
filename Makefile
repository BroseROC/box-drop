
CXX := g++
CXXFLAGS := -std=c++0x -g -lpthread -lrt -Wall
FILES := manager.cpp file_watch.cpp consts.cpp

all: clean boxdrop

boxdrop:
	#mkdir ../bin 
	$(CXX) -o boxdrop $(CXXFLAGS) $(FILES)

clean:
	rm -f boxdrop
