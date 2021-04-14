CXX=g++
CXXFLAGS=-g -Wall 

OBJS = coloring.o 

all : coloring 

coloring: $(OBJS)
		  $(CXX) $(CXXFLAGS) $(DEFS) $(OBJS) -o coloring 
coloring.o: 
		  $(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c coloring.cpp

clean: 
		  rm -f *.o coloring