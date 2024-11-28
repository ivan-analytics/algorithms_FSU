CXXFLAGS=-std=c++11 -Wall -pedantic

# GNU C Library's crypt() method to encrypt the password
LIBS=


proj5.x: proj5.o passserver.o
	$(CXX) $(CXXFLAGS) -I. -o $@ proj5.o passserver.o $(LIBS)


passserver.o: passserver.cpp passserver.h hashtable.h hashtable.hpp
	$(CXX) $(CXXFLAGS) -I. -c -o $@ passserver.cpp

proj5.o: proj5.cpp passserver.h hashtable.h hashtable.hpp
	$(CXX) $(CXXFLAGS) -I. -c -o $@ proj5.cpp


.SUFFIXES: .x


.PHONY : clean

clean:
	rm -f *.o *.x core.*


%.x : %.cpp
	$(CXX) $(CXXFLAGS) -I. -o $@ $< $(LIBS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -I. -c -o $@ $<
