#Graph

C++ graph library that offers the possibility to :

- Define empty Graph directed/undirected
- Define graph using regex  
- Copy constructor
- Adding node
- Remove node
- Adding edge and weighted edge
- Remove edge
- Print to standard output
- Draw the graph using a [javascript library](http://www.graphdracula.net/)
- Other utility graph functions

#Installation
On linux run the command make 

#Example

```{c++}
Graph G1 = Graph::generateRandomGraph(10);   
Graph G4(Graph::undirected);  
Graph G2("a-g", Graph::circular);  
Graph G3("1-45", Graph::random);  
G3.addNode("46");  
G4.addEdge("3", "2");  
G4.addEdge("23", "34", 5);   
.......  
G4.print();  // print to standard output  
G4.draw();   //generate html page with graphical representation of the graph  
```





