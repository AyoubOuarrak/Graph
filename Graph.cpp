/*
   @file    Graph.cpp
   @author  Ayoub Ouarrak, ouarrakayoub@gmail.com
   @version 1.0
*/
#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstdlib>
#include <fstream>
#include <climits>
#include <ctime>
#include <queue>
#include "Graph.hh"
#include "Utility.hh"

using namespace GraphLib;

/** Define Infinite as a large enough value. This value will be used
  for vertices not connected to each other */
#define INF 99999

typedef std::pair<std::string, std::string> link;
typedef std::map<std::string, bool> mapStringBool;

int  Graph::random = 0;
int  Graph::circular = 1;
bool Graph::directed = true;
bool Graph::undirected = false;

/**
   Constructor
   
   @param  graphType  directed/undirect graph
*/
Graph::Graph(bool graphType) {
   direct = graphType;
}

/**
   Copy contructor

   @param  Graph graph to copy
*/
Graph::Graph(const Graph& G) {
   _node = G._Node();
   _edge = G._Edge();
   _edgeWeight = G._EdgeWeight();
}

/**
   Add Node using regex eg. G("A-Z"), G(1-5), G(12-82)

   @param regex     regex eg. A-Z, 1-6
   @param edgeType  random/circular edges generation
   @param graphType directed/undirect graph
*/
Graph::Graph(std::string regex, int edgeType, bool graphType) {
   direct = graphType;
   if(utility::checkIfInterval(regex)) {
      /** 1-9,  a-z,  A-Z ... */
      if(regex.length() == 3) {  
         std::vector<char> tmp = utility::regexChar(regex);
         std::vector<char>::const_iterator it;
         for(it = tmp.begin(); it != tmp.end(); ++it)
            _node.push_back(utility::to_string(*it));
      }
      /** 10-17,  12-102 ... */
      else if(regex.length() > 3) { 
         std::vector<int> tmp = utility::regexInt(regex);
         std::vector<int>::const_iterator it;
         for(it = tmp.begin(); it != tmp.end(); ++it)
            _node.push_back(utility::to_string(*it));
      }
   }
   _generateEdge(edgeType);
}

