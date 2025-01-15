#ifndef _BpTree_H_
#define _BpTree_H_

#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <list>
#include <map>
#include <cmath>

class BpTree {
private:
	BpTreeNode* root;
	int			order;		// m children
	ofstream* fout;
public:
	BpTree(ofstream* fout, int order = 3) {
		root = NULL;
		this->order = order;
		this->fout = fout;
	}
	~BpTree();
	/* essential */
	bool		Insert(int key, set<string> input_set);
	bool		excessDataNode(BpTreeNode* pDataNode);
	bool		excessIndexNode(BpTreeNode* pIndexNode);
	void splitDataNode(BpTreeNode* pDataNode);
	void		splitIndexNode(BpTreeNode* pIndexNode);
	BpTreeNode* getRoot() { return root; }
	BpTreeNode* searchDataNode(int n);

	void	printFrequentPatterns(set<string> pFrequentPattern);
	bool	printFrequency(string item, int min_frequency);
	bool	printConfidence(string item, double item_frequency, double min_confidence);
	bool 	printRange(string item, int min, int max);

	/////
	bool treeExist() {
		if (root == NULL) return false;
		else return true;
	}

	//Does "word" exist in set?
	bool CheckExistsInSet(set<string> s, string word) {
		set<string>::iterator it;
		for (it = s.begin(); it != s.end(); it++) {
			if (*it == word) return true;	//word exists in s
		}
		return false; //doesn't exist
	}
	

};

#endif
