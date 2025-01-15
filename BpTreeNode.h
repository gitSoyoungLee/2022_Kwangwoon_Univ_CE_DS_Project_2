#pragma once
#include "FrequentPatternNode.h"
#include "FPNode.h"
#include <iostream>
using namespace std;

class BpTreeNode
{
private:
	BpTreeNode* pParent;	//parent node
	BpTreeNode* pMostLeftChild;	//most left node of child nodes

public:
	BpTreeNode() {
		pParent = NULL;
		pMostLeftChild = NULL;
	}
	~BpTreeNode() {

	}

	void setMostLeftChild(BpTreeNode* pN) { pMostLeftChild = pN; }
	void setParent(BpTreeNode* pN) { pParent = pN; }

	BpTreeNode* getParent() { return pParent; }
	BpTreeNode* getMostLeftChild() { return pMostLeftChild; }

	virtual void setNext(BpTreeNode* pN) {
	
	}
	virtual void setPrev(BpTreeNode* pN) {
	
	}
	virtual BpTreeNode* getNext() { return NULL; }
	virtual BpTreeNode* getPrev() { return NULL; }

	virtual void insertDataMap(int n, FrequentPatternNode* pN) {}
	virtual void insertIndexMap(int n, BpTreeNode* pN) {}
	virtual void deleteDataMap(int n) {}
	virtual void deleteIndexMap(int n) {}

	virtual map<int, BpTreeNode*>* getIndexMap() { return {}; }
	virtual map<int, FrequentPatternNode*>* getDataMap() { return {}; }

	////

	virtual int getDataMapSize() { return NULL; }

	virtual int getIndexMapSize() { return NULL; }

	virtual bool keyExists(int key) { return NULL; }

	virtual FrequentPatternNode* getFPNode(int key) { return NULL; }

	virtual FrequentPatternNode* DataNode_CheckWordInFPNode(string word) { return NULL; }

	virtual map<int, FrequentPatternNode*> my_getDataMap() { return {}; }
};
