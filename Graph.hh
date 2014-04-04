/*
 *  Author : Ouarrak Ayoub
 *  Date   : ~/04/2014
*/

#ifndef GRAPH_HH
#define GRAPH_HH 1

#include <utility>
#include <string>
#include <vector>
#include <set>
#include <map>

namespace GraphLib {

class Graph {

public:
   static int random;    // generate a random edge to connect the vertex
   static int circular;  // generate a edge that forms a circular graph
   static bool directed;  // generate directed Graph
   static bool undirected;  // generate undirected Graph
   static Graph  generateRandomGraph(int, bool graphType = directed); // generate random Graph with (max) n vertex

   Graph& operator=(const Graph&) = delete; // operator= is not implemented

   explicit Graph(bool graphType = directed);
   Graph(std::string, int edgeMode, bool graphType = directed);  // add vertex using regex eg. G("A-Z"), G(1-5), G(12-82)
   Graph(const Graph&); //copy ctr
   ~Graph() = default;

   void   generateGraph(int);  // generate edge to connect the Graph, using random/circular method.
   void   addVertex(std::string node);
   void   addEdge(std::string fromNode, std::string toNode, double cost = 1);
   void   setWeight(std::string fromNode, std::string toNode, double cost);
   bool   hasEdge(std::string fromNode, std::string toNode) const;
   double weight(std::string fromNode, std::string toNode) const;  // return weight of the edge

   std::set<std::string> adjacent(std::string) const; // return a vector of nodes adjacent to v

   /*
   bool isTree() const;
   bool isDag() const;
   bool isOriented() const;
   bool isConnected() const;
   bool hasNegativeWeigth();
   */
   inline unsigned vertex() const; // return the number of vertex
   inline unsigned edge() const; // return the number of edge
   void print(std::ostream&) const;

private:
   bool direct;  // direct graph or undirect?
   typedef std::pair<std::string, std::string> link;  // eg. <v. u>

   std::vector<std::string> _vertex;
   std::vector<link>        _edge;  // eg. {<v1, u1>, <v2, u2>, ...}
   std::map<link, double>   _edgeWeight;  //eg. {<v1,u1> = 1, <v2,u2> = 1 ,...}

   inline std::vector<std::string> _Vertex() const;  // return vector vertex
   inline std::vector<link>        _Edge() const;    // return vector edge
   inline std::map<link, double>   _EdgeWeight() const;  //return map edgeWeight
};

// operator << overloaded
std::ostream& operator<<(std::ostream& os, const GraphLib::Graph& g);
#include "Graph_Inlines.hh"

} //namespace Graph
#endif //GRAPH_HH