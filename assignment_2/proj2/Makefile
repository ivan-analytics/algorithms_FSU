# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall -pedanticx
TARGET = proj2.x
SRC = test_list.cpp
# SRC = mem_manager.cpp
# HEADERS = List.h List.hpp

# The default target
all: $(TARGET)

# Compile the program
$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Force rebuild
.PHONY: clean
clean:
	rm -f $(TARGET)