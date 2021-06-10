CXX = g++
CPPFLAGS = -g -Wall -std=c++11 

all: binary_test

valgrind: binary_test
	valgrind --tool=memcheck --track-origins=yes --leak-check=yes ./binary_test

binary_test: binary_test.cpp avlbst.h
	$(CXX) $(CPPFLAGS) $< -o $@

clean: 
	rm -rf binary_test