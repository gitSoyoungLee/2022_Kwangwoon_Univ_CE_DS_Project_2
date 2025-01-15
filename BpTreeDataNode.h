#ifndef _BpTreeDataNode_H_
#define _BpTreeDataNode_H_

#include "BpTreeNode.h"
#include <iostream>
using namespace std;

class BpTreeDataNode : public BpTreeNode
{
private:
	map <int, FrequentPatternNode*> mapData;
	BpTreeNode* pNext;
	BpTreeNode* pPrev;


public:
	BpTreeDataNode() {
		pNext = NULL;
		pPrev = NULL;
	}

	void setNext(BpTreeNode* pN) { pNext = pN; }
	void setPrev(BpTreeNode* pN) { pPrev = pN; }
	BpTreeNode* getNext() { return pNext; }
	BpTreeNode* getPrev() { return pPrev; }

	void insertDataMap(int n, FrequentPatternNode* pN) {
		mapData.insert(map<int, FrequentPatternNode*>::value_type(n, pN));
	}

	void deleteDataMap(int n) {
		mapData.erase(n);
	}
	map<int, FrequentPatternNode*>* getDataMap() { return &mapData; }

	////

	int getDataMapSize() { return mapData.size(); }

	bool keyExists(int key) {
		if (mapData.find(key) == mapData.end()) return false;	//it doesn't exist
		else return true;	//it exists
	}

	FrequentPatternNode* getFPNode(int key) {
		return mapData.find(key)->second;
	}

	FrequentPatternNode* DataNode_CheckWordInFPNode(string word,int min_freq) {
		for (auto it = this->mapData.begin(); it != mapData.end(); it++) {
			FrequentPatternNode* fpnode = it->second;
			if(fpnode->checkWordExists_FPList(word,min_freq)==true) return fpnode;
		}
		return NULL;
	}

	map<int, FrequentPatternNode*> my_getDataMap() { return mapData; }
};

#endif

