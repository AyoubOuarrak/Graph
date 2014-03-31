#include <stdexcept>
#include "Graph.hh"
#include <iostream>


int main() {

   Graph G1 = Graph::generateRandomGraph(10); // 10:=  max vertex
   Graph G2("a-g", Graph::circular);
   Graph G3("1-5", Graph::random);
   Graph G4;
   Graph G5(G1);

   G2.setWeight("c", "d", 6);

   G4.addVertex("h");
   G4.addVertex("y");
   G4.addVertex("j");

   try {
      G4.addEdge("h", "j");
      G4.addEdge("j", "y", 5);
      G4.addEdge("y", "h");
   }
   catch(std::exception e) {
      std::cout << e.what();
   }
   std::cout << "-----------------------------------" << std::endl
             << "            Random Graph           " << std::endl
             << "-----------------------------------" << std::endl;
   G1.print();
   std::cout << "---------------------------------------" << std::endl
             << " interval:<a-g>  using Graph::circular " << std::endl
             << "---------------------------------------" << std::endl;
   G2.print();
   std::cout << "---------------------------------------" << std::endl
             << " interval:<1-5>  using Graph::random   " << std::endl
             << "---------------------------------------" << std::endl;
   G3.print();
   std::cout << "-----------------------------------" << std::endl
             << "        default constructor        " << std::endl
             << "-----------------------------------" << std::endl;
   G4.print();
   std::cout << "-----------------------------------" << std::endl
             << "           copy constructor        " << std::endl
             << "-----------------------------------" << std::endl;
   G5.print();
}