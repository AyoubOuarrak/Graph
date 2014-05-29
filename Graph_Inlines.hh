/*
   @file    Graph_inlines.hh
   @author  Ayoub Ouarrak, ouarrakayoub@gmail.com
   @version 1.0
*/
#ifndef GRAPH_INLINES_HH
#define GRAPH_INLINES_HH 1

/** eg. <v. u> */
typedef std::pair<std::string, std::string> link;  

/**
   @return number of nodes
*/
inline unsigned
Graph::nodes() const {
   return _node.size();
}

/**
   @return vector of nodes
*/
inline std::vector<std::string>
Graph::_Node() const {
   return _node;
}

/**
   @return vector of edge
*/
inline std::vector<link>
Graph::_Edge() const {
   return _edge;
}

/**
   @return weight of edges
*/
inline std::map<link, double>
Graph::_EdgeWeight() const {
   return _edgeWeight;
}

/**
   @return number of edges
*/
inline unsigned
Graph::edges() const {
   return _edge.size();
}

/**
   @param  v node 
   @return number of nodes adjacent to v
*/
inline unsigned
Graph::rank(std::string v) const {
   return adjacent(v).size();
}

/**
   @return minRank = maxRank?
*/
inline bool
Graph::isRegular() const {
   return minRank() == maxRank() ? true : false;
}

/**
   @return graph oriented or not?
*/
inline bool
Graph::isOriented() const {
   return direct;
}

/**
   @param node to control
   @return exist node?
*/
inline bool
Graph::exist(std::string node) const {
   return std::find(_node.begin(), _node.end(), node) != _node.end();
}

/**
   @param  fromNode first node of edge
   @param  toNode   second node of edge
   @return exist edge: (fromNode, toNode)?
*/
inline bool
Graph::hasEdge(std::string fromNode, std::string toNode) const {
   return std::find(_edge.begin(), _edge.end(),
                    std::make_pair(fromNode, toNode)) != _edge.end();
}

/**
   @param  fromNode first node of edge
   @param  toNode   second node of edge
   @return weight of edge: (fromNode, toNode)
*/
inline double 
Graph::weight(std::string fromNode, std::string toNode) const {
   if(_edgeWeight.find(std::make_pair(fromNode, toNode)) != _edgeWeight.end())
      return _edgeWeight.at(std::make_pair(fromNode, toNode));
   return 0;
}

/**
   Overloaded << operator

   @param  os  ostream object
   @param  g   Graph object
   @return ostream object
*/ 
inline std::ostream&
operator<<(std::ostream& os, const Graph& g) {
   g.print(os);
   return os;
}

#endif