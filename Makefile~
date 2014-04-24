CC = $(CXX)

Graph: Graph.o test.o
	g++ -std=c++11 -Wall -Wextra Graph.o test.o -o Graph

Graph.o: Graph.cpp
	g++ -Wall -Wextra -std=c++11 -c Graph.cpp -o Graph.o

test.o: test.cpp
	g++ -c test.cpp -o test.o

clean: 
	-rm -f *.o Graph
