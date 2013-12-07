#ifndef _EDGE
#define _EDGE

#include <stdio.h>
#include <iostream>
#include "adjnode.h"

class edge{
	public:
		adjnode* src;
		adjnode* dst;
		int cost;
		bool covered;
		edge(adjnode* s,adjnode* d,int c);
		~edge();
		bool isConnected(adjnode* n1,adjnode* n2);
};

#endif //_EDGE
