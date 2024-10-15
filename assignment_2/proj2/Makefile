# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = proj2.x
SRC = test_list.cpp
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