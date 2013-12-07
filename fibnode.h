#ifndef FNODE_H
#define FNODE_H

struct fNode {
	int x;
	int key;
	fNode *p, *childNode, *leftNode, *rightNode;
	bool markNode;
	unsigned degree;

	fNode( int x, int k );
	~fNode();
	void insert(fNode *f);
	void remove();
	void addChild(fNode *f);
	void merge(fNode *f);
};
typedef fNode* FNODE;
void nodeSwap(FNODE&, FNODE&);
#endif //  FNODE_H
