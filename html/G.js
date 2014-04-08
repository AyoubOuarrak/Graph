$(document).ready(function() {
var width = $(document).width();
var height = $(document).height();
var g = new Graph();
g.edgeFactory.template.style.directed = true;
var render = function(r, n) { 
var set = r.set().push(
r.circle(n.point[0], n.point[1]-13, 60, 44).attr({"fill": "#8b8d8b", r : "11px","stroke-width" : "0.4px"})).push(
r.text(n.point[0], n.point[1] + 5, (n.label || n.id)));
return set; }
g.addNode("v1", {render:render});
g.addNode("v2", {render:render});
g.addNode("v3", {render:render});
g.addNode("v4", {render:render});
g.addEdge("v1", "v3",{label : "5","label-style" : {"font-size": 15},fill : "#bebebe",stroke: "#646464"});
g.addEdge("v2", "v4",{label : "3","label-style" : {"font-size": 15},fill : "#bebebe",stroke: "#646464"});
g.addEdge("v1", "v2",{label : "6","label-style" : {"font-size": 15},fill : "#bebebe",stroke: "#646464"});
g.addEdge("v3", "v2",{label : "10","label-style" : {"font-size": 15},fill : "#bebebe",stroke: "#646464"});
var layouter = new Graph.Layout.Spring(g);
layouter.layout();
var renderer = new Graph.Renderer.Raphael('canvas', g, width, height);
renderer.draw();
});
