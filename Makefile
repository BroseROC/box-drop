#Symbols
#Required Install of glibc-static and libstdc++-static 

CXX := g++
CXXFLAGS := -std=c++0x -g -lpthread -Wall

DetectorConnectionMgr:
	#mkdir ../bin 
	$(CXX) -o boxdrop manager.cpp $(CXXFLAGS)

clean:
	rm -f boxdrop
