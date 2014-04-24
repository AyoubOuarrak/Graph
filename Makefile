CC = $(CXX)

Graph: Graph.o test.o
	g++ -std=c++11 -g -Wall -Wextra Graph.o test.o -o Graph

Graph.o: Graph.cpp
	g++ -Wall -Wextra -std=c++11 -c -g Graph.cpp -o Graph.o

test.o: test.cpp
	g++ -c -g test.cpp -o test.o

clean: 
	-rm -f *.o Graph
