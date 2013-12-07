#include "prim.h"
#include "edge.h"
#include <climits>
#include "fibheap.h"
#include <time.h>

prim::prim():minCost(0),noOfNodes(0){
}

prim::~prim(){

}
int totalMinCost;
void prim::primsGraph(graph* g,const char* s){
	if(g->numberOfNodes == 0) return;
	std::vector<edge*> result ;
	std::vector<edge*> fibresult;

	if(strcmp(s,"-s")==0){
		clock_t Start, Time;
		cout<<"Simple scheme"<<endl;

		Start = clock();
		generateSimple(g);
		Time = clock() - Start; // time in micro seconds

		cout<<"Time taken in Simple  is "<<Time<<endl;
		/*
		 * comment to get only time printed out without edges
		 */
//		for(unsigned int i = 0 ; i < result.size(); i++){
//				cout<<result[i]->src->data<<" - "<<result[i]->dst->data<<endl;
//		}
		/*
		 * end comment
		 */
	} else if(strcmp(s,"-f")==0){
				cout<<"Fibonacci scheme"<<endl;

				clock_t Start, Time;
				Start = clock();
				FibHeapPrimMst(g);
				Time = clock() - Start; // time in micro seconds

				cout<<"Time taken in Fibonacci is "<<Time<<endl;
	}
}


void prim::generateSimple(graph* a){
	int n=a->numberOfNodes;
	bool non_mst[n];
	int mst[n];
	int costs[n];

	for(int i=0;i<n;i++){
		costs[i]=INT_MAX;
		non_mst[i]=false;
	}

	costs[0]=0;
int simMinCost=0;
	mst[0]=-1;
	for(int i=0;i<n;i++){

		int tmp  ,tmp2=INT_MAX;

		for(int i=0;i<n;i++){
			if(non_mst[i]==false && costs[i]<tmp2){
				tmp2 =  costs[i];
				tmp=i;

			}
		}

		simMinCost += costs[tmp];

		non_mst[tmp]=true;

		vector<edge*>::iterator it;
		adjnode* vertextNode = a->nodeList[tmp];
		for(it=vertextNode->adjEdges.begin();it!=vertextNode->adjEdges.end();it++){

				if(	(non_mst[(*it)->dst->data]==false) ){
					if(((*it)->cost<costs[(*it)->dst->data])){
						mst[(*it)->dst->data]=tmp;
						costs[(*it)->dst->data]=(*it)->cost;

					}

			}

		}


	}

//	for(int i=0;i<n;i++)fibmincost+=costs[i];
//	 for(int i=1;i<n;i++)
//		    {
//		        cout<<mst[i]<<" - "<<i;
//		        cout<<endl;
//		    }
//	cout<< "Min Cost "<< fibmincost<<endl;
	cout<< "Simple Total Cost "<< simMinCost<<endl;


}

//edge* prim::getMinEdge(std::vector<adjnode*> nodeL){
//	if(nodeL.size()!=0){
//		int min=INT_MAX;
//		edge* result;
//		int i=0;
//		for(std::vector<adjnode*>::iterator it=nodeL.begin();
//				it!=nodeL.end();++it,++i){
//			(*it)->visited=true;
//			if((*it)->adjEdges.size()!=0){
//				int minEdgeIndex=0;
//				std::vector<edge*>::iterator edgeIt;
//				int j=0;
//				for(edgeIt=(*it)->adjEdges.begin();
//						edgeIt!=(*it)->adjEdges.end();++edgeIt,++j){
//					if((min > (*edgeIt)->cost) && isMinValid(*edgeIt)){
//						min=(*edgeIt)->cost;
//						minEdgeIndex=j;
//						result=(*edgeIt);
//						// (*edgeIt)->covered=true;
//					}
//				}
////				(*it)->adjEdges.erase((*it)->adjEdges.begin()+minEdgeIndex);
//			}
//		}
//		return result;
//	}
//	return NULL;
//}


void prim::FibHeapPrimMst(graph* g){
	int n=g->numberOfNodes;
	bool non_mst[n];
	int mst[n];
	int costs[n];

	for(int i=0;i<n;i++){
		costs[i]=INT_MAX;
		non_mst[i]=false;
	}

   fHeap* heap =new fHeap;


	costs[0]=0;
	heap->insert(0,0);
	int fibmincost=0;

	mst[0]=-1;
//	totalMinCost=0;
	for(int i=0;i<n;i++){

//		cout<<1<<endl;


		int tmp=heap->extract_min();
		if(tmp==-1){
			break;

		}

		while(non_mst[tmp] ){
			tmp=heap->extract_min();
			if(tmp==-1){
				break;

			}
		}

		fibmincost += costs[tmp];

		non_mst[tmp]=true;

		vector<edge*>::iterator it;
		adjnode* vertextNode = g->nodeList[tmp];
		for(it=vertextNode->adjEdges.begin();it!=vertextNode->adjEdges.end();it++){
			if((!(*it)->covered)){
				if(	(non_mst[(*it)->dst->data]==false) ){
					if(((*it)->cost<costs[(*it)->dst->data])){
						mst[(*it)->dst->data]=tmp;
						costs[(*it)->dst->data]=(*it)->cost;
						(*it)->covered=true;

						heap->insert((*it)->dst->data,(*it)->cost);
					}
				}
			}

		}


	}

//	 for(int i=1;i<n;i++)
//		    {
//		        cout<<mst[i]<<" - "<<i;
//		        cout<<endl;
//		    }
//	cout<< "Min Cost "<< fibmincost<<endl;
	cout<< "Fibonacci Total Cost "<< fibmincost<<endl;
//	printSimpleSchemeMst(mst);


}

bool prim::isMinValid(edge* e){
	bool b1=false;
	bool b2=false;
	for(std::vector<adjnode*>::iterator it=nl.begin();
			it!=nl.end();++it){
		if((*it)->data == e->src->data){
			b1=true;
		} 
		if((*it)->data == e->dst->data){
			b2=true;
		} 
	}	
	return !(b1 && b2);
}
