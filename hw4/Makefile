CXX=g++
CXXFLAGS=-g -Wall 

OBJS = floorplan.o 

all : floorplan

floorplan: $(OBJS)
		  $(CXX) $(CXXFLAGS) $(DEFS) $(OBJS)
floorplan.o: 
		  $(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c floorplan.cpp

clean: 
		  rm -f *.o floorplan