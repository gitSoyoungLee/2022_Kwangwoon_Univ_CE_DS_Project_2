#pragma once
#include "FPNode.h"
#include <list>
#include <string>
#pragma warning(disable : 4996)
class HeaderTable
{
private:
	list<pair<int, string> > indexTable;
	list<pair<int, string> > indexTable_threshold;
	map<string, FPNode*> dataTable;

public:
	HeaderTable() {	}
	~HeaderTable();
	void insertTable(char* item, int frequency);
	list<pair<int, string>> getindexTable() { return indexTable; }
	map<string, FPNode*> getdataTable() { return dataTable; }
	FPNode* getNode(string item) { return dataTable.find(item)->second; }
	void descendingIndexTable() { indexTable.sort(greater<pair<int, string>>()); }
	void ascendingIndexTable() { indexTable.sort(); }
	int find_frequency(string item);
	
	///////////////////////////
	
	void print_table();
	void print_table_console();
	void createDataTable();
	
	list<pair<int, string>>getIndexTable_threshold() { return indexTable_threshold; }

	void createIndexTable_threshold(int threshold) {
		for (auto it = indexTable.begin(); it != indexTable.end(); it++) {
			if (it->first >= threshold) indexTable_threshold.push_back(pair<int, string>(it->first, it->second));	//insert
		}
	}

	//console print, print for test
	void print_table_threshold_console();
	void descendingIndexTable_threshold() { indexTable_threshold.sort(greater<pair<int, string>>()); }

	//descending market.txt before create fp node
	list<string> descendingList_IndexTable(list<string> l);

	void setDataTableNode(string item, FPNode* node);
	void setDataTableNext(string item, FPNode* node);

	void ascendingIndexTable_threshold() { indexTable_threshold.sort(); }
};


