#pragma once
#include "FPGrowth.h"
#include "BpTree.h"
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <sstream>
#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

class Manager
{
private:
	char* cmd;
	FPGrowth* fpgrowth;
	BpTree* bptree;
	//////

public:
	ifstream fin;	//command.txt
	ofstream flog;	//log.txt

	Manager(int threshold, int bpOrder)	//constructor
	{
		/* You must fill here */
		flog.open("log.txt");	
		fpgrowth = new FPGrowth(&flog, threshold);
		bptree = new BpTree(&flog, bpOrder);
		//FPGrowth fpgrowth(&flog, threshold);	//class object construct
		//BpTree bp(&flog, bpOrder);
	}


	~Manager()//destructor
	{
		/* You must fill here */
		flog.close();	//close log.txt
	}


	void run(const char* command);
	bool LOAD();
	bool BTLOAD();

	bool PRINT_ITEMLIST();
	bool PRINT_FPTREE();

	bool PRINT_RANGE(char* item, int start, int end);
	bool PRINT_CONFIDENCE(char* item, double rate);
	bool PRINT_BPTREE(char* item, int min_frequency);


	void printErrorCode(int n);
	void printSuccessCode();

	///////////////////////////////////////////

	void modify_market();

	bool checkExistinVector(vector<pair<int, string>> v, string ch);

	int findElemementinVector(vector<pair<int, string>> v, string ch);
};
