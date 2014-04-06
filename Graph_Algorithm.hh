/*
 *  Author : Ouarrak Ayoub
 *  Date   : ~/04/2014
*/

#ifndef GUARD_GRAPH_ALGORITHM_HH
#define GUARD_GRAPH_ALGORITHM_HH

#include "Graph.hh"
#include <iterator>
 #include <iostream>
#include <string>
#include <set>
#include <map>

namespace GraphAlgorithm {

class DepthFirstSearch {
private:
   std::map<std::string, bool> _marked;    // marked[v] = is there an s-v path?
   int _count;                   // number of vertices connected to s

public:
   DepthFirstSearch(const GraphLib::Graph& G, std::string sourceVertex) {
      _count = 0;
      dfs(G, sourceVertex);
   }

   void dfs(const GraphLib::Graph& G, std::string sourceVertex) {
      _count++;
      _marked[sourceVertex] = true;

      std::set<std::string> adj = G.adjacent(sourceVertex);
      std::set<std::string>::const_iterator adjIt;

      for (adjIt = adj.begin(); adjIt != adj.end(); ++adjIt) {
         if (!_marked[*adjIt]) {
            dfs(G, *adjIt);
         }
      }
   }

   bool marked(std::string s) {
      return _marked.at(s);
   }

   std::map<std::string, bool>::iterator
   begin() {
      return _marked.begin();
   }

    std::map<std::string, bool>::iterator
   end() {
      return _marked.end();
   }

   unsigned vertexConnected() {
      return _count;
   }

}; // class DFS

} // namespace GraphAlgorithm

#endif