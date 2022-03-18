# -*- Makefile -*-

# target: dependencies
# 	action

all: test_bst main

main: main.o
	g++ main.o -o main

main.o: main.cpp bst.cpp 
	g++ -c main.cpp

test_bst: test_bst.o
	g++ test_bst.o -o test_bst

test_bst.o: test_bst.cpp bst.cpp
	g++ -c test_bst.cpp

clean:
	rm -f *.o test_bst main

