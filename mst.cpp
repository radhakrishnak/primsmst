#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include "graph.h"
#include "prim.h"

using namespace std;

int getRandomDst(int i,int numberOfVertices);
bool insertToGraph(graph* g,int src,int dst, int cost);
graph* generateRandomGraph(int noVertices,int noEdges);

int main(int argc, const char* argv[]){
	srand(time(NULL));
	if(argc < 2) {
		cout<<"Please give the mode to run (-r or -s or -f)"<<endl;
		exit(1);
	}
	int numberOfVertices = 0;
	int density = 0;
	if(strcmp(argv[1],"-r") == 0 && argc == 4){
		numberOfVertices = atoi(argv[2]);
		int n=numberOfVertices;
		density = atoi(argv[3]);
		int numberOfEdges = (n*(n-1)*density)/200;
		//		int i,j,cost;
		graph* g;
		//		for(int k=1;k<=numberOfEdges;k++){
		//			i=rand() % numberOfVertices;
		//			j=getRandomDst(i,numberOfVertices);
		//			cost=(rand()%1000)+1;
		//			g=insertToGraph(g,i,j,cost);
		//		}
		g = generateRandomGraph(numberOfVertices,numberOfEdges);
		prim p;
		//		g->printGraph();
		p.primsGraph(g,"-s");
		p.primsGraph(g,"-f");
		//		cout<<"==================="<<endl;
		//		g->printGraph();

	} else if(argc>=2 && argc<4 && strcmp(argv[1],"-r") == 0){
		cout<<"Mention the number of vertices and density"<<endl;
		exit(1);
	} else if(strcmp(argv[1],"-s") == 0 || strcmp(argv[1],"-f") == 0){
		if(argv[2]==NULL){
			cout<<"Please mention file name"<<endl;
			exit(1);
		}
		ifstream infile(argv[2]);
		std::string line;
		int vno=0,eno=0;
		int v1=0,v2=0,w=0;
		std::getline(infile,line);
		std::stringstream firstline(line);
		if(firstline >> vno >> eno){
//			cout<<vno<<"  "<<eno<<endl;
		}
		graph* g = new graph(vno);
		while(std::getline(infile,line)){
			std::stringstream iss(line);
			if(iss >> v1 >> v2 >> w){
				cout<<v1<<" "<<v2<<" "<<w<<endl;
				g->insertEdge(v1,v2,w);
			}
		}
		prim p;
		if(strcmp(argv[1],"-s") == 0){
			p.primsGraph(g,"-s");
		}else if(strcmp(argv[1],"-f") == 0){
			p.primsGraph(g,"-f");
		}
	} else{
		cout<<"Please give the mode to run (-r or -s or -f)"<<endl;
		exit(1);
	}

	return 0;
}

graph* generateRandomGraph(int noVertices,int noEdges){
	int i,j,cost;
	graph* g=new graph(noVertices);
	for(int k=1;k<=noEdges;k++){
		i=rand() % noVertices;
		j=getRandomDst(i,noVertices);
		cost=(rand()%1000)+1;
		if(!insertToGraph(g,i,j,cost)){
			k--;
		}
	}
	if(!g->DepthFirstSearch(1)){
//		cout<<"in BFS"<<endl;
		delete g;
		g=NULL;
		g=new graph(noVertices);
		g = generateRandomGraph(noVertices,noEdges);
	}
	return g;
}

int getRandomDst(int i,int numberOfVertices){
	int j = rand() % numberOfVertices;
	if(j==i){
		j = getRandomDst(i,numberOfVertices);
	}
	return j;
}



bool insertToGraph(graph* g,int src,int dst, int cost){
	bool result=false;
	if(src!=dst){
		//		unsigned int noofnodes = g->nodeList.size();
		//		for(std::vector<adjnode*>::iterator it=g->nodeList.begin();
		//				it!=g->nodeList.end();++it){
		bool found=false;
		adjnode* it = g->nodeList[src];
		std::vector<edge*>::iterator edgeIt;
		for(edgeIt=it->adjEdges.begin();
				edgeIt!=it->adjEdges.end();++edgeIt){

			//						int sData = (*edgeIt)->src->data;
			int dData = (*edgeIt)->dst->data;
			//						if(sData!=dst && dData!=src && sData!=src && dData!=dst){
			//							g->insertEdge(src,dst,cost);
			//							break;
			//						}

			if(dData==dst){
				found=true;
				break;
			}

			//						}
		}
		//		it = g->nodeList[dst];
		//		for(edgeIt=it->adjEdges.begin();
		//					edgeIt!=it->adjEdges.end();++edgeIt){
		//
		//		//						int sData = (*edgeIt)->src->data;
		//					int dData = (*edgeIt)->dst->data;
		//		//						if(sData!=dst && dData!=src && sData!=src && dData!=dst){
		//		//							g->insertEdge(src,dst,cost);
		//		//							break;
		//		//						}
		//
		//					if(dData==dst){
		//								found=true;
		//								}
		//
		//								//						}
		//							}

		if(!found){
			g->insertEdge(src,dst,cost);
			result = true;
		}



		//		}
	}
	return result;
}