/*
   Generate edges and add them to the graph

   @param  edgeType  random/circular edges generation
   @return void
*/
void Graph::_generateEdge(int edgeType) {
   switch(edgeType) {
      /** random */
      case 0: { 
         srand(time(NULL));
         for(unsigned i = 0; i < nodes(); ++i) {
            int randNode1 = rand() % nodes();
            int randNode2 = rand() % nodes();
            double randWeight = rand() % 100;
            if(randNode1 != randNode2)
               addEdge(_node.at(randNode1), _node.at(randNode2), randWeight);
         }
      }
      /** circular */
      case 1: { 
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

/** 
   Generate random graph
   
   @param maxNode   max node of the generated graph
   @param graphType directed/undirect graph
   @return Graph
*/
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

/** 
   Transpose of this graph 

   @return Graph
*/
Graph Graph::transpose() {
  Graph G;
  for(auto e = _edge.begin(); e != _edge.end(); ++e) {
    G.addEdge(e->second, e->first, weight(e->first, e->second));
  }
  return G;
}

/**
   Add node to the graph

   @param  node node to add
   @return void
*/
void Graph::addNode(std::string node) {
      _node.push_back(node);
}

/**
   Remove node from the graph

   @param  node node to remove
   @return void
*/
void Graph::removeNode(std::string node) {
   std::vector<std::string>::iterator v;
   std::vector<link>::iterator e;
   std::vector<link> edgeToRemove;
   
   v = std::find(_node.begin(), _node.end(), node);
   if(v != _node.end()) {
      /** remove the edge connected to the node */
      for(e = _edge.begin(); e != _edge.end(); ++e) {
         if(direct) {
            if(e->first == node || e->second == node)
               edgeToRemove.push_back(std::make_pair(e->first, e->second));
         }
         else {
            if(e->first == node)
               edgeToRemove.push_back(std::make_pair(e->first, e->second));
         }
      }
      /** removing edges */
      for(e = edgeToRemove.begin(); e != edgeToRemove.end(); ++e)
         removeEdge(e->first, e->second);
      _node.erase(v);
   }
}

/**
   Add edge to the graph

   @param  fromNode edge from node
   @param  toNode   edge to node
   @param  cost     weight of the edge, default is 1
   @return void
*/
void Graph::addEdge(std::string fromNode, std::string toNode, double cost) {
   /** if the nodes do not exist, create them */
   if(!exist(fromNode))
      addNode(fromNode);
   
   if(!exist(toNode))
      addNode(toNode);

   if(!hasEdge(fromNode, toNode)) {
      if(direct) {
         _edge.push_back(std::make_pair(fromNode, toNode));
         _edgeWeight[std::make_pair(fromNode, toNode)] = cost;
      }
      /** undirected graph */
      else { 
         _edge.push_back(std::make_pair(fromNode, toNode));
         _edge.push_back(std::make_pair(toNode, fromNode));
         _edgeWeight[std::make_pair(fromNode, toNode)] = cost;
         _edgeWeight[std::make_pair(toNode, fromNode)] = cost;
      }
   }
}

/**
   Remove edge from the graph

   @param  fromNode edge from node
   @param  toNode   edge to node
   @return void
*/
void Graph::removeEdge(std::string fromNode, std::string toNode) {
   if(hasEdge(fromNode, toNode)) {
      if(direct) {
         _edge.erase(std::find(_edge.begin(), _edge.end(), 
                               std::make_pair(fromNode, toNode)));
         _edgeWeight.erase(std::make_pair(fromNode, toNode));
      }
      /** undirected graph */
      else {
         _edge.erase(std::find(_edge.begin(), _edge.end(), 
                               std::make_pair(fromNode, toNode)));
         _edge.erase(std::find(_edge.begin(), _edge.end(), 
                               std::make_pair(toNode, fromNode)));
         _edgeWeight.erase(std::make_pair(fromNode, toNode));
         _edgeWeight.erase(std::make_pair(toNode, fromNode));
      }
   }
}

/** 
   Set weight to edge(fromNode, toNode)

   @param  toNode   edge to node
   @param  fromNode edge from node
   @return void
*/
void Graph::setWeight(std::string fromNode, std::string toNode, double cost) {
   if(exist(fromNode) && exist(toNode)) {
      if(direct) {
         _edgeWeight[std::make_pair(fromNode, toNode)] = cost;
      }
      /** undirected Graph */
      else { 
         _edgeWeight[std::make_pair(fromNode, toNode)] = cost;
         _edgeWeight[std::make_pair(toNode, fromNode)] = cost;
      }
   }
}

/** 
   Print the graph on the standard output 

   @return void
*/
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

/**
   adjacent list

*/
std::list<std::string> Graph::adjacent(std::string v) const {
   std::list<std::string> adj;
   std::vector<link>::const_iterator E;
   for(E = _edge.begin(); E != _edge.end(); ++E) {
      if(E->first == v)
         adj.push_back(E->second);
   }
   return adj;
}

/**
   Min rank of a graph

   @return unsigned
*/
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

/**
   Max rank of a graph

   @return unsigned
*/
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

/**
   Control if graph has negative weight

   @return bool
*/
bool Graph::hasNegativeWeigth() const {
   std::map<link, double>::const_iterator w;
   for(w = _edgeWeight.begin(); w != _edgeWeight.end(); ++w) {
      if(w->second < 0)
         return true;
   }
   return false;
}

/**
   Generate html page to draw the graph

   @return void
*/
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

/**
   Generate javascript page to draw the graph

   @return void
*/
void Graph::_generateJavascriptPage() const {
   std::ofstream f_js("G.js");
   f_js << "$(document).ready(function() {" << std::endl
        /** dimension of the div */
        << "var width = $(document).width();" << std::endl   
        /** dimension of the div */
        << "var height = $(document).height();" << std::endl 
        << "var g = new Graph();" << std::endl;

   if(direct)
      f_js << "g.edgeFactory.template.style.directed = true;" << std::endl;
   else
      f_js << "g.edgeFactory.template.style.directed = false;" << std::endl;

   /** customize the nodes */
   f_js << "var render = function(r, n) { " << std::endl
        << "var set = r.set().push(" << std::endl
        << "r.circle(n.point[0], n.point[1]-13, 60, 44).attr({\"fill\": \"#8b8d8b\", r : \"11px\""
        << ",\"stroke-width\" : \"0.4px\"})).push(" << std::endl
        << "r.text(n.point[0], n.point[1] + 5, (n.label || n.id)));" << std::endl
        << "return set; }" << std::endl;

   /** generate the nodes */
   std::vector<std::string>::const_iterator v;
   for(v = _node.begin(); v != _node.end(); ++v) {
      f_js << "g.addNode(\"" << *v << "\", {render:render});" << std::endl;
   }

   /** generate the edges */
   std::vector<link>::const_iterator e;
   for(e = _edge.begin(); e != _edge.end(); ++e) {
      /** insert the weight into the javascript code */
      double w = weight(e->first, e->second);

      std::string st = ",{label : \"" + utility::to_string(w) + "\",\"" +
                       "label-style\" : {\"font-size\": 15}," +
                       "fill : \"#bebebe\"," +
                       "stroke: \"#646464\"}";
      f_js << "g.addEdge(\"" << e->first << "\", \"" << e->second <<"\"" << st << ");" << std::endl;
   }

   /** draw using the dracula library */
   f_js << "var layouter = new Graph.Layout.Spring(g);" << std::endl
        << "layouter.layout();" << std::endl
        << "var renderer = new Graph.Renderer.Raphael('canvas', g, width, height);" << std::endl
        << "renderer.draw();" << std::endl
        << "});" << std::endl;

   f_js.close();
   system("cp G.js html/");
   system("rm G.js");
}

/** 
   draw the graph using html/javascript 

   @return void
*/
void Graph::draw() const {
   _generateHtmlPage();
   _generateJavascriptPage();
   /** execute default browser */
   system("xdg-open html/G.html &"); 
}

/** 
   Time Complexity of this method is same as time complexity of DFS traversal which is O(V+E)

   @return bool
*/
bool Graph::isCyclic() const {
   /** Mark all the vertices as not visited and not part of recursion
       stack */
   mapStringBool visited;
   mapStringBool recStack;
   std::vector<std::string>::const_iterator i;
   for(i = _node.begin(); i != _node.end(); ++i) {
      visited[*i] = false;
      recStack[*i] = false;
   }
 
   /** Call the recursive helper function to detect cycle in different
       DFS trees */
   for(i = _node.begin(); i != _node.end(); ++i) {
      if(_isCyclicUtil(*i, visited, recStack))
         return true;
   }
   return false;
}

/**
   Helper function to detect cycle in different DFS trees

   @return bool
*/
bool Graph::_isCyclicUtil(std::string v, mapStringBool visited, mapStringBool recStack) const {
   if(visited[v] == false) {
      /** Mark the current node as visited and part of recursion stack */
      visited[v]= true;
      recStack[v]= true;
 
      /** Recur for all the vertices adjacent to this vertex */
      for(auto i = adjacent(v).begin(); i != adjacent(v).end(); ++i) {
         if(!visited[*i] && _isCyclicUtil(*i, visited, recStack))
            return true;
         else if(recStack[*i])
            return true;
      }
   }
   /** remove the vertex from recursion stack */
   recStack[v]= false;  
   return false;
}

/** 
   Graph Coloring (Greedy Algorithm) :- FIXED By Wyvilo
   Assigns colors (starting from 0) to all vertices and prints
   the assignment of colors

   @return void
*/
void Graph::coloring() {
   Graph Gt = this->transpose();

   /** remove common edges */
   for(auto e = this->_edge.begin(); e != this->_edge.end(); ++e)
      Gt.removeEdge(e->first, e->second);

   /** temporaly turn graph into undirected (if not) */
   for(auto e = this->_edge.begin(); e != this->_edge.end(); ++e)
      this->addEdge(e->first, e->second, 1);

   std::map<std::string, int> result;
   /** Assign the first color to first vertex */
   result[*(_node.begin())] = 0;

   /** Initialize remaining V-1 vertices as unassigned */
   for(auto u = _node.begin() + 1; u != _node.end(); ++u)
      result[*u] = -1;  // no color is assigned to u
 
   /** Assign colors to remaining V-1 vertices */
   for(auto u = _node.begin() + 1; u != _node.end(); ++u) {   
      /** Process all adjacent vertices and flag their colors
          as unavailable */
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
      /** Assign the found color */
      result[*u] = color; 
   }
 
   /** print the result */
   for(auto u = _node.begin(); u != _node.end(); ++u) 
      std::cout << "Vertex " << *u << " --->  Color " << result[*u] << std::endl;

   for(auto e = Gt._edge.begin(); e != Gt._edge.end(); ++e)
      this->removeEdge(e->first, e->second);   
}

/**
   @param  v       source node
   @param  visited vector of boolean
   @return void
*/
void Graph::_DFSUtil(std::string v, mapStringBool& visited) const {
   /** Mark the current node as visited and print it */
   visited[v] = true;
   /** Recur for all the vertices adjacent to this vertex */
   std::list<std::string>::iterator i;
   std::list<std::string> adj = adjacent(v);
   for(i = adj.begin(); i != adj.end(); ++i)
      if(!visited[*i]) 
         _DFSUtil(*i, visited);
}

void Graph::_DFSUtil2(std::string v, mapStringBool& visited) const {
   /** Mark the current node as visited and print it */
   visited[v] = true;
   std::cout << v << " ";
 
   /** Recur for all the vertices adjacent to this vertex */
   std::list<std::string>::iterator i;
   std::list<std::string> adj = adjacent(v);
   for(i = adj.begin(); i != adj.end(); ++i)
      if(!visited[*i]) 
         _DFSUtil2(*i, visited);
}

/** 
   DFS traversal of the vertices reachable from v. It uses recursive _DFSUtil()
*/
void Graph::DFS(std::string sourceNode) {
   /** Mark all the vertices as not visited */
   mapStringBool visited;
   for(auto u = _node.begin(); u != _node.end(); ++u) 
      visited[*u] = false;
 
   // Call the recursive helper function to print DFS traversal
   _DFSUtil2(sourceNode, visited);
}

/**
   Breadth First Traversal for a Graph
*/
void Graph::BFS(std::string sourceNode) {
   /** Mark all the vertices as not visited */
   mapStringBool visited;
   for(auto u = _node.begin(); u != _node.end(); ++u) 
      visited[*u] = false;
 
   /** Create a queue for BFS */
   std::list<std::string> queue;
 
   /** Mark the current node as visited and enqueue it */
   visited[sourceNode] = true;
   queue.push_back(sourceNode);
 
   /** 'i' will be used to get all adjacent vertices of a vertex */
   std::list<std::string>::iterator i;
 
   while(!queue.empty()) {
      /** Dequeue a vertex from queue and print it */
      sourceNode = queue.front();
      std::cout << sourceNode << " ";
      queue.pop_front();
 
      /** Get all adjacent vertices of the dequeued vertex s
          If a adjacent has not been visited, then mark it visited
          and enqueue it */
      std::list<std::string>::iterator i;
      std::list<std::string> adj = adjacent(sourceNode);
      for(i = adj.begin(); i != adj.end(); ++i) {
         if(!visited[*i]) {
            visited[*i] = true;
            queue.push_back(*i);
         }
      }
   }
}

/** 
   Method to check if all non-zero degree vertices are connected.
   It mainly does DFS traversal starting from

   @return bool
*/
bool Graph::isConnected() const {
   /** Mark all the vertices as not visited */
   std::map<std::string, bool> visited;
   std::vector<std::string>::const_iterator u;
   for(u = _node.begin(); u != _node.end(); ++u) 
      visited[*u] = false;
 
   /** Find a vertex with non-zero degree */
   for(u = _node.begin(); u != _node.end(); ++u)
      if(adjacent(*u).size() != 0)
         break;
   std::string strU = *u;
   unsigned lastNode = atoi(strU.c_str());
   /** If there are no edges in the graph, return true */
   if(lastNode == nodes())
      return true;
 
   /** Start DFS traversal from a vertex with non-zero degree */
   _DFSUtil(*u, visited);
 
   /** Check if all non-zero degree vertices are visited */
   for(auto v = _node.begin(); v != _node.end(); ++v)
      if(visited[*v] == false && adjacent(*v).size() > 0) 
         return false;
   return true;
}

/** 
   The function returns one of the following values
   0 --> If grpah is not Eulerian
   1 --> If graph has an Euler path (Semi-Eulerian)
   2 --> If graph has an Euler Circuit (Eulerian)  
   
   @return integer
*/
int Graph::isEulerian() const {
   /** Check if all non-zero degree vertices are connected */
   if(isConnected() == false) {
      std::cout << "not connected" <<std::endl;
      return 0;
    }
 
   /** Count vertices with odd degree */
   int odd = 0;
   for(auto v = _node.begin(); v != _node.end(); ++v)
      if(adjacent(*v).size() & 1)
         odd++;
 
   /** If count is more than 2, then graph is not Eulerian */
   if(odd > 2)
      return 0;
 
   /** If odd count is 2, then semi-eulerian.
       If odd count is 0, then eulerian
       Note that odd count can never be 1 for undirected graph */
   return (odd)? 1 : 2;
}

/** 
   Convert adjacent list into a matrix
*/
int** Graph::fromListADJToMatrixADJ() {
   /** matrix allocation */
   int** ADJMatrix = new int*[nodes()];
   for(unsigned i = 0; i < nodes(); ++i)
      ADJMatrix[i] = new int[nodes()];

   /** initialize matrix */
   for(auto i = _node.begin(); i != _node.end(); ++i)
      for(auto j = _node.begin(); j != _node.end(); ++j) 
         ADJMatrix[atoi((*j).c_str())][atoi((*i).c_str())] = 0;

   for(auto j = _node.begin(); j != _node.end(); ++j) {
      std::list<std::string>::iterator k;
      std::list<std::string> adj = adjacent(*j);
      for(k = adj.begin(); k != adj.end(); ++k) {
         if(direct)  
            ADJMatrix[atoi((*k).c_str())][atoi((*j).c_str())] = 1;
         else {
            ADJMatrix[atoi((*j).c_str())][atoi((*k).c_str())] = 1;
            ADJMatrix[atoi((*k).c_str())][atoi((*j).c_str())] = 1;
         }
      }
   }

   return ADJMatrix;
}

/**
  @return matrix of edge's weight
*/

double** Graph::weightMatrix() {
   /** matrix allocation */
   int i, j, k;
   double** wMatrix = new double*[nodes()];
   for(unsigned i = 0; i < nodes(); ++i)
      wMatrix[i] = new double[nodes()];

    /** initialize matrix */
   for(auto ii = _node.begin(); ii != _node.end(); ++ii) {
      i = atoi((*ii).c_str());
      for(auto jj = _node.begin(); jj != _node.end(); ++jj) {
         j = atoi((*jj).c_str());
         if(*ii == *jj)
            wMatrix[j][i] = 0;
         else
            wMatrix[j][i] = INF;
      }
   }

   for(auto jj = _node.begin(); jj != _node.end(); ++jj) {
      j = atoi((*jj).c_str());
      std::list<std::string>::iterator kk;
      std::list<std::string> adj = adjacent(*jj);

      for(kk = adj.begin(); kk != adj.end(); ++kk) {
         k = atoi((*kk).c_str());
         if(direct) {
            wMatrix[k][j] = weight(*jj, *kk);
         }
         else {
            wMatrix[j][k] = weight(*jj, *kk);
            wMatrix[k][j] = weight(*jj, *kk);
         }
      }
   }
   return wMatrix;
}

/** 
   Solves the all-pairs shortest path problem using Floyd Warshall algorithm
*/
void Graph::floydWarshell(double** graph) {
   /** dist[][] will be the output matrix that will finally have the shortest
       distances between every pair of vertices */
   int i, j, k;
   int** dist = new int*[nodes()];
   for(unsigned i = 0; i < nodes(); ++i)
      dist[i] = new int[nodes()];
 
   /** Initialize the solution matrix same as input graph matrix. Or
       we can say the initial values of shortest distances are based
       on shortest paths considering no intermediate vertex. */
   for(auto ii = _node.begin(); ii != _node.end(); ++ii) {
      i = atoi((*ii).c_str());
      for(auto jj = _node.begin(); jj != _node.end(); ++jj) {
         j = atoi((*jj).c_str());
         dist[i][j] = graph[i][j];
      }
   }
 
   /** Add all vertices one by one to the set of intermediate vertices.
       ---> Before start of a iteration, we have shortest distances between all
       pairs of vertices such that the shortest distances consider only the
       vertices in set {0, 1, 2, .. k-1} as intermediate vertices.
       ----> After the end of a iteration, vertex no. k is added to the set of
       intermediate vertices and the set becomes {0, 1, 2, .. k} */
   for(auto kk = _node.begin(); kk != _node.end(); ++kk) {
      /** Pick all vertices as source one by one */
      k = atoi((*kk).c_str());
      for(auto ii = _node.begin(); ii != _node.end(); ++ii) {
         /** Pick all vertices as destination for the
             above picked source */
         i = atoi((*ii).c_str());
         for(auto jj = _node.begin(); jj != _node.end(); ++jj) {
            /** If vertex k is on the shortest path from
                i to j, then update the value of dist[i][j] */
            j = atoi((*jj).c_str());
            if(dist[i][k] + dist[k][j] < dist[i][j])
               dist[i][j] = dist[i][k] + dist[k][j];
         }
      }
   }
 
   // Print the shortest distance matrix
   _printSolutionFloydWarshell(dist);
}

/** 
   A utility function to print solution 
*/
void Graph::_printSolutionFloydWarshell(int** dist) {
   std::cout << "Following matrix shows the shortest distances" 
             << std::endl << " between every pair of vertices \n";
   int i, j;
   for(auto ii = _node.begin(); ii != _node.end(); ++ii) {
      i = atoi((*ii).c_str());
      for(auto jj = _node.begin(); jj != _node.end(); ++jj) {
         j = atoi((*jj).c_str());
         if(dist[i][j] == INF)
            std::cout <<  "INF\t";
         else
            std::cout << dist[i][j] << "\t";
      }
      std::cout << std::endl;
   }
}