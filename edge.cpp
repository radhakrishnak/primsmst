#include "edge.h"

edge::edge(adjnode* s,adjnode* d,int c):src(s),dst(d),cost(c),covered(false){

}

// Destructor
edge::~edge(){

}

// boolean value which tells if n1,n2 are connected
bool edge::isConnected(adjnode* n1,adjnode* n2){
	if(NULL == n1 || NULL == n2) return false;
	bool result = false;
	if(this->src==n1 && this->dst==n2 || 
		this->src==n2 && this->dst==n1)
		result = true;
	return result;
}