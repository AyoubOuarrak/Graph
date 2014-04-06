CC = $(CXX)

Graph: Graph.o main.o
	g++ -std=c++11 -Wall -Wextra Graph.o main.o -o Graph

Graph.o: Graph.cpp
	g++ -Wall -Wextra -std=c++11 -c Graph.cpp -o Graph.o

main.o: main.cpp
	g++ -c main.cpp -o main.o

clean: 
	-rm -f *.o Graph
