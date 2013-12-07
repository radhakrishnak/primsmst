#ifndef _GRAPH
#define _GRAPH

#include <stdio.h>
#include <iostream>
#include <vector>
#include "adjnode.h"
#include "edge.h"

using namespace std;
class graph {
    public:
		int numberOfNodes;
		std::vector<adjnode*> nodeList;
		std::vector<edge*> edgeList;
		graph(int);
		~graph();
		void insertEdge(int src,int dst,int cost);    	
		void printGraph();
		void primsGraph(graph* g);
		void DepthFirstRecur(int value, bool visited[]) ;
		bool DepthFirstSearch(int value);

};
#endif //_GRAPH
