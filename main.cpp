#include "Graph.hh"
#include <iostream>

int main() {

   Graph G1 = Graph::generateRandomGraph(5);
   //Graph G1("a-c", Graph::random);

   //G1.setWeight("a", "b", 3);
/*
   G1.addEdge("A", "B");
   G1.addEdge("B", "A");
   G1.addEdge("B", "C");
   G1.addEdge("C", "B");
   G1.addEdge("C", "A");
   G1.addEdge("A", "C");
*/

   G1.print();

   //std::cout << std::endl << G.weight("e", "B");
}