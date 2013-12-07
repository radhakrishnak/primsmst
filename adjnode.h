#ifndef _ADJ_NODE
#define _ADJ_NODE

#include <stdio.h>
#include <iostream>
#include <vector>
class edge;

class adjnode{

    public:
	    int data;
	    bool visited;
	    std::vector<edge*> adjEdges;
	    int parent;
	    adjnode(int);
	    ~adjnode();
};

#endif //_ADJ_NODE
