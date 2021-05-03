CXX=g++
CXXFLAGS=-g -Wall 

OBJS = counting.o Hashtable.o

all : counting

counting: counting.o Hashtable.o
		  $(CXX) $(CXXFLAGS) -o counting counting.o

counting.o: counting.cpp
		  $(CXX) $(CXXFLAGS) -c counting.cpp

Hashtable.o: Hashtable.h Hashtable.cpp
		  $(CXX) $(CXXFLAGS) -c Hashtable.cpp


clean: 
		  rm -f *.o counting Hashtable