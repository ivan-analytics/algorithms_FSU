# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall -pedantic

all: temp.x test_list.x

test_list.x: test_list.cpp
	$(CXX) $(CXXFLAGS) test_list.cpp -o test_list.x

temp.x: mem_manager.cpp
	$(CXX) $(CXXFLAGS) mem_manager.cpp -o temp.x

# proj2.x: 


