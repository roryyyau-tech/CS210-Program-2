# makefile for CS 210 Program 2

# specify compiler
CXX=g++
# compiler flags
# 	-Wall -> shows all warnings
# 	-g -> shows gdb debugging information
# 	-std=c++11 -> use the C++ 2011 ISO standard
CXXFLAGS=-Wall -g -std=c++11
# output flags
CXXOUT=-o p2
# separate compilation
CXXSEP=-c 

# loadbalancer main compilation
p2: p2.cpp webserver.o loadbalancer.o request.h
	$(CXX) $(CXXOUT) $(CXXFLAGS) p2.cpp webserver.o loadbalancer.o

# compile webserver.o
webserver.o: webserver.cpp request.h
	$(CXX) $(CXXSEP) $(CXXFLAGS) webserver.cpp

# compile loadbalancer.o
loadbalancer.o: loadbalancer.cpp loadbalancer.h request.h
	$(CXX) $(CXXSEP) $(CXXFLAGS) loadbalancer.cpp

# clean all *.o files and executable
clean:
	rm -f *.o *.gch p2

# clean all *.o files
cleano:
	rm -f *.o

