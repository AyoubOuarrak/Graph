/*
 *  Author : Ouarrak Ayoub
 *  Date   : ~04/2014
*/

#ifndef GRAPH_HH
#define GRAPH_HH 1

#include <utility>
#include <string>
#include <vector>
#include <map>

namespace GraphLib {

class Graph {

public:
   static int random;    // generate a random edge to connect the vertex
   static int circular;  // generate a edge that forms a circular graph
   static bool directed;
   static bool undirected;
   static Graph  generateRandomGraph(int, bool graphType = directed); // generate random Graph with (max) n vertex

   Graph& operator=(const Graph&) = delete;

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

   /*
   bool isTree() const;
   bool isDag() const;
   bool isOriented() const;
   bool isConnected() const;
   bool hasNegativeWeigth();
   */
   unsigned vertex() const;
   unsigned edge() const;
   void print() const;

private:
   bool direct;  // direct graph or undirect?

   typedef std::pair<std::string, std::string> link;

   std::vector<std::string> _vertex;
   std::vector<link>        _edge;
   std::map<link, double>   _edgeWeight;

   std::vector<std::string> _Vertex() const;  // return vector vertex
   std::vector<link>        _Edge() const;    // return vector edge
   std::map<link, double>   _EdgeWeight() const;  //return map edgeWeight
};
} //namespace Graph
#endif // GRAPH_HH