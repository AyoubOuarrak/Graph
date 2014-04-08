#ifndef GRAPH_INLINES_HH
#define GRAPH_INLINES_HH 1
typedef std::pair<std::string, std::string> link;  // eg. <v. u>

inline unsigned
Graph::nodes() const {
   return _node.size();
}

inline std::vector<std::string>
Graph::_Node() const {
   return _node;
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
Graph::edges() const {
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

inline bool
Graph::exist(std::string node) const {
   return std::find(_node.begin(), _node.end(), node) != _node.end();
}

inline bool
Graph::hasEdge(std::string fromNode, std::string toNode) const {
   return std::find(_edge.begin(),
                    _edge.end(),
                    std::make_pair(fromNode, toNode)) != _edge.end();
}
inline std::ostream&
operator<<(std::ostream& os, const Graph& g) {
   g.print(os);
   return os;
}

#endif