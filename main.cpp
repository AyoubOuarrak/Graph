#include "Graph_Algorithm.hh"
#include <stdexcept>
#include "Graph.hh"
#include <iostream>
#include <ctime>

using namespace GraphLib;
using namespace GraphAlgorithm;

int main() {
   std::cout << "***************************************" << std::endl
             << "         TESTING GRAPH CLASS           " << std::endl
             << "***************************************" << std::endl;
   // random Graph with(max) 10 nodes
   std::cout << "***** test 1: generate random graph" << std::endl;
   Graph G1 = Graph::generateRandomGraph(10);
   std::cout << G1 << std::endl;
   std::cout << "**** test 1.1 rank of a vertex" << std::endl;
   std::cout << G1.rank("3") << std::endl;

   try {
      // circular Graph with nodes{a,b,c,d}
      std::cout << "***** test 2: interval:<a-d> using Graph::circular " << std::endl;
      Graph G2("a-d", Graph::circular);

      std::cout << "***** test 2.1: setWeight" << std::endl;
      G2.setWeight("c", "d", 6);  //manual setting of weight in the edge
      std::cout << G2 << std::endl;

      // nodes{1,2,3,4} with random edges to connect the nodes
      std::cout << "***** test 3: interval:<1-4> using Graph::random   " << std::endl;
      Graph G3("1-4", Graph::random);
      std::cout << G3 << std::endl;
   }
   catch(std::exception e) {
      std::cerr << e.what(); // invalid interval
   }

   std::cout << "***** test 4: undirected graph" << std::endl;
   // undirected Graph
   Graph G4(Graph::undirected);
   std::cout << "***** test 4.1:  addVertex" << std::endl;
   G4.addVertex("h");
   G4.addVertex("y");
   G4.addVertex("j");

   std::cout << "***** test 4.2: addEdge" << std::endl;
   // if the nodes does not exist, throw: out of range exception
   try {
      G4.addEdge("h", "j");    // default weight is 1
      G4.addEdge("j", "y", 5); // 5: weight of edge <j, y>
      G4.addEdge("y", "h");
   }
   catch(std::exception e) {
      std::cerr << e.what();
   }
   std::cout << G4 << std::endl;


   // copy ctr
   std::cout << "***** test 5: copy ctr" << std::endl;
   Graph G5(G1);
   std::cout << G5 << std::endl;


   std::cout << "**** test 6: vertex adjacent to h (in G5)" << std::endl;
   std::set<std::string> adj = G4.adjacent("h");
   std::set<std::string>::const_iterator adjIt;
   for(adjIt = adj.begin(); adjIt != adj.end(); ++adjIt) {
      std::cout << *adjIt << " ";
   }
   std::cout << std::endl;


   std::cout << "***************************************" << std::endl
             << "       TESTING GRAPH ALGORITHM         " << std::endl
             << "***************************************" << std::endl;

   std::cout << "**** 7: dfs ( g4, h)" << std::endl;
   DepthFirstSearch dfs(G4, "h");

   std::map<std::string, bool>::iterator v;
   for(v = dfs.begin(); v != dfs.end(); ++v) {
      if(dfs.marked(v->first))
         std::cout << v->first <<  " ";
   }
   std::cout << std::endl;
}