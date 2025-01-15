#pragma once
#include <cstring>
#include <string>
#include <map>
#include <cmath>
#include <iostream>
using namespace std;

class FPNode
{
private:
	int frequency;
	FPNode* parent;
	FPNode* next;
	map<string, FPNode*> children;
	//////
	
public:
	FPNode();
	~FPNode();
	void setParent(FPNode* node) { this->parent = node; }
	void setNext(FPNode* node) { next = node; }
	void pushchildren(string item, FPNode* node) { children.insert(map<string, FPNode*>::value_type(item, node)); }
	void updateFrequency(int frequency) { this->frequency += frequency; }

	int getFrequency() { return frequency; }
	FPNode* getParent() { return parent; }
	FPNode* getNext() { return next; }
	FPNode* getChildrenNode(string item);
	map<string, FPNode*> getChildren() { return children; }


	//////
	bool CheckExist(string item, FPNode* parent) {
		if (parent->children.find(item)->first == "\0") return false;
		else return true;
	}

	//PRINT FPTREE
	void printPathToRoot(FILE*file, FPNode* node) {
		FPNode* currNode = node;
		while (currNode->parent != NULL) {
			fputs("(", file);
			fputs((currNode->children.begin()->first).c_str(), file);
			fputs(", ", file);
			string freq = to_string(currNode->frequency);
			fputs(freq.c_str(), file);
			fputs(") ", file);
			currNode = currNode->parent;
		}
		fputs("\n", file);
	}

	//Modify children->second:NULL to newNode
	void exchangeFPNode(FPNode* parentNode, FPNode* newNode) {
		parentNode->children.begin()->second = newNode;
	}

	FPNode* CheckChildExists(FPNode* parentNode, string item) {
		map<string, FPNode*>m = parentNode->getChildren();
		for (auto it = m.begin(); it != m.end(); it++) {
			FPNode* currNode = it->second;
			map<string, FPNode*> currM = currNode->getChildren();
			if (currM.begin()->first == item) return currNode;
		}
		return NULL;
	}



};


