$(document).ready(function() {
var width = $(document).width();
var height = $(document).height();
var g = new Graph();
g.edgeFactory.template.style.directed = false;
var render = function(r, n) { 
var set = r.set().push(
r.circle(n.point[0], n.point[1]-13, 60, 44).attr({"fill": "#8b8d8b", r : "11px","stroke-width" : "0.4px"})).push(
r.text(n.point[0], n.point[1] + 5, (n.label || n.id)));
return set; }
g.addNode("E", {render:render});
g.addNode("T", {render:render});
g.addNode("P", {render:render});
g.addNode("+", {render:render});
g.addNode("*", {render:render});
g.addEdge("E", "E",{label : "2","label-style" : {"font-size": 15},fill : "#bebebe",stroke: "#646464"});
g.addEdge("E", "E",{label : "2","label-style" : {"font-size": 15},fill : "#bebebe",stroke: "#646464"});
g.addEdge("E", "+",{label : "1","label-style" : {"font-size": 15},fill : "#bebebe",stroke: "#646464"});
g.addEdge("+", "E",{label : "1","label-style" : {"font-size": 15},fill : "#bebebe",stroke: "#646464"});
g.addEdge("E", "T",{label : "1","label-style" : {"font-size": 15},fill : "#bebebe",stroke: "#646464"});
g.addEdge("T", "E",{label : "1","label-style" : {"font-size": 15},fill : "#bebebe",stroke: "#646464"});
g.addEdge("E", "T",{label : "1","label-style" : {"font-size": 15},fill : "#bebebe",stroke: "#646464"});
g.addEdge("T", "E",{label : "1","label-style" : {"font-size": 15},fill : "#bebebe",stroke: "#646464"});
g.addEdge("T", "P",{label : "1","label-style" : {"font-size": 15},fill : "#bebebe",stroke: "#646464"});
g.addEdge("P", "T",{label : "1","label-style" : {"font-size": 15},fill : "#bebebe",stroke: "#646464"});
g.addEdge("T", "T",{label : "2","label-style" : {"font-size": 15},fill : "#bebebe",stroke: "#646464"});
g.addEdge("T", "T",{label : "2","label-style" : {"font-size": 15},fill : "#bebebe",stroke: "#646464"});
g.addEdge("T", "*",{label : "1","label-style" : {"font-size": 15},fill : "#bebebe",stroke: "#646464"});
g.addEdge("*", "T",{label : "1","label-style" : {"font-size": 15},fill : "#bebebe",stroke: "#646464"});
g.addEdge("T", "P",{label : "1","label-style" : {"font-size": 15},fill : "#bebebe",stroke: "#646464"});
g.addEdge("P", "T",{label : "1","label-style" : {"font-size": 15},fill : "#bebebe",stroke: "#646464"});
var layouter = new Graph.Layout.Spring(g);
layouter.layout();
var renderer = new Graph.Renderer.Raphael('canvas', g, width, height);
renderer.draw();
});
