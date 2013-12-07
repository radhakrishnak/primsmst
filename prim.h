#ifndef _PRIM
#define _PRIM

#include "graph.h"
#include <set>
#include "fibheap.h"
#include "fibnode.h"
using namespace std;

class prim
{
public:
	int minCost;
	bool noOfNodes;
//	bool check[];
	fHeap f;
//	FibonacciHeap fHP;
	std::vector<edge*> finalSet;
	std::vector<edge*> finalSetFib;
	std::vector<adjnode*> nl;
	std::vector<adjnode*> nlfib;
	prim();
	~prim();
	void primsGraph(graph* g,const char* s);
	std::vector<edge*> findMinimum(graph* g);
//	std::vector<edge*> findMinimumFib(graph* g);
	edge* getMinEdge(std::vector<adjnode*> nodeL);
//	edge* getMinEdgeFib(adjnode* nodeL,int costs[],bool check[]);
	std::vector<edge*> findMinimum1(graph* g);
	void FibHeapPrimMst(graph* g);
	bool isMinValid(edge* e);
	bool isMinValidFib(edge* e);
	void removeEdgeFromDst(edge* e);
	void generateSimple(graph* a);
};


#endif //_PRIM
