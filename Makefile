CC = $(CXX)

Graph: Graph.o test_graph.o
	g++ -std=c++11 -g -Wall -Wextra Graph.o test_graph.o -o Graph

Graph.o: Graph.cpp
	g++ -Wall -Wextra -std=c++11 -c -g Graph.cpp -o Graph.o

test.o: test_graph.cpp
	g++ -c -g test_graph.cpp -o test_graph.o

clean: 
	-rm -f *.o Graph
