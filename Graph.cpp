#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstdlib>
#include <fstream>
#include <climits>
#include <ctime>
#include "Graph.hh"
#include "Utility.hh"

using namespace GraphLib;

typedef std::pair<std::string, std::string> link;
typedef std::map<std::string, bool> mapStringBool;

int  Graph::random = 0;
int  Graph::circular = 1;
bool Graph::directed = true;
bool Graph::undirected = false;

Graph::Graph(bool graphType) {
   direct = graphType;
}

Graph::Graph(const Graph& G) {
   _node = G._Node();
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
            _node.push_back(utility::to_string(*it));
      }
      else if(regex.length() > 3) { //10-17,  12-102 ...
         std::vector<int> tmp = utility::regexInt(regex);
         std::vector<int>::const_iterator it;
         for(it = tmp.begin(); it != tmp.end(); ++it)
            _node.push_back(utility::to_string(*it));
      }
   }
   _generateEdge(edgeType);
}

void Graph::_generateEdge(int edgeType) {
   switch(edgeType) {
      case 0: { // random
         srand(time(NULL));
         for(unsigned i = 0; i < nodes(); ++i) {
            int randNode1 = rand() % nodes();
            int randNode2 = rand() % nodes();
            double randWeight = rand() % 100;
            if(randNode1 != randNode2)
               addEdge(_node.at(randNode1), _node.at(randNode2), randWeight);
         }
      }
      case 1: { // circular
         std::string initialNode = _node.at(0);
         std::vector<std::string>::const_iterator it;
         for(it = _node.begin(); it != _node.end(); ++it) {
            if(it + 1 != _node.end())
               addEdge(*it, *(it + 1));
            else
               addEdge(*it, initialNode);
         }
      }
   }
}

Graph Graph::generateRandomGraph(int maxNode, bool graphType) {
   srand(time(NULL));
   int fromInt = rand() % maxNode;
   int toInt = rand() % maxNode;
   std::string ivt = std::min(utility::to_string(fromInt), utility::to_string(toInt)) +
                     "-" +
                     std::max(utility::to_string(toInt), utility::to_string(fromInt));

   Graph G(ivt, Graph::random, graphType);
   return G;
}

Graph Graph::transpose() {
  Graph G;
  for(auto e = _edge.begin(); e != _edge.end(); ++e) {
    G.addEdge(e->second, e->first, weight(e->first, e->second));
  }
  return G;
}

void Graph::addNode(std::string node) {
      _node.push_back(node);
}

void Graph::removeNode(std::string node) {
   std::vector<std::string>::iterator v;
   std::vector<link>::iterator e;
   std::vector<link> edgeToRemove;
   v = std::find(_node.begin(), _node.end(), node);
   if(v != _node.end()) {
      // remove the edge connected to the node
      for(e = _edge.begin(); e != _edge.end(); ++e) {
         if(direct) {
            if(e->first == node || e->second == node)
               edgeToRemove.push_back(std::make_pair(e->first, e->second));
               //removeEdge(e->first, e->second);
         }
         else {
            if(e->first == node)
               edgeToRemove.push_back(std::make_pair(e->first, e->second));
               //removeEdge(e->first, e->second);
         }
      }
      // removing edges
      for(e = edgeToRemove.begin(); e != edgeToRemove.end(); ++e)
         removeEdge(e->first, e->second);
      _node.erase(v);
   }
}

