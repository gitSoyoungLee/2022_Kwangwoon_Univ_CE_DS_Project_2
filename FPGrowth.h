#pragma once
#include "HeaderTable.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <string>
#pragma warning(disable : 4996)
using namespace std;

class FPGrowth
{
private:
	int threshold;
	FPNode* fpTree;
	HeaderTable* table;
	map<set<string>, int> frequenctPatterns;
	ofstream* fout;	//log.txt
	ofstream flog;	//result.txt
public:
	FPGrowth(ofstream* fout, int threshold = 3) {
		this->threshold = threshold;
		flog.open("result.txt", ios::app);
		flog.setf(ios::fixed);
		fpTree = new FPNode;  table = new HeaderTable;
		this->fout = fout;
	}
	~FPGrowth();
	void createTable(char* item, int frequency) { table->insertTable(item, frequency); }
	//void createFPtree(FPNode* root, HeaderTable* table, list<string> item_array, int frequency);
	void connectNode(HeaderTable* table, string item, FPNode* node);


	void frequenctPatternSetting() {
		table->ascendingIndexTable();
		frequenctPatterns = getFrequentPatterns(table, fpTree);
	}

	map<set<string>, int> getFrequentPatterns(HeaderTable* pTable, FPNode* pTree);
	void powerSet(map<set<string>, int>* FrequentPattern, vector<string> data, string item, int frequency, int* flag, int depth);
	bool contains_single_path(FPNode* pNode);
	int item_frequency(string item) { return table->find_frequency(item); }
	FPNode* getTree() { return fpTree; }
	HeaderTable* getHeaderTable() { return table; }

	bool printList() {
		if (table == NULL) return false;
		return true;
	}

	bool printTree();
	void saveFrequentPatterns();

	///////////////////////////////////////////////////
	
	//PRINT_ITEMLIST for test
	void Print_ItemList_console() { table->print_table_console(); }

	//PRINT_ITEMLIST
	void Print_ItemList() {
		table->print_table();
		ifstream table_txt;
		table_txt.open("print_table.txt");
		while (!table_txt.eof()) {
			string line;
			getline(table_txt, line);
			*fout << line << endl;
		}
		table_txt.close();
	}	
	void Table_Descending() { table->descendingIndexTable(); }

	void createIndexTable_threshold() {
		table->createIndexTable_threshold(threshold);
		table->descendingIndexTable_threshold();
	}

	//print index table_threshold for test
	void print_indexTable_threshold() {
		table->print_table_threshold_console();
	}

	//descending market.txt before create fp node
	list<string> descendingList_IndexTable(list<string> l) { return table->descendingList_IndexTable(l); }

	bool CheckExistsNode(string item, FPNode* parent) {
		return fpTree->CheckExist(item, parent);
	}

	void createDataTable() { table->createDataTable(); }

	void createFPtree(FPNode* root, HeaderTable* table, list<string> item_array, int frequency) {
		FPNode* parentNode = root;
		for (auto it = item_array.begin(); it != item_array.end(); it++) {
			FPNode* newNode = new FPNode;
			newNode->setParent(parentNode); newNode->setNext(NULL);
			newNode->updateFrequency(frequency);
			newNode->pushchildren(*it, NULL);

			map<string, FPNode*>child = parentNode->getChildren();
			if (child.begin()->second == NULL) {	//if newNode is parentNode's first child
				parentNode->exchangeFPNode(parentNode, newNode);
				table->setDataTableNext(*it, newNode);
				parentNode = newNode;
			}
			else {
				//If the same node already exists, only the frequency should be updated
				if (parentNode->CheckChildExists(parentNode, *it) !=NULL) {
					parentNode->CheckChildExists(parentNode, *it)->updateFrequency(frequency);
					parentNode = parentNode->CheckChildExists(parentNode, *it);
				}
				else {
					parentNode->pushchildren(*it, newNode);
					table->setDataTableNext(*it, newNode);
					parentNode = newNode;
				}
			}
		}

		return;
	}

	void printFPTree() {
		table->ascendingIndexTable_threshold();
		printFPTree_file();
		ifstream fptree_txt;
		fptree_txt.open("print_fptree.txt");
		while (!fptree_txt.eof()) {
			string line;
			getline(fptree_txt, line);
			*fout << line << endl;
		}
		fptree_txt.close();
	}

	void printFPTree_file() {
		FILE* fptree_txt = NULL;
		fptree_txt = fopen("print_fptree.txt", "wt");
		fputs("========PRINT_FPTREE========\n", fptree_txt);
		fputs("{StandardItem,Frequency} (Path_Item,Frequency)\n", fptree_txt);
		list<pair<int, string>>indextable = table->getIndexTable_threshold();
		for (auto it = indextable.begin(); it != indextable.end(); it++) {
			fputs("{", fptree_txt);
			fputs(it->second.c_str(), fptree_txt);
			fputs(", ", fptree_txt);
			fputs((to_string(it->first)).c_str(), fptree_txt);
			fputs("}\n", fptree_txt);
			FPNode* currNode = table->getNode(it->second);
			while (currNode) {
				currNode->printPathToRoot(fptree_txt, currNode);
				currNode = currNode->getNext();
			}
		}
		fputs("===============================\n", fptree_txt);
		fclose(fptree_txt);
	}

	FPNode* createRoot() {
		FPNode* root = new FPNode;
		root->setNext(NULL); root->setParent(NULL);
		root->pushchildren("\0", NULL);
		return root;
	}

	int find_frequency(string item) {
		return table->find_frequency(item);
	}
};

