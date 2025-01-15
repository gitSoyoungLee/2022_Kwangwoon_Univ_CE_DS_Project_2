#ifndef _BPTREEINDEXNODE_H_
#define _BPTREEINDEXNODE_H_

#include "BpTreeNode.h"
#include <iostream>
using namespace std;

//template <class T>
class BpTreeIndexNode : public BpTreeNode {
private:
	map <int, BpTreeNode*> mapIndex;

public:
	BpTreeIndexNode() {}


	void insertIndexMap(int n, BpTreeNode* pN) {
		mapIndex.insert(map<int, BpTreeNode*>::value_type(n, pN));
	}

	void deleteIndexMap(int n) {
		mapIndex.erase(n);
	}

	map <int, BpTreeNode*>* getIndexMap() { return &mapIndex; }


	///

	int getIndexMapSize() { return mapIndex.size(); }
};

#endif
