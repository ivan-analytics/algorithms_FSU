# Compiler and Flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -pedantic

# Detect Operating System
UNAME_S := $(shell uname -s)

# Set LIBS based on OS
ifeq ($(UNAME_S),Linux)
    LIBS = -lcrypt
else
    LIBS =
endif

# Default Target: Build both proj5.x and sproj5.x
all: proj5.x sproj5.x

# Compile proj5.x
proj5.x: proj5.cpp passserver.cpp passserver.h
	@echo "Building proj5.x"
	@echo "Detected OS: $(UNAME_S)"
	@echo "Libraries: $(LIBS)"
	$(CXX) $(CXXFLAGS) -I. -o proj5.x proj5.cpp passserver.cpp $(LIBS)

# Compile sproj5.x
sproj5.x: sproj5.cpp passserver.cpp passserver.h
	@echo "Building sproj5.x"
	@echo "Detected OS: $(UNAME_S)"
	@echo "Libraries: $(LIBS)"
	$(CXX) $(CXXFLAGS) -I. -o sproj5.x sproj5.cpp passserver.cpp $(LIBS)

# Clean Build Files
clean:
	@echo "Cleaning up..."
	rm -f proj5.x sproj5.x core.* 
	@echo "Clean complete."

# Phony Targets
.PHONY: all clean
