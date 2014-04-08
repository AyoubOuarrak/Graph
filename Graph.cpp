#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <iterator>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include "Graph.hh"
#include "Utility.hh"
#include "Graph_Algorithm.hh"

using namespace GraphLib;

typedef std::pair<std::string, std::string> link;
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
   else throw std::invalid_argument("invalid interval");

   generateEdge(edgeType);
}

void Graph::generateEdge(int edgeType) {
   switch(edgeType) {
      case 0: { // random
         srand(time(NULL));
         for(unsigned i = 0; i < nodes(); ++i) {
            int randNode1 = rand() % nodes();
            int randNode2 = rand() % nodes();
            if(randNode1 != randNode2)
               try {
                  addEdge(_node.at(randNode1), _node.at(randNode2));
               }
               catch(std::exception e) {
                  std::cout << e.what();
               }
         }
      }
      case 1: { // circular
         std::vector<std::string>::const_iterator it;
         std::string initialNode = _node.at(0);
         for(it = _node.begin(); it != _node.end(); ++it) {
            try {
               if(it + 1 != _node.end())
                  addEdge(*it, *(it + 1));
               else
                  addEdge(*it, initialNode);
            }
            catch(std::exception e) {
               std::cout << e.what();
            }
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

void Graph::addNode(std::string node) {
      _node.push_back(node);
}

void Graph::removeNode(std::string node) {
   std::vector<std::string>::iterator v;
   v = std::find(_node.begin(), _node.end(), node);
   if(v != _node.end()) {
      _node.erase(v);
      // remove the edge connected to the node
      std::vector<link>::const_iterator e;
      for(e = _edge.begin(); e != _edge.end(); ++e) {
         if(e->first == node)
            removeEdge(e->first, e->second);
         if(e->second == node)
            removeEdge(e->second, e->first);
      }
   }
   else throw std::out_of_range("invalid_argument");
}

void Graph::addEdge(std::string fromNode, std::string toNode, double cost) {
   if(std::find(_node.begin(), _node.end(), fromNode) != _node.end() &&
      std::find(_node.begin(), _node.end(), toNode)   != _node.end()) {

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

void Graph::removeEdge(std::string fromNode, std::string toNode) {
   if(std::find(_node.begin(), _node.end(), fromNode) != _node.end() &&
      std::find(_node.begin(), _node.end(), toNode)   != _node.end()) {

      if(direct) {
         _edge.erase(std::find(_edge.begin(),
                               _edge.end(),
                               std::make_pair(fromNode, toNode)));
         _edgeWeight.erase(std::make_pair(fromNode, toNode));
      }
      else { //undirected graph
         _edge.erase(std::find(_edge.begin(),
                               _edge.end(),
                               std::make_pair(fromNode, toNode)));
         _edge.erase(std::find(_edge.begin(),
                               _edge.end(),
                               std::make_pair(toNode, fromNode)));
         _edgeWeight.erase(std::make_pair(fromNode, toNode));
         _edgeWeight.erase(std::make_pair(toNode, fromNode));
      }
   }
   else throw std::out_of_range("invalid edge");
}

void Graph::setWeight(std::string fromNode, std::string toNode, double cost) {
   if(std::find(_node.begin(), _node.end(), fromNode) != _node.end() &&
      std::find(_node.begin(), _node.end(), toNode)   != _node.end()) {

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
   std::vector<link>::const_iterator E = _edge.begin();
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

std::set<std::string> Graph::adjacent(std::string v) const {
   std::set<std::string> adjV;
   std::vector<link>::const_iterator E;
   for(E = _edge.begin(); E != _edge.end(); ++E) {
      if(E->first == v)
         adjV.insert(E->second);
   }
   return adjV;
}

unsigned Graph::minRank() const {
   unsigned min;
   std::vector<std::string>::const_iterator v = _node.begin();
   min = rank(*v);
   for(v = _node.begin(); v != _node.end(); ++v) {
      if(v + 1 != _node.end())
         if(rank(*(v + 1)) < min)
            min = rank(*(v + 1));
   }
   return min;
}

unsigned Graph::maxRank() const {
   unsigned max;
   std::vector<std::string>::const_iterator v = _node.begin();
   max = rank(*v);
   for(v = _node.begin(); v != _node.end(); ++v) {
      if(v + 1 != _node.end())
         if(rank(*(v + 1)) > max)
            max = rank(*(v + 1));
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

bool Graph::isConnected() const {
   GraphAlgorithm::DepthFirstSearch dfs(*this, _node[0]);
   return dfs.nodeConnected() == _node.size();
}

void Graph::generateHtmlPage() {
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
//I apologize for the ugliness of this function
void Graph::generateJavascriptPage() {
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

void Graph::draw() {
   generateHtmlPage();
   generateJavascriptPage();
   system("xdg-open html/G.html &"); // execute default browser
}
