/*
 *  Author : Ouarrak Ayoub
 *  Date   : ~/04/2014
*/

#ifndef GRAPH_LIB_HH
#define GRAPH_LIB_HH 1

#include <algorithm>
#include <utility>
#include <string>
#include <vector>
#include <list>
#include <map>
 
namespace GraphLib {

class Graph {

public:
   static int random;    // generate a random edge to connect the Node
   static int circular;  // generate a edge that forms a circular graph
   static bool directed;  // generate directed Graph
   static bool undirected;  // generate undirected Graph
   static Graph  generateRandomGraph(int, bool graphType = directed); // generate random Graph with (max) n Node

   Graph& operator=(const Graph&) = delete; // operator= is not implemented

   explicit Graph(bool graphType = directed);
   Graph(std::string, int edgeMode, bool graphType = directed);  // add Node using regex eg. G("A-Z"), G(1-5), G(12-82)
   Graph(const Graph&); //copy ctr
   ~Graph() = default;

   Graph  transpose();     
   void   coloring(); //Graph Coloring (Greedy Algorithm)
   void   draw() const;  //draw the graph using the javascript library: "dracula"
   void   print(std::ostream&) const;
   void   addNode(std::string node);
   void   removeNode(std::string node);
   void   addEdge(std::string fromNode, std::string toNode, double cost = 1);
   void   removeEdge(std::string from, std::string toNode);
   void   setWeight(std::string fromNode, std::string toNode, double cost);
   bool   hasNegativeWeigth() const;
   bool   isCyclic() const;

   unsigned minRank() const;
   unsigned maxRank() const;

   std::list<std::string> adjacent(std::string) const; // return a list of nodes adjacent to v

   inline bool hasEdge(std::string fromNode, std::string toNode) const;
   inline bool isOriented() const;
   inline bool isRegular() const; // minRank = maxRank = k -> regularity of graph is k
   inline bool exist(std::string) const; // check if exist node

   inline unsigned nodes() const; // return the number of Node
   inline unsigned edges() const; // return the number of edge
   inline unsigned rank(std::string v) const; // n° of adjacent Node of v
   inline double   weight(std::string fromNode, std::string toNode) const;  // return weight of the edge


private:
   bool direct;  // direct graph or undirect
   
   typedef std::pair<std::string, std::string> link;  // eg. <v. u>
   typedef std::map<std::string, bool> mapStringBool;

   std::vector<std::string> _node;
   std::vector<link>        _edge;  // eg. {<v1, u1>, <v2, u2>, ...}
   std::map<link, double>   _edgeWeight;  //eg. {<v1,u1> = 1, <v2,u2> = 1 ,...}

   inline std::vector<std::string> _Node() const;  // return vector Node
   inline std::vector<link>        _Edge() const;    // return vector edge
   inline std::map<link, double>   _EdgeWeight() const;  //return map edgeWeight

   // function to draw the graph using javascript and html
   void _generateHtmlPage() const;
   void _generateJavascriptPage() const;
   void _generateEdge(int);  // generate edge to connect the Graph, using random/circular method.

   // This function is a variation of DFSUytil() in http://www.geeksforgeeks.org/archives/18
   bool _isCyclicUtilDirected(std::string v, mapStringBool visited, mapStringBool recStack) const; 
   bool _isCyclicUtilUnDirected(std::string v, mapStringBool visited, std::string parent) const;
   bool _isCyclicDirected() const;
   bool _isCyclicUnDirected() const;
};

// operator << overloaded
std::ostream& operator<<(std::ostream& os, const GraphLib::Graph& g);
// include inline functions
#include "Graph_Inlines.hh"

} //namespace GraphLib
#endif //GRAPH_LIB_HH