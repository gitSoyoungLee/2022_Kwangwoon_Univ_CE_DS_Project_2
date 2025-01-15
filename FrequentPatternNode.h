#pragma once

#include <set>
#include <map>
#include <iostream>
using namespace std;

class FrequentPatternNode
{
private:
	int frequency;		// FrequentPattern frequency
	multimap<int, set<string> > FrequentPatternList;	//first is FrequentPattern size, second is FrequentPattern data

public:
	FrequentPatternNode() { frequency = 0; }
	~FrequentPatternNode() { FrequentPatternList.clear(); }
	void setFrequency(int frequency) { this->frequency = frequency; }
	void InsertList(set<string> item) { FrequentPatternList.insert(multimap<int, set<string>>::value_type(item.size(), item)); }
	int getFrequency() { return frequency; }
	multimap<int, set<string> > getList() { return FrequentPatternList; }

	////

	//Does "word" exist in the Frequency Pattern Node and the Frequency is greater than min_freq?
	bool checkWordExists_FPList(string word,int min_freq) {
		for (auto it = FrequentPatternList.begin(); it != FrequentPatternList.end(); it++) {
			if (checkWordExists_Set(it->second, word)) {
				if(this->frequency>=min_freq)
					return true;
			}
		}
		return false;
	}

	//Does "word" exist in the set?
	bool checkWordExists_Set(set<string>Listset,string word) {
		for (auto it = Listset.begin(); it != Listset.end(); it++) {
			if (*it == word) return true;
		}
		return false;
	}

};