void Graph::addEdge(std::string fromNode, std::string toNode, double cost) {
   // if the nodes do not exist, create them
   if(!exist(fromNode))
      addNode(fromNode);
   
   if(!exist(toNode))
      addNode(toNode);

   if(!hasEdge(fromNode, toNode)) {
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
}

void Graph::removeEdge(std::string fromNode, std::string toNode) {
   if(hasEdge(fromNode, toNode) && exist(fromNode) && exist(toNode)) {
      if(direct) {
         _edge.erase(std::find(_edge.begin(), _edge.end(), 
                               std::make_pair(fromNode, toNode)));
         _edgeWeight.erase(std::make_pair(fromNode, toNode));
      }
      else { //undirected graph
         _edge.erase(std::find(_edge.begin(), _edge.end(), 
                               std::make_pair(fromNode, toNode)));
         _edge.erase(std::find(_edge.begin(), _edge.end(), 
                               std::make_pair(toNode, fromNode)));
         _edgeWeight.erase(std::make_pair(fromNode, toNode));
         _edgeWeight.erase(std::make_pair(toNode, fromNode));
      }
   }
}

void Graph::setWeight(std::string fromNode, std::string toNode, double cost) {
   if(exist(fromNode) && exist(toNode)) {
      if(direct) {
         _edgeWeight[std::make_pair(fromNode, toNode)] = cost;
      }
      else { // undirected Graph
         _edgeWeight[std::make_pair(fromNode, toNode)] = cost;
         _edgeWeight[std::make_pair(toNode, fromNode)] = cost;
      }
   }
}

void Graph::print(std::ostream& os) const {
   std::vector<std::string>::const_iterator V;
   std::vector<link>::const_iterator E;
   os << "Node : { ";
   for(V = _node.begin(); V != _node.end(); ++V) {
      os << *V;
      if(V + 1 != _node.end())
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

std::list<std::string> Graph::adjacent(std::string v) const {
   std::list<std::string> adj;
   std::vector<link>::const_iterator E;
   for(E = _edge.begin(); E != _edge.end(); ++E) {
      if(E->first == v)
         adj.push_back(E->second);
   }
   return adj;
}

unsigned Graph::minRank() const {
   unsigned min;
   std::vector<std::string>::const_iterator v = _node.begin();
   min = rank(*v);

   for(v = _node.begin() + 1; v != _node.end(); ++v) {
      if(v != _node.end())
         if(rank(*v) < min)
            min = rank(*v);
   }
   return min;
}

unsigned Graph::maxRank() const {
   unsigned max;
   std::vector<std::string>::const_iterator v = _node.begin();
   max = rank(*v);

   for(v = _node.begin() + 1; v != _node.end(); ++v) {
      if(v != _node.end())
         if(rank(*v) > max)
            max = rank(*v);
   }
   return max;
}

bool Graph::hasNegativeWeigth() const {
   std::map<link, double>::const_iterator w;
   for(w = _edgeWeight.begin(); w != _edgeWeight.end(); ++w) {
      if(w->second < 0)
         return true;
   }
   return false;
}

void Graph::_generateHtmlPage() const {
   std::ofstream f_html("G.html");
   system("mkdir html");
   f_html << "<html>" << std::endl
          << "   <head>" << std::endl
          << "      <script type=\"text/javascript\" src=\"../js/raphael-min.js\"></script>" << std::endl
          << "      <script type=\"text/javascript\" src=\"../js/dracula_graffle.js\"></script>" << std::endl
          << "      <script type=\"text/javascript\" src=\"../js/dracula_algorithms.js\"></script>" << std::endl
          << "      <script type=\"text/javascript\" src=\"../js/dracula_graph.js\"></script>" << std::endl
          << "      <script type=\"text/javascript\" src=\"../js/jquery-1.4.2.min.js\"></script>" << std::endl
          << "      <script type=\"text/javascript\" src=\"G.js\"></script>" << std::endl
          << "      <style type=\"text/css\">" << std::endl
          << "         body {" << std::endl
          << "            overflow: hidden;" << std::endl
          << "         }" << std::endl
          << "      </style>" << std::endl
          << "   </head>" << std::endl
          << "   <body>" << std::endl
          << "      <div id = \"canvas\"></div>" << std::endl
          << "   </body>" << std::endl
          << "</html>" << std::endl;
   f_html.close();
   system("cp G.html html/");
   system("rm G.html");
}

void Graph::_generateJavascriptPage() const {
   std::ofstream f_js("G.js");
   f_js << "$(document).ready(function() {" << std::endl
        << "var width = $(document).width();" << std::endl   // dimension of the div
        << "var height = $(document).height();" << std::endl // dimension of the div
        << "var g = new Graph();" << std::endl;

   if(direct)
      f_js << "g.edgeFactory.template.style.directed = true;" << std::endl;
   else
      f_js << "g.edgeFactory.template.style.directed = false;" << std::endl;

   //customize the nodes
   f_js << "var render = function(r, n) { " << std::endl
        << "var set = r.set().push(" << std::endl
        << "r.circle(n.point[0], n.point[1]-13, 60, 44).attr({\"fill\": \"#8b8d8b\", r : \"11px\""
        << ",\"stroke-width\" : \"0.4px\"})).push(" << std::endl
        << "r.text(n.point[0], n.point[1] + 5, (n.label || n.id)));" << std::endl
        << "return set; }" << std::endl;

   //generate the nodes
   std::vector<std::string>::const_iterator v;
   for(v = _node.begin(); v != _node.end(); ++v) {
      f_js << "g.addNode(\"" << *v << "\", {render:render});" << std::endl;
   }

   //generate the edges
   std::vector<link>::const_iterator e;
   for(e = _edge.begin(); e != _edge.end(); ++e) {
      // insert the weight into the javascript code
      double w = weight(e->first, e->second);

      std::string st = ",{label : \"" + utility::to_string(w) + "\",\"" +
                       "label-style\" : {\"font-size\": 15}," +
                       "fill : \"#bebebe\"," +
                       "stroke: \"#646464\"}";
      f_js << "g.addEdge(\"" << e->first << "\", \"" << e->second <<"\"" << st << ");" << std::endl;
   }

   //draw using the dracula library
   f_js << "var layouter = new Graph.Layout.Spring(g);" << std::endl
        << "layouter.layout();" << std::endl
        << "var renderer = new Graph.Renderer.Raphael('canvas', g, width, height);" << std::endl
        << "renderer.draw();" << std::endl
        << "});" << std::endl;

   f_js.close();
   system("cp G.js html/");
   system("rm G.js");
}

void Graph::draw() const {
   _generateHtmlPage();
   _generateJavascriptPage();
   system("xdg-open html/G.html &"); // execute default browser
}

// Time Complexity of this method is same as time complexity of DFS traversal which is O(V+E)
bool Graph::isCyclic() const {
   // Mark all the vertices as not visited and not part of recursion
   // stack
   mapStringBool visited;
   mapStringBool recStack;
   std::vector<std::string>::const_iterator i;
   for(i = _node.begin(); i != _node.end(); ++i) {
      visited[*i] = false;
      recStack[*i] = false;
   }
 
   // Call the recursive helper function to detect cycle in different
   // DFS trees
   for(i = _node.begin(); i != _node.end(); ++i) {
      if(_isCyclicUtil(*i, visited, recStack))
         return true;
   }
   return false;
}

bool Graph::_isCyclicUtil(std::string v, mapStringBool visited, mapStringBool recStack) const {
   if(visited[v] == false) {
      // Mark the current node as visited and part of recursion stack
      visited[v]= true;
      recStack[v]= true;
 
      // Recur for all the vertices adjacent to this vertex
      for(auto i = adjacent(v).begin(); i != adjacent(v).end(); ++i) {
         if(!visited[*i] && _isCyclicUtil(*i, visited, recStack))
            return true;
         else if(recStack[*i])
            return true;
      }
   }
   recStack[v]= false;  // remove the vertex from recursion stack
   return false;
}

// FIXED By Wyvilo
// Assigns colors (starting from 0) to all vertices and prints
// the assignment of colors
void Graph::coloring() {
   Graph Gt = this->transpose();

   // remove common edges
   for(auto e = this->_edge.begin(); e != this->_edge.end(); ++e)
      Gt.removeEdge(e->first, e->second);

   // temporaly turn graph into undirected (if not)
   for(auto e = this->_edge.begin(); e != this->_edge.end(); ++e)
      this->addEdge(e->first, e->second, 1);

   std::map<std::string, int> result;
   // Assign the first color to first vertex
   result[*(_node.begin())] = 0;

   // Initialize remaining V-1 vertices as unassigned
   for(auto u = _node.begin() + 1; u != _node.end(); ++u)
      result[*u] = -1;  // no color is assigned to u
 
   // Assign colors to remaining V-1 vertices
   for(auto u = _node.begin() + 1; u != _node.end(); ++u) {   
      // Process all adjacent vertices and flag their colors
      // as unavailable
      std::list<std::string> adj = adjacent(*u); 
      
      signed color = -1;
      bool found = false;
      while(!found) {
         ++color;
         found = true;
         for(auto v = adj.begin(); v != adj.end(); ++v) {
            if(color == result[*v]) {
               found = false;
               break;
            }
         } 
      }

      result[*u] = color; // Assign the found color
   }
 
   // print the result
   for(auto u = _node.begin(); u != _node.end(); ++u) 
      std::cout << "Vertex " << *u << " --->  Color " << result[*u] << std::endl;

   for(auto e = Gt._edge.begin(); e != Gt._edge.end(); ++e)
      this->removeEdge(e->first, e->second);   

}

