#include "BpTree.h"

bool BpTree::Insert(int key, set<string> input_set) {
	//create FrequentPatternNode
	FrequentPatternNode* newFPNode = new FrequentPatternNode;
	newFPNode->setFrequency(key); newFPNode->InsertList(input_set);

	//create TreeNode
	if (root == NULL) {
		BpTreeDataNode* dataNode = new BpTreeDataNode;
		BpTreeNode* newDataNode = new BpTreeNode;
		newDataNode = dataNode;
		newDataNode->insertDataMap(key, newFPNode);
		//newDataNode->insertDataMap(key, newFPNode);
		root=newDataNode;
		return true;
	}
	else {
		//Find DataNode to insert
		BpTreeNode* currDataNode = root;
		while (currDataNode->getMostLeftChild() != NULL) {
			if (key < currDataNode->getIndexMap()->begin()->first)
				currDataNode = currDataNode->getMostLeftChild();
			else if (key >= currDataNode->getIndexMap()->begin()->first) {
				currDataNode = currDataNode->getIndexMap()->begin()->second;
			}
		}
		
		//insert
		//If the key already exists in the data node, add the FrequencyPatternNode and if not, just insert
		if(currDataNode->keyExists(key)==false)
			currDataNode->insertDataMap(key, newFPNode);
		else {
			FrequentPatternNode* fpnode = currDataNode->getFPNode(key);
			fpnode->InsertList(input_set);
			currDataNode->deleteDataMap(key);
			currDataNode->insertDataMap(key, fpnode);

		}
		//#childern>=order?
		if (excessDataNode(currDataNode) == true) {
			//split data node
			splitDataNode(currDataNode);
			//split index node
			BpTreeNode* currNode = currDataNode->getParent();
			while (currNode) {
				if (excessIndexNode(currNode) == true) {
					splitIndexNode(currNode);
				}
				currNode = currNode->getParent();
			}
		}
		
	}
	return true;
}


void BpTree::splitDataNode(BpTreeNode* pDataNode) {
	if (pDataNode->getDataMap()->size() >= order) {
		//create new data node
		int idx = 0;	//"idx"th element
		if (order % 2 == 0) idx = order / 2;
		else if (order % 2 != 0) idx = (order + 1) / 2;
		map <int, FrequentPatternNode*> DataMap= *pDataNode->getDataMap();
		map <int, FrequentPatternNode*> DataMap_bidx; //Data Map before m[idx]
		for (auto it = DataMap.begin(); it->second != DataMap[idx];it++)
			DataMap_bidx[it->first] = it->second;
		for (auto it = DataMap_bidx.begin(); it!=DataMap_bidx.end(); it++)
			pDataNode->deleteDataMap(it->first);
		BpTreeDataNode* datanode = new BpTreeDataNode;
		BpTreeNode* newDataNode = new BpTreeNode;
		newDataNode = datanode;
		for (auto it = DataMap_bidx.begin(); it != DataMap_bidx.end(); it++)
			newDataNode->insertDataMap(it->first, it->second);
		newDataNode->setNext(pDataNode);
		pDataNode->setPrev(newDataNode);

		//create new index node
		if (pDataNode->getParent() == NULL) {
			BpTreeIndexNode* newIndexNode_2 = new BpTreeIndexNode;
			BpTreeNode* newIndexNode = new BpTreeNode;
			newIndexNode_2->insertIndexMap(DataMap.begin()->first,pDataNode);
			newDataNode->setParent(newIndexNode_2); pDataNode->setParent(newIndexNode_2);
			newIndexNode_2->setMostLeftChild(newDataNode);
			newIndexNode = newIndexNode_2;
			root = newIndexNode;
			return;
		}
		else if (pDataNode->getParent() != NULL) {
			BpTreeNode* prevNode = pDataNode->getPrev();
			newDataNode->setParent(pDataNode->getParent());
			newDataNode->setPrev(prevNode);		prevNode->setNext(newDataNode);
			newDataNode->setNext(pDataNode);	pDataNode->setPrev(newDataNode);
		}
	}
	return;
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {
	if (pIndexNode->getIndexMap()->size() >= order) {
		int idx = 0;	//"idx"th element
		if (order % 2 == 0) idx = order / 2;
		else if (order % 2 != 0) idx = (order + 1) / 2;
		map <int, BpTreeNode*> IndexMap = *pIndexNode->getIndexMap();
		map <int, BpTreeNode*> IndexMap_bidx; //Data Map before m[idx]
		for (auto it = IndexMap.begin(); it->second != IndexMap[idx]; it++)
			IndexMap_bidx[it->first] = it->second;
		for (auto it = IndexMap_bidx.begin(); it != IndexMap_bidx.end(); it++)
			pIndexNode->deleteIndexMap(it->first);
		BpTreeNode* leftIndexNode = new BpTreeNode;
		for (auto it = IndexMap_bidx.begin(); it != IndexMap_bidx.end(); it++)
			leftIndexNode->insertIndexMap(it->first, it->second);
		
		BpTreeNode* newLeftChild = NULL;
		map <int, BpTreeNode*>::iterator it = IndexMap.begin();
		for (int i = 0; i < idx - 1; i++)
			it++;
		newLeftChild = it->second;


		//create new index node
		if (pIndexNode->getParent() == NULL) {
			BpTreeNode* newIndexNode = new BpTreeNode;
			newIndexNode->insertIndexMap(it->first,pIndexNode);
			leftIndexNode->setParent(newIndexNode); pIndexNode->setParent(newIndexNode);
			newIndexNode->setMostLeftChild(leftIndexNode);
			root = newIndexNode;
		}
		else if (pIndexNode->getParent() != NULL) {
			BpTreeNode* parentNode = pIndexNode->getParent();
			parentNode->insertIndexMap(it->first,pIndexNode);
			parentNode->setMostLeftChild(leftIndexNode);
		}

	}
	return;
}

bool BpTree::excessDataNode(BpTreeNode* pDataNode) {
	int size = pDataNode->getDataMapSize();	
	if (size > order - 1) return true;//order is equal to the number of elements 
	else return false;
}

bool BpTree::excessIndexNode(BpTreeNode* pIndexNode) {
	int size = pIndexNode->getIndexMapSize();
	if (size > order - 1)return true;//order is equal to the number of elements 
	else return false;
}


bool BpTree::printConfidence(string item, double item_frequency, double min_confidence)
{
	int count = 0;
	double min_freq = item_frequency * min_confidence;
	double currConfidence;
	*fout << "========PRINT_CONFIDENCE========\n";
	*fout << "FrequentPattern Frequency Confidence\n";
	//move to first DataNode
	BpTreeNode* currNode = root;
	while (currNode->getMostLeftChild())
		currNode = currNode->getMostLeftChild();
	//search and print
	while (currNode) {
		map <int, FrequentPatternNode*> DataMap = currNode->my_getDataMap();
		for (auto DataMap_it = DataMap.begin(); DataMap_it != DataMap.end(); DataMap_it++) {
			multimap<int, set<string> >List = DataMap_it->second->getList();
			int currFreq = DataMap_it->second->getFrequency();
			currConfidence = currFreq / item_frequency;
			currConfidence = ceil(currConfidence * 100) / 100;
			for (auto List_it = List.begin(); List_it != List.end(); List_it++) {
				if (CheckExistsInSet(List_it->second, item) == true && currConfidence >= min_confidence) {
					printFrequentPatterns(List_it->second); *fout << currFreq << " "<<currConfidence<<"\n";
					count++;
				}
			}
		}
		currNode = currNode->getNext();
	}


	if (count == 0)
		*fout << "ERROR 600\n";
	*fout << "==========================\n\n";
	return true;
}

//PRINT_BPTREE
bool BpTree::printFrequency(string item, int min_frequency)//print winratio in ascending order
{
	int count = 0;
	*fout << "========PRINT_BPTREE========\n";
	*fout << "FrequentPattern Frequency\n";
	//move to first DataNode
	BpTreeNode* currNode = root;
	while (currNode->getMostLeftChild())
		currNode = currNode->getMostLeftChild();
	//search and print
	while (currNode) {
		map <int, FrequentPatternNode*> DataMap = currNode->my_getDataMap();
		for (auto DataMap_it = DataMap.begin(); DataMap_it != DataMap.end(); DataMap_it++) {
			multimap<int, set<string> >List = DataMap_it->second->getList();
			int currFreq = DataMap_it->second->getFrequency();
			for (auto List_it = List.begin(); List_it != List.end(); List_it++) {
				if (CheckExistsInSet(List_it->second, item) == true && currFreq >= min_frequency) {
					printFrequentPatterns(List_it->second); *fout << currFreq << "\n"; count++;
				}
			}
		}
		currNode = currNode->getNext();
	}
	if (count == 0) {
		*fout << "ERROR 500\n";
	}
	*fout << "==========================\n\n";

	return true;
}



bool BpTree::printRange(string item, int min, int max) {
	
	int count = 0;
	*fout << "========PRINT_RANGE========\n";
	*fout << "FrequentPattern Frequency\n";
	//move to first DataNode
	BpTreeNode* currNode = root;
	while (currNode->getMostLeftChild())
		currNode = currNode->getMostLeftChild();
	//search and print
	while (currNode) {
		map <int, FrequentPatternNode*> DataMap = currNode->my_getDataMap();
		for (auto DataMap_it = DataMap.begin(); DataMap_it != DataMap.end(); DataMap_it++) {
			multimap<int, set<string> >List = DataMap_it->second->getList();
			int currFreq = DataMap_it->second->getFrequency();
			for (auto List_it = List.begin(); List_it != List.end(); List_it++) {
				if (CheckExistsInSet(List_it->second, item) == true && currFreq >= min && currFreq<=max) {
					printFrequentPatterns(List_it->second); *fout << currFreq << "\n"; count++;
				}
			}
		}
		currNode = currNode->getNext();
	}
	if (count == 0) {
		*fout << "ERROR 700\n";
	}
	*fout << "==========================\n\n";

	return true;
}

void BpTree::printFrequentPatterns(set<string> pFrequentPattern) {
	*fout << "{";
	set<string> curPattern = pFrequentPattern;
	for (set<string>::iterator it = curPattern.begin(); it != curPattern.end();) {
		string temp = *it++;
		*fout << temp;
		if (it == curPattern.end()) {
			*fout << "} ";
			break;
		}
		*fout << ", ";
	}
}
