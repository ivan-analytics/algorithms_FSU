CXXFLAGS=-std=c++11 -Wall -pedantic

# GNU C Library's crypt() method to encrypt the password
# Detect Operating System
UNAME_S := $(shell uname -s)

# Set LIBS based on OS
ifeq ($(UNAME_S),Linux)
    LIBS = -lcrypt
else
    LIBS =
endif

proj5.x: proj5.cpp passserver.cpp
	@echo "Detected OS: $(UNAME_S)"
	@echo "Libraries: $(LIBS)"
	$(CXX) $(CXXFLAGS) -I. -o proj5.x proj5.cpp passserver.cpp $(LIBS)

clean:
	rm -f proj5.x core.*
