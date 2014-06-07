/*
   @file    test_graph.cpp
   @author  Ayoub Ouarrak, ouarrakayoub@gmail.com
   @version 1.0
*/
#include "Graph.hh"
#include <iostream>
#include <string>
#include <ctime>
#include <list>

using namespace GraphLib;

void testRandomGraphGenerator() {
    /** random Graph with(max) 10 nodes */
   std::cout << "***** test 1: generate random graph" << std::endl;
   Graph G1 = Graph::generateRandomGraph(10);
   std::cout << G1 << std::endl;
   std::cout << "**** test 1.1 rank of a Node" << std::endl;
   std::cout << G1.rank("3") << std::endl;
}

void testGraphInterval() {
   /** circular Graph with nodes{a,b,c,d} */
   std::cout << "***** test 2: interval:<a-d> using Graph::circular " << std::endl;
   Graph G2("a-d", Graph::circular);

   std::cout << "***** test 2.1: setWeight" << std::endl;
   /** manual setting of weight in the edge */
   G2.setWeight("c", "d", 6);  
   std::cout << G2 << std::endl;

   /** nodes{1,2,3,4} with random edges to connect the nodes */
   std::cout << "***** test 3: interval:<1-4> using Graph::random   " << std::endl;
   Graph G3("1-4", Graph::random);
   std::cout << G3 << std::endl;

}

void testUndirectedGraph() {
   std::cout << "***** test 4: undirected graph" << std::endl;
   /** undirected Graph */
   Graph G4(Graph::undirected);
   std::cout << "***** test 4.1:  addNode" << std::endl;
   G4.addNode("h");
   G4.addNode("y");
   G4.addNode("j");

   std::cout << "***** test 4.2: addEdge" << std::endl;

   G4.addEdge("h", "j");    // default weight is 1
   G4.addEdge("j", "y", 5); // 5: weight of edge <j, y>
   G4.addEdge("y", "h");

   std::cout << G4 << std::endl;
}

void testNodeAdjacent() {
   std::cout << "**** test 6: Node adjacent to 2 (in G5)" << std::endl;
   Graph G5 = Graph::generateRandomGraph(6);
   std::cout << G5 << std::endl;

   std::list<std::string> adj = G5.adjacent("2");
   std::list<std::string>::const_iterator adjIt;
   for(adjIt = adj.begin(); adjIt != adj.end(); ++adjIt) {
      std::cout << *adjIt << " ";
   }
   std::cout << std::endl;
}

