CXXFLAGS=-std=c++11 -Wall -pedantic

# GNU C Library's crypt() method to encrypt the password
LIBS=

proj5.x: proj5.cpp passserver.cpp
	$(CXX) $(CXXFLAGS) -I. -o proj5.x proj5.cpp passserver.cpp $(LIBS)

clean:
	rm -f proj5.x core.*
