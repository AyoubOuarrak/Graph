#include "Graph_Algorithm.hh"
#include <stdexcept>
#include "Graph.hh"
#include <iostream>
#include <ctime>

using namespace GraphLib;
using namespace GraphAlgorithm;

void testRandomGraphGenerator() {
    // random Graph with(max) 10 nodes
   std::cout << "***** test 1: generate random graph" << std::endl;
   Graph G1 = Graph::generateRandomGraph(10);
   std::cout << G1 << std::endl;
   std::cout << "**** test 1.1 rank of a Node" << std::endl;
   std::cout << G1.rank("3") << std::endl;
}

void testGraphInterval() {
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

void testUndirectedGraph() {
   std::cout << "***** test 4: undirected graph" << std::endl;
   // undirected Graph
   Graph G4(Graph::undirected);
   std::cout << "***** test 4.1:  addNode" << std::endl;
   G4.addNode("h");
   G4.addNode("y");
   G4.addNode("j");

   std::cout << "***** test 4.2: addEdge" << std::endl;
   // if the nodes does not exist, throw: out of range exception

   G4.addEdge("h", "j");    // default weight is 1
   G4.addEdge("j", "y", 5); // 5: weight of edge <j, y>
   G4.addEdge("y", "h");

   std::cout << G4 << std::endl;
}

void testNodeAdjacent() {
   std::cout << "**** test 6: Node adjacent to 2 (in G5)" << std::endl;
   Graph G5 = Graph::generateRandomGraph(6);
   std::cout << G5 << std::endl;

   std::set<std::string> adj = G5.adjacent("2");
   std::set<std::string>::const_iterator adjIt;
   for(adjIt = adj.begin(); adjIt != adj.end(); ++adjIt) {
      std::cout << *adjIt << " ";
   }
   std::cout << std::endl;
}

void testGraphConnection() {
   std::cout << "**** test 7: G6 is connected?" << std::endl;
   Graph G6 = Graph::generateRandomGraph(5);
   std::cout << G6 << std::endl;

   if(G6.isConnected())
      std::cout << "true" << std::endl;
   else
      std::cout << "false" << std::endl;
}

void testRemoveEdge() {
   std::cout << "**** test 8: remove edge" << std::endl;
   Graph G8("a-f", Graph::circular);
   std::cout << G8 << std::endl;
   G8.removeEdge("b", "c");
   G8.removeEdge("d", "e");
   std::cout << G8 << std::endl;
   if(G8.isConnected())
      std::cout << "G8 is connected" << std::endl;
   else
      std::cout << "G8 is not connected" << std::endl;
}

void testRemoveNode() {
   std::cout << "**** test 9: remove Node" << std::endl;
   Graph G9;
   G9.addNode("v1");
   G9.addNode("v2");
   G9.addNode("v3");
   G9.addNode("v4");
   G9.addNode("v5");
   G9.addEdge("v1", "v2");
   G9.addEdge("v1", "v3");
   G9.addEdge("v2", "v4");
   G9.addEdge("v4", "v5");
   G9.addEdge("v5", "v1");

   std::cout << G9 << std::endl;
   std::cout << "remove v5" << std::endl;
   G9.removeNode("v5");
   std::cout << G9 << std::endl;
}

void testDfs() {
   std::cout << "**** test 10: dfs ( G7, 3)" << std::endl;
   Graph G7 = Graph::generateRandomGraph(7);
   std::cout << G7 << std::endl;

   DepthFirstSearch dfs(G7, "3");
   std::map<std::string, bool>::iterator v;
   for(v = dfs.begin(); v != dfs.end(); ++v) {
      if(dfs.marked(v->first))
         std::cout << v->first <<  " ";
   }
   std::cout << std::endl;
}

void testDraw() {
   std::cout << "**** test 11: draw graph using dracula javascript library" << std::endl;
   Graph G11;
   G11.addNode("v1");
   G11.addNode("v2");
   G11.addNode("v3");
   G11.addNode("v4");

   G11.addEdge("v1", "v3", 5);
   G11.addEdge("v2", "v4", 3);
   G11.addEdge("v1", "v2", 6);
   G11.addEdge("v3", "v2", 10);

   std::cout << G11 << std::endl;
   G11.draw();
}

void testDraw2() {
   std::cout << "**** test 12: draw large graph using dracula" << std::endl;
   Graph G12(Graph::undirected);
   G12.addNode("E");
   G12.addNode("T");
   G12.addNode("P");
   G12.addNode("+");
   G12.addNode("*");
   G12.addEdge("E", "E", 2);
   G12.addEdge("E", "+");
   G12.addEdge("E", "T");

   G12.addEdge("E", "T");
   G12.addEdge("T", "P");
   
   G12.addEdge("T", "T", 2);
   G12.addEdge("T", "*");
   G12.addEdge("T", "P");
   G12.draw();
}

void testRemoveNode2() {
   Graph G(Graph::undirected);

   G.addEdge("A", "B");
   G.addEdge("B", "C");
   G.addEdge("D", "A");
   G.addEdge("A", "F");
   G.addEdge("C", "A");
   std::cout << G;
   G.removeNode("A");
   std::cout << G;
}
int main() {
   std::cout << "***************************************" << std::endl
             << "         TESTING GRAPH CLASS           " << std::endl
             << "***************************************" << std::endl;

   testRandomGraphGenerator();
   testGraphInterval();
   testUndirectedGraph();
   testNodeAdjacent();
   testGraphConnection();
   testRemoveEdge();
   testDraw2();

   testRemoveNode2();
   std::cout << "***************************************" << std::endl
             << "       TESTING GRAPH ALGORITHM         " << std::endl
             << "***************************************" << std::endl;

   testDfs();
}