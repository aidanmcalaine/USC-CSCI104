CXX=g++
CXXFLAGS=-g -Wall 

OBJS = bayes.o 

all : bayes

bayes: $(OBJS)
		  $(CXX) $(CXXFLAGS) $(DEFS) $(OBJS) -o bayes
bayes.o: 
		  $(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c bayes.cpp

clean: 
		  rm -f *.o bayes