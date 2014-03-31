#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <iterator>
#include <cstdlib>
#include <ctime>
#include "Graph.hh"
#include "Utility.hh"

typedef std::pair<std::string, std::string> link;
int Graph::random = 0;
int Graph::circular = 1;

Graph::Graph() {
}

Graph::Graph(const Graph& G) {
   _vertex = G._Vertex();
   _edge = G._Edge();
   _edgeWeight = G._EdgeWeight();
}

Graph::Graph(std::string regex, int edgeType) {
   // loading the vertex vector
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
   generateGraph(edgeType);
}

void Graph::generateGraph(int edgeType) {
   switch(edgeType) {
      case 0: { // random
         srand(time(NULL));
         for(int i = 0; i < _vertex.size(); ++i) {
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

Graph Graph::generateRandomGraph(int maxVertex) {
   srand(time(NULL));
   int fromInt = rand() % maxVertex;
   int toInt = rand() % maxVertex;
   std::string ivt = std::min(utility::to_string(fromInt), utility::to_string(toInt)) +
                     "-" +
                     std::max(utility::to_string(toInt), utility::to_string(fromInt));
   Graph G(ivt, Graph::random);

   return G;
}

void Graph::addVertex(std::string node) {
   _vertex.push_back(node);
}

void Graph::addEdge(std::string fromNode, std::string toNode, double cost) {
   if(std::find(_vertex.begin(), _vertex.end(), fromNode) != _vertex.end() &&
      std::find(_vertex.begin(), _vertex.end(), toNode)   != _vertex.end()) {
      _edge.push_back(std::make_pair(fromNode, toNode));
      _edgeWeight[std::make_pair(fromNode, toNode)] = cost;
   }
   else throw std::out_of_range("invalid edge");
}

void Graph::setWeight(std::string fromNode, std::string toNode, double cost) {
   if(std::find(_vertex.begin(), _vertex.end(), fromNode) != _vertex.end() &&
      std::find(_vertex.begin(), _vertex.end(), toNode)   != _vertex.end()) {
      _edgeWeight[std::make_pair(fromNode, toNode)] = cost;
   }
}

void Graph::addEdge(std::string fromNode, std::string toNode) {
   if(std::find(_vertex.begin(), _vertex.end(), fromNode) != _vertex.end() &&
      std::find(_vertex.begin(), _vertex.end(), toNode)   != _vertex.end()) {
      _edge.push_back(std::make_pair(fromNode, toNode));
      _edgeWeight[std::make_pair(fromNode, toNode)] = 0;
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

unsigned Graph::vertex() const {
   return _vertex.size();
}

std::vector<std::string> Graph::_Vertex() const {
   return _vertex;
}

std::vector<link> Graph::_Edge() const {
   return _edge;
}

std::map<link, double> Graph::_EdgeWeight() const {
   return _edgeWeight;
}

unsigned Graph::edge() const {
   return _edge.size();
}

void Graph::print() const {
   std::vector<std::string>::const_iterator V;
   std::vector<link>::const_iterator E;

   std::cout << "Vertex : { ";
   for(V = _vertex.begin(); V != _vertex.end(); ++V) {
      std::cout << *V;
      if(V + 1 != _vertex.end())
         std::cout << " , ";
   }

   std::cout << " }" << std::endl;

   std::cout << "Edge : { " << std::endl;
   for(E = _edge.begin();  E != _edge.end(); ++E)
      std::cout << "\t( "
                << E->first  << " , " << E->second
                << " ) "
                << " weight: " << _edgeWeight.at(*E) << std::endl;

   std::cout << std::endl << "}" << std::endl;
}