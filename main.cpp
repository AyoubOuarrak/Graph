#include "Graph.hh"
#include <iostream>

int main() {

   Graph G1 = Graph::generateRandomGraph(5); // 5:=  max vertex
   Graph G2("a-g", Graph::circular);
   Graph G3("1-5", Graph::random);
   Graph G4;

   G2.setWeight("c", "d", 6);

   G4.addVertex("h");
   G4.addVertex("y");
   G4.addVertex("j");

   G4.addEdge("h", "j");
   G4.addEdge("j", "y", 5);
   G4.addEdge("y", "h");


   G1.print();
   G2.print();
   G3.print();
   G4.print();
}