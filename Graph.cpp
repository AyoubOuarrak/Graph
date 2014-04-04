#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <iterator>
#include <cstdlib>
#include <ctime>
#include "Graph.hh"
#include "Utility.hh"

using namespace GraphLib;

typedef std::pair<std::string, std::string> link;
int Graph::random = 0;
int Graph::circular = 1;
bool Graph::directed = true;
bool Graph::undirected = false;

Graph::Graph(bool graphType) {
   direct = graphType;
}

Graph::Graph(const Graph& G) {
   _vertex = G._Vertex();
   _edge = G._Edge();
   _edgeWeight = G._EdgeWeight();
}

Graph::Graph(std::string regex, int edgeType, bool graphType) {
   direct = graphType;
   if(utility::checkIfInterval(regex)) {
      if(regex.length() == 3) {  //1-9,  a-z,  A-Z ..
         std::vector<char> tmp = utility::regexChar(regex);
         std::vector<char>::const_iterator it;
         for(it = tmp.begin(); it != tmp.end(); ++it)
            _vertex.push_back(utility::to_string(*it));
      }
      else if(regex.length() > 3) { //10-17,  12-102 ...
         std::vector<int> tmp = utility::regexInt(regex);
         std::vector<int>::const_iterator it;
         for(it = tmp.begin(); it != tmp.end(); ++it)
            _vertex.push_back(utility::to_string(*it));
      }
   }
   else throw std::invalid_argument("invalid interval");

   generateGraph(edgeType);
}

void Graph::generateGraph(int edgeType) {
   switch(edgeType) {
      case 0: { // random
         srand(time(NULL));
         for(unsigned i = 0; i < _vertex.size(); ++i) {
            int randVertex1 = rand() % _vertex.size();
            int randVertex2 = rand() % _vertex.size();
            if(randVertex1 != randVertex2)
               try {
                  addEdge(_vertex.at(randVertex1), _vertex.at(randVertex2));
               }
               catch(std::exception e) {
                  std::cout << e.what();
               }
         }
      }
      case 1: { // circular
         std::vector<std::string>::const_iterator it;
         std::string initialVertex = _vertex.at(0);
         for(it = _vertex.begin(); it != _vertex.end(); ++it) {
            try {
               if(it + 1 != _vertex.end())
                  addEdge(*it, *(it + 1));
               else
                  addEdge(*it, initialVertex);
            }
            catch(std::exception e) {
               std::cout << e.what();
            }
         }
      }
   }
}

Graph Graph::generateRandomGraph(int maxVertex, bool graphType) {
   srand(time(NULL));
   int fromInt = rand() % maxVertex;
   int toInt = rand() % maxVertex;
   std::string ivt = std::min(utility::to_string(fromInt), utility::to_string(toInt)) +
                     "-" +
                     std::max(utility::to_string(toInt), utility::to_string(fromInt));

   Graph G(ivt, Graph::random, graphType);
   return G;
}

void Graph::addVertex(std::string node) {
      _vertex.push_back(node);
}

void Graph::addEdge(std::string fromNode, std::string toNode, double cost) {
   if(std::find(_vertex.begin(), _vertex.end(), fromNode) != _vertex.end() &&
      std::find(_vertex.begin(), _vertex.end(), toNode)   != _vertex.end()) {

      if(direct) {
         _edge.push_back(std::make_pair(fromNode, toNode));
         _edgeWeight[std::make_pair(fromNode, toNode)] = cost;
      }
      else { //undirected graph
         _edge.push_back(std::make_pair(fromNode, toNode));
         _edge.push_back(std::make_pair(toNode, fromNode));
         _edgeWeight[std::make_pair(fromNode, toNode)] = cost;
         _edgeWeight[std::make_pair(toNode, fromNode)] = cost;
      }
   }
   else throw std::out_of_range("invalid edge");
}

void Graph::setWeight(std::string fromNode, std::string toNode, double cost) {
   if(std::find(_vertex.begin(), _vertex.end(), fromNode) != _vertex.end() &&
      std::find(_vertex.begin(), _vertex.end(), toNode)   != _vertex.end()) {

      if(direct) {
         _edgeWeight[std::make_pair(fromNode, toNode)] = cost;
      }
      else { // undirected Graph
         _edgeWeight[std::make_pair(fromNode, toNode)] = cost;
         _edgeWeight[std::make_pair(toNode, fromNode)] = cost;
      }
   }
   else throw std::out_of_range("invalid edge");
}

bool Graph::hasEdge(std::string fromNode, std::string toNode) const {
   return std::find(_edge.begin(),
                    _edge.end(),
                    std::make_pair(fromNode, toNode)) != _edge.end();
}

double Graph::weight(std::string fromNode, std::string toNode) const {
   if(_edgeWeight.find(std::make_pair(fromNode, toNode)) != _edgeWeight.end())
      return _edgeWeight.at(std::make_pair(fromNode, toNode));
   else throw std::out_of_range("invalid edge");
}

void Graph::print(std::ostream& os) const {
   std::vector<std::string>::const_iterator V;
   std::vector<link>::const_iterator E;

   os << "Vertex : { ";
   for(V = _vertex.begin(); V != _vertex.end(); ++V) {
      os << *V;
      if(V + 1 != _vertex.end())
         os << " , ";
   }

   os << " }" << std::endl << "Edge : { " << std::endl;

   for(E = _edge.begin();  E != _edge.end(); ++E)
      os << "\t( "
                << E->first  << " , " << E->second
                << " ) "
                << " weight: " << _edgeWeight.at(*E) << std::endl;

   os << std::endl << "}" << std::endl;
}

std::set<std::string> Graph::adjacent(std::string v) const {
   std::set<std::string> adjV;
   std::vector<link>::const_iterator E;
   for(E = _edge.begin(); E != _edge.end(); ++E) {
      if(E->first == v)
         adjV.insert(E->second);
   }
   return adjV;
}