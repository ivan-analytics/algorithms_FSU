# Variables
CXX = g++
CXXFLAGS = -std=c++11 -Wall -pedantic

all: proj2.x test_list.x

test_list.x: test_list.cpp
	$(CXX) $(CXXFLAGS) test_list.cpp -o test_list.x

proj2.x: mem_manager.cpp MyMemory.cpp MyMemoryBlock.cpp
	$(CXX) $(CXXFLAGS) mem_manager.cpp MyMemory.cpp MyMemoryBlock.cpp -o proj2.x