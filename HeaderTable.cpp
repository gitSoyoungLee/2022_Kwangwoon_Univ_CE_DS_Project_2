#include "HeaderTable.h"

HeaderTable::~HeaderTable() {
	
}


void HeaderTable::insertTable(char* item, int frequency) {
	///
	for (int i = 0; i < 100; i++) {
		if (item[i] == '\n') item[i] = '\0';
	}
	string item_s(item);	//char* to string
	indexTable.push_back(pair<int, string>(frequency, item_s));	//insert
}

int HeaderTable::find_frequency(string item) {
	int frequency = 0;
	for (auto it = indexTable.begin(); it != indexTable.end(); it++) {
		if (it->second == item) frequency = it->first;
	}
	return frequency;
}

//console print, print for test
void HeaderTable::print_table_console() {
	cout << "========PRINT_ITEMLIST========" << endl;
	cout << "Item\tFrequency" << endl;
	for (auto it = indexTable.begin(); it != indexTable.end(); it++)
		cout << it->first << "  " << it->second << endl;
	cout << "===============================" << endl;
}

//PRINT_ITEMLIST
void HeaderTable::print_table() {
	FILE* table_txt = NULL;
	table_txt = fopen("print_table.txt", "wt");
	fputs("========PRINT_ITEMLIST========\n", table_txt);
	fputs("Item\tFrequency\n", table_txt);
	for (auto it = indexTable.begin(); it != indexTable.end(); it++) {
		fputs((to_string(it->first) + "\t" + it->second+"\n").c_str(), table_txt);
	}
	fputs("===============================\n", table_txt);
	fclose(table_txt);
}

//Create DataTable
void HeaderTable::createDataTable() {
	FPNode* pointer = NULL;
	list<pair<int, string> > ::iterator it;
	for (it = indexTable.begin(); it != indexTable.end(); it++) {
		dataTable.insert(map<string, FPNode*>::value_type(it->second, pointer));
	}
	return;
}

//console print, print for test
void HeaderTable::print_table_threshold_console() {
	for (auto it = indexTable_threshold.begin(); it != indexTable_threshold.end(); it++)
		cout << it->first << "  " << it->second << endl;
}

//descending market.txt before create fp node
list<string> HeaderTable::descendingList_IndexTable(list<string> l) {
	int size = l.size();
	int* num = new int[size];	//find frequency
	for (int i = 0; i < size; i++) {
		num[i] = 1;
	}
	int j = 0;
	for (auto i = l.begin(); i != l.end(); i++) {
		for (auto it = indexTable.begin(); it != indexTable.end(); it++) {
			if (it->second == *i) {
				num[j] = it->first;
				int k = j + 1;
				if (k >= size) j = size - 1;
				else j++;
			}
		}
	}
	string temp; int num_temp;
	list<string>::iterator iter_1 = l.begin();
	list<string>::iterator iter_2 = l.begin();
	iter_2++;
	for (int j = 0; j < 100; j++) {
		for (int i = 1; i < size; i++) {	//sort descending
			int before = num[i - 1]; int after = num[i];
			if (before < after) { //swap
				temp = *iter_2;
				*iter_2 = *iter_1;
				*iter_1 = temp;
				num_temp = num[i-1]; num[i-1] = num[i]; num[i] = num_temp;
			}
			if (i != size) {
				iter_1++;
				iter_2++;
			}
		}
		iter_1 = l.begin();
		iter_2 = l.begin(); iter_2++;
	}
	return l;
}

void HeaderTable::setDataTableNode(string item, FPNode* node) {
	dataTable.find(item)->second = node;
}

void HeaderTable::setDataTableNext(string item, FPNode* node) {
	FPNode* currNode = dataTable.find(item)->second;
	if (currNode == NULL) {
		dataTable.find(item)->second = node;
		return;
	}
	while (currNode->getNext()!=NULL) {
		currNode = currNode->getNext();
	}
	currNode->setNext(node);
}