#ifndef FHEAP_H
#define FHEAP_H

/*
 * Include files
 */

#include <utility>
#include <cstring>
#include <vector>
#include "fibnode.h"

/*
 * Global variables
 */

class fHeap {

	FNODE minNode; //current min
	int degree; //number of nodes in heap


  std::vector<FNODE> LookUp;
  void link(FNODE, FNODE);


  void consolidate();
  void CascadingCut(FNODE);
  void cut(FNODE, FNODE);


public:
  fHeap() : minNode(NULL), degree(0) {}
  ~fHeap() {
    if(minNode) delete minNode;
  }
  int extract_min();
  FNODE insert(int, int);
  bool isHeapEmpty() {
	  return NULL == minNode;
  }

};

#endif // FHEAP_H