void testRemoveEdge() {
   std::cout << "**** test 8: remove edge" << std::endl;
   Graph G8("a-f", Graph::circular);
   std::cout << G8 << std::endl;
   G8.removeEdge("b", "c");
   G8.removeEdge("d", "e");
   std::cout << G8 << std::endl;
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

void testRemoveNode() {
   std::cout << "**** test 12: remove A" << std::endl;
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

void testIsCyclic() {
   std::cout << "**** test 13: cyclic Graph" << std::endl;
   Graph G("1-4", Graph::random);
   std::cout << G << std::endl;
   if(G.isCyclic())
      std::cout << "Graph contains cycle" << std::endl;
   else
      std::cout << "Graph doesn't contain cycle" << std::endl;
}

void testTranspose() {
   std::cout << "**** test 14: graph transpose" << std::endl;
   Graph g(Graph::directed);
   g.addEdge("1", "0");
   g.addEdge("0", "2");
   g.addEdge("2", "1");
   g.addEdge("0", "3");
   g.addEdge("3", "4");
   std::cout << g << std::endl;
   std::cout << g.transpose() << std::endl;
}

void testColoring() {
   std::cout << "**** test 15: coloring graph" << std::endl;
   Graph g2(Graph::undirected);
   g2.addEdge("0", "1");
   g2.addEdge("0", "2");
   g2.addEdge("1", "2");
   g2.addEdge("1", "4");
   g2.addEdge("2", "4");
   g2.addEdge("4", "3");
   std::cout << "Coloring of Graph 1 \n";
   g2.coloring(); 
}

void testEulerian() {
   std::cout << "**** test 16: eulerian cycle/path" << std::endl;
   Graph g1;
   g1.addNode("0");
   g1.addNode("1");
   g1.addNode("2");
   g1.addNode("3");
   g1.addNode("4");

   g1.addEdge("1", "0");
   g1.addEdge("0", "2");
   g1.addEdge("2", "1");
   g1.addEdge("0", "3");
   g1.addEdge("3", "1");
   std::cout << g1 << std::endl;

   int res = g1.isEulerian();
   if (res == 0)
      std::cout << "Graph is not Eulerian \n";
   else if (res == 1)
      std::cout << "Graph has a Euler path \n";
   else
      std::cout << "Graph has a Euler cycle \n";
 
   Graph g2;
   g2.addNode("0");
   g2.addNode("1");
   g2.addNode("2");
   g2.addNode("3");
   g2.addNode("4");

   g2.addEdge("1", "0");
   g2.addEdge("0", "2");
   g2.addEdge("2", "1");
   g2.addEdge("0", "3");
   g2.addEdge("3", "4");
   g2.addEdge("4", "0");
   std::cout << g2 << std::endl;

   res = g2.isEulerian();
   if (res == 0)
      std::cout << "Graph is not Eulerian \n";
   else if (res == 1)
      std::cout << "Graph has a Euler path \n";
   else
      std::cout << "Graph has a Euler cycle \n";
 
   Graph g3;
   g3.addNode("0");
   g3.addNode("1");
   g3.addNode("2");
   g3.addNode("3");
   g3.addNode("4");

   g3.addEdge("1", "0");
   g3.addEdge("0", "2");
   g3.addEdge("2", "1");
   g3.addEdge("0", "3");
   g3.addEdge("3", "4");
   g3.addEdge("1", "3");
   std::cout << g3 << std::endl;

   res = g3.isEulerian();
   if (res == 0)
      std::cout << "Graph is not Eulerian \n";
   else if (res == 1)
      std::cout << "Graph has a Euler path \n";
   else
      std::cout << "Graph has a Euler cycle \n";
 
   // Let us create a graph with 3 vertices
   // connected in the form of cycle
   Graph g4;
   g4.addNode("0");
   g4.addNode("1");
   g4.addNode("2");

   g4.addEdge("0", "1");
   g4.addEdge("1", "2");
   g4.addEdge("2", "0");
   std::cout << g4 << std::endl;

   res = g4.isEulerian();
   if (res == 0)
      std::cout << "Graph is not Eulerian \n";
   else if (res == 1)
      std::cout << "Graph has a Euler path \n";
   else
      std::cout << "Graph has a Euler cycle \n";
}

void testBFS() {
   std::cout << "**** test 17: BFS" << std::endl;
   Graph g;
   g.addEdge("0", "1");
   g.addEdge("0", "2");
   g.addEdge("1", "2");
   g.addEdge("2", "0");
   g.addEdge("2", "3");
   g.addEdge("3", "3");
   std::cout << std::endl;
   std::cout << "Following is Breadth First Traversal (starting from vertex 2) \n";
   std::cout << g << std::endl;
   std::cout << std::endl;
   g.BFS("2");
   std::cout << std::endl;
}

void testDFS() {
   std::cout << "**** test 18: DFS" << std::endl;
   Graph g;
   g.addEdge("0", "1");
   g.addEdge("0", "2");
   g.addEdge("1", "2");
   g.addEdge("2", "0");
   g.addEdge("2", "3");
   g.addEdge("3", "3");
   std::cout << std::endl;
   std::cout << "Following is Depth First Traversal (starting from vertex 2) \n";
   std::cout << g << std::endl;
   std::cout << std::endl;
   g.DFS("2");
   std::cout << std::endl;
}

void testFloydWarshell() {
   std::cout << "**** test 19: Floyd Warshall algorithm" << std::endl;
   Graph g;
   g.addNode("0");
   g.addNode("1");
   g.addNode("2");
   g.addNode("3");

   g.addEdge("0", "3", 9);
   g.addEdge("0", "1", 5);
   g.addEdge("1", "2", 3);
   g.addEdge("2", "3", 1);

   double** wMatrix = new double*[g.nodes()];
   for(unsigned i = 0; i < g.nodes(); ++i)
      wMatrix[i] = new double[g.nodes()];

   std::cout << std::endl;
   std::cout << g << std::endl;
   g.floydWarshell(g.transpose().weightMatrix());

}
int main() {
   testRandomGraphGenerator();
   testGraphInterval();
   testUndirectedGraph();
   testNodeAdjacent();
   testRemoveEdge();
   testRemoveNode();
   testIsCyclic();
   testTranspose();
   testColoring();
   testEulerian();
   testBFS();
   testDFS();
   testFloydWarshell();
}