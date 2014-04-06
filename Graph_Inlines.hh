#ifndef GRAPH_INLINES_HH
#define GRAPH_INLINES_HH 1

typedef std::pair<std::string, std::string> link;  // eg. <v. u>

inline unsigned
Graph::vertex() const {
   return _vertex.size();
}

inline std::vector<std::string>
Graph::_Vertex() const {
   return _vertex;
}

inline std::vector<link>
Graph::_Edge() const {
   return _edge;
}

inline std::map<link, double>
Graph::_EdgeWeight() const {
   return _edgeWeight;
}

inline unsigned
Graph::edge() const {
   return _edge.size();
}

inline unsigned
Graph::rank(std::string v) const {
   return adjacent(v).size();
}

inline bool
Graph::isRegular() const {
   return minRank() == maxRank() ? true : false;
}

inline bool
Graph::isOriented() const {
   return direct;
}

inline std::ostream&
operator<<(std::ostream& os, const Graph& g) {
   g.print(os);
   return os;
}

#endif