# -*- Makefile -*-

# target: dependencies
# 	action

all: test_bst

# main: main.o
# 	g++ main.o -o main

# main.o: main.cpp hashtable.cpp element.cpp utility.cpp
# 	g++ -c main.cpp

test_bst: test_bst.o
	g++ test_bst.o -o test_bst

test_bst.o: test_bst.cpp bst.cpp
	g++ -c test_bst.cpp

# bst: bst.o 
# 	g++ bst.o -o bst

# bst.o: bst.cpp
# 	g++ -c bst.cpp 

clean:
	rm -f *.o test_bst main

