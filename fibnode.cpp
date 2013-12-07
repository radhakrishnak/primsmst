#include "fibnode.h"
#include <cstdlib>
#ifndef NULL
#define NULL   ((void *) 0)
#endif
using namespace std;

void nodeSwap(FNODE& a, FNODE& b) {
	FNODE c = a;
	a = b;
	b = c;
}

fNode::fNode( int x, int k )
: x(x), key(k),
  p(NULL), childNode(NULL),
  leftNode(this), rightNode(this),
  markNode(false), degree(0)
{}

fNode::~fNode() {
	if(p) p->childNode = NULL;
	if(rightNode) this->rightNode->leftNode = NULL;
	if(leftNode && leftNode != this) delete leftNode;
	if(childNode) delete childNode;
}

void fNode::remove() {
	if(p) p->childNode = p->childNode->rightNode;
	this->leftNode->rightNode = this->rightNode;
	this->rightNode->leftNode = this->leftNode;
	this->leftNode = this->rightNode = this;
}

void fNode::insert(fNode *f) {
	f->leftNode = this->leftNode;
	f->rightNode = this;
	this->leftNode->rightNode = f;
	this->leftNode = f;
}

void fNode::addChild(fNode *f) {
	if(childNode)
		childNode->insert(f);
	else
		childNode = f;
	f->p = this;
	f->markNode = false;
	degree++;
}

void fNode::merge(fNode *f) {
	nodeSwap(f->rightNode->leftNode, this->rightNode->leftNode);
	nodeSwap(f->rightNode, this->rightNode);
}
