/*
   @file    Graph.hh
   @author  Ayoub Ouarrak, ouarrakayoub@gmail.com
   @version 1.0
*/
#ifndef GRAPH_LIB_HH
#define GRAPH_LIB_HH 1

#include <algorithm>
#include <utility>
#include <string>
#include <vector>
#include <list>
#include <map>
 
namespace GraphLib {

/** C++ implementation of a directed/undirected graph using the STL 
    and the dracula javasript library to draw the graph
*/
class Graph {

public:
   /** generate a random edge to connect the Node */
   static int random;       
   /** generate a edge that forms a circular graph */
   static int circular;  
   /** generate directed Graph */
   static bool directed;  
   /** generate undirected Graph */
   static bool undirected;  
   /** generate random Graph with (max) n Node */
   static Graph  generateRandomGraph(int, bool graphType = directed); 

   /** operator= is not implemented */
   Graph& operator=(const Graph&) = delete; 

   explicit Graph(bool graphType = directed);
   
   Graph(std::string regex, int edgeMode, bool graphType = directed);  
   Graph(const Graph&); 
   /** default Distructor*/
   ~Graph() = default;  

   Graph transpose();  
   void  DFS(std::string sourceNode); 
   void  BFS(std::string sourceNode);
   void  floydWarshell(double** graph);
   void  coloring();    
   void  draw() const;  
   void  print(std::ostream&) const;   
   void  addNode(std::string node);    
   void  removeNode(std::string node); 
   void  addEdge(std::string fromNode, std::string toNode, double cost = 1);
   void  removeEdge(std::string from, std::string toNode);
   void  setWeight(std::string fromNode, std::string toNode, double cost);
   bool  hasNegativeWeigth() const;
   bool  isCyclic() const;
   bool  isConnected() const;
   int   isEulerian() const; 
   int** fromListADJToMatrixADJ(); 

   double** weightMatrix();

   unsigned minRank() const;
   unsigned maxRank() const;

   std::list<std::string> adjacent(std::string v) const; 

   inline bool hasEdge(std::string fromNode, std::string toNode) const;
   inline bool isOriented() const;
   inline bool isRegular() const;        
   inline bool exist(std::string) const; 

   inline unsigned nodes() const;
   inline unsigned edges() const; 
   inline unsigned rank(std::string v) const; 
   inline double   weight(std::string fromNode, std::string toNode) const;  

private: 
   /** direct graph or undirect */
   bool direct;  
   
   /** eg. <v. u> */
   typedef std::pair<std::string, std::string> link;  
   typedef std::map<std::string, bool> mapStringBool;

   /** eg. {v1, v2, v3, ...} */
   std::vector<std::string> _node;     
   /** eg. {<v1, u1>, <v2, u2>, ...}  */  
   std::vector<link>        _edge;   
   /** eg. {<v1,u1> = 1, <v2,u2> = 1 ,...}  */    
   std::map<link, double>   _edgeWeight;  

   inline std::vector<std::string> _Node() const;        
   inline std::vector<link>        _Edge() const;        
   inline std::map<link, double>   _EdgeWeight() const;  
   
   void _DFSUtil(std::string v, mapStringBool& visited) const;
   void _DFSUtil2(std::string v, mapStringBool& visited) const;
   void _generateHtmlPage() const;   
   void _generateJavascriptPage() const;
   void _generateEdge(int);          
   bool _isCyclicUtil(std::string v, mapStringBool visited, mapStringBool recStack) const; 
   void _printSolutionFloydWarshell(int** dist);

/** class Graph */
};  

std::ostream& operator<<(std::ostream& os, const GraphLib::Graph& g);  

/** include inline functions */
#include "Graph_Inlines.hh"  

/** namespace GraphLib */
} 

#endif //GRAPH_LIB_HH