#include "fibheap.h"
#include <iostream>
#include <cmath>
using namespace std;

/**
* Insert a new node into the heap
*
*  int x the node data
*  int k the node associated key
*
*/

FNODE fHeap::insert(int x, int k) {
  if ( LookUp.size() <= k ) {
    LookUp.resize(k+1, NULL);
  } else {
    if (NULL != LookUp[k]) {
//    	cout<<"Duplicate Keys"<<endl;
    }
  }
  FNODE ptr = new fNode(x,k);
  if (minNode) {
    minNode->insert(ptr);
    if(k < minNode->key) {
      minNode = ptr;
    }
  } else {
    minNode = ptr;
  }
  LookUp[k] = ptr;
  degree++;
  return ptr;
}

/**
* Extract the node of minimum key
*
* returns {int} data
*/
int fHeap::extract_min() {
  if(this->isHeapEmpty()) {
	  return -1;
  }
  int data = minNode->x;
  int key = minNode->key;

  if (minNode->childNode) {
    FNODE ptr = minNode->childNode;
    do {
      ptr->p = NULL;
      ptr = ptr->leftNode;
    } while (ptr != minNode->childNode);
    minNode->childNode = NULL;
    minNode->merge(ptr);
  }

  FNODE ptr = minNode;
  LookUp[key] = NULL;

  if(minNode->rightNode == minNode) {
    //If there is only one node left inside the heap
    delete minNode;
    minNode = NULL;
  } else {
    //We isolate the (current) fmin, then delete it
    minNode = minNode->rightNode;
    ptr->remove();
    delete ptr;
    this->consolidate();
  }
  degree--;
  return data;
}

/**
* Consolidate the root node chain
*/
void fHeap::consolidate() {
  //+1 for ceiling log_2, +1 for null terminated
  const std::size_t sz = log2(this->degree) + 2;
  FNODE A[sz];
  memset(A, 0x0, sz * sizeof(FNODE));
  FNODE w = minNode->rightNode;
  bool finished = false;
  do {
    if(w == minNode) finished = true;
    FNODE x = w;
    w = w->rightNode;
    unsigned d = x->degree;
    while ( A[d] ) {
      FNODE y = A[d];
      if ( x->key > y->key ) { swap(x,y); }
      this->link(y,x);
      A[d] = NULL;
      d++;
    }
    A[d] = x;
  }while(!finished);

  minNode = NULL;
  for (std::size_t i = 0; i < sz; i++) {
    if (A[i]) {
      if(NULL == minNode) {
        minNode = A[i];
        minNode->leftNode = minNode;
        minNode->rightNode = minNode;
      } else {
        minNode->insert(A[i]);
        if ( A[i]->key < minNode->key )
          minNode = A[i];
      }
    }
  }
}

/**
* Link the y node into x's child node chain
*
*  y the new child node to link
*  x the parent node
*/
void fHeap::link(FNODE y, FNODE x) {
  if( !x || !y ) return;
  y->remove();
  x->addChild(y);
}

/**
* Move a node x from y's child node chain to the root chain
*
*  x the node to move
*  y the parent node
*/
void fHeap::cut(FNODE x, FNODE y) {
  x->remove();
  y->degree--;
  minNode->insert(x);
  x->p = NULL;
  x->markNode = false;
}

void fHeap::CascadingCut(FNODE y) {
  FNODE z = y->p;
  if (z) {
    if (y->markNode) {
      cut(y,z);
      CascadingCut(z);
    } else {
      y->markNode = true;
    }
  }
}
