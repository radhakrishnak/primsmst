#include "graph.h"

graph::graph(int iMaxNodes):numberOfNodes(iMaxNodes){
	for (int i=0;i<numberOfNodes;i++)
	{
		adjnode* temp=new adjnode(i);
		nodeList.push_back(temp);
	}
}

graph::~graph(){
	nodeList.clear();
}

void graph::insertEdge(int srcData,int dstData,int cost){
	adjnode* a = nodeList[srcData];
	adjnode* b = nodeList[dstData];
	edge* atob = new edge(a,b,cost);
	edge* btoa = new edge(b,a,cost);
	 edgeList.push_back(atob);
	a->adjEdges.push_back(atob);
	b->adjEdges.push_back(btoa);
	// std::cout<<"insertEdge"<<std::	endl;
}


void graph::printGraph(){
	// for(unsigned int i =0;i<edgeList.size();i++){
	// 	std::cout<<edgeList[i]->src->data<<" -> "<<edgeList[i]->dst->data
	// 		<<" ("<<edgeList[i]->cost<<")"<<std::endl;
	// }
	for(unsigned int i =0;i<edgeList.size();i++){
		std::cout<<edgeList[i]->src->data<<" -> "<<edgeList[i]->dst->data
			<<" ("<<edgeList[i]->cost<<")"<<std::endl;
	}
}

void graph::DepthFirstRecur(int value, bool visited[]) {
    visited[value] = true;

    vector<edge*>::iterator it;
    for(it = nodeList[value]->adjEdges.begin(); it != nodeList[value]->adjEdges.end(); ++it)
        if(!visited[(*it)->dst->data])
        	DepthFirstRecur((*it)->dst->data, visited);
}

bool graph::DepthFirstSearch(int value) {
	// Mark all the vertices as not visited
	bool *visited = new bool[numberOfNodes];
	int final=0;
	for(int i = 0; i < numberOfNodes; i++)
		visited[i] = false;

	DepthFirstRecur(value, visited);

	for(int i=0;i<numberOfNodes;i++){
		if(visited[i])final++;

	}
	if(final==numberOfNodes)return true;
	else return false;
}
