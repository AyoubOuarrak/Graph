#ifndef GRAPH_HH
#define GRAPH_HH 1

#include <utility>
#include <string>
#include <vector>
#include <map>

class Graph {

public:
   static int random;    // generate a random edge to connect the vertex
   static int circular;  // generate a edge that form a circular graph
   static Graph  generateRandomGraph(int); // generate random Graph with (max) n vertex

   Graph();
   Graph(std::string, int);  // add vertex using regex eg. G("A-Z"), G(1-5), G(12-82)
   Graph(const Graph&);

   void   generateGraph(int);  // generate edge to connect the Graph, using random/circular method.
   void   addVertex(std::string node);
   void   addEdge(std::string fromNode, std::string toNode);
   void   addEdge(std::string fromNode, std::string toNode, double cost);
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
   typedef std::pair<std::string, std::string> link;

   std::vector<std::string> _vertex;
   std::vector<link>        _edge;
   std::map<link, double>   _edgeWeight;
};
#endif // GRAPH_HH