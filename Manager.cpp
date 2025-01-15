#include "Manager.h"

void Manager::run(const char* command)
{	

	fin.open(command);
	if (!fin)
	{
		flog << "==========NO COMMAND==========" << endl;
		return;
	}
	char cmd[1000];
	while (!fin.eof())
	{
		/* You must fill here */
		fin.getline(cmd,sizeof(cmd));
		//LOAD
		if (cmd[0] == 'L' && cmd[1] == 'O' && cmd[2] == 'A' && cmd[3] == 'D')
		{
			//create header table
			FILE* market_txt = fopen("market.txt", "r");
			if (market_txt == NULL) {
				flog << "==========LOAD==========" << endl;
				printErrorCode(100);
			}
			fclose(market_txt);

			modify_market();
			vector<pair<int, string>> v;
			FILE* modified_market = fopen("modified_market.txt", "r");
			char item_c[100];
			while (!feof(modified_market)) {
				fgets(item_c, sizeof(item_c), modified_market);
				string item(item_c);
				if (checkExistinVector(v, item) == true) {
					int n = findElemementinVector(v, item);
					v[n].first = v[n].first + 1;
				}
				else v.push_back(pair<int, string>(1, item));
			}
			//print for test
			//for (int i = 0; i < v.size(); i++) {
			//	cout << v[i].first << "\t" << v[i].second << endl;
			//}
			for (int i = 0; i < v.size(); i++) {
				const char* c = v[i].second.c_str();
				fpgrowth->createTable((char*)c,v[i].first);
			}
			fclose(modified_market);
			fpgrowth->createIndexTable_threshold();
			//print for test
			//fpgrowth->print_indexTable_threshold();

			//create fp tree
			list <string> l;
			FILE* market = fopen("market.txt", "r");
			char buffer[200];
			while (!feof(market)) {
				fgets(buffer, sizeof(buffer), market);
				//if (buffer == "\0" || buffer == "\t" || buffer == "\n") break;
				char* ptr = strtok(buffer, "\t");
				while (ptr != NULL) {
					for (int i = 0; i < 200; i++) {
						if (ptr[i] == '\n') ptr[i] = '\0';
					}
					//print for test
					//cout << ptr << "!!!\n";
					string s = ptr;	//char* to string
					l.push_back(s); //list insert
					ptr = strtok(NULL, "\t");
				}
				//cout << "-------\n";
				//descending
				l = fpgrowth->descendingList_IndexTable(l);
				//print for test
				//for (auto it = l.begin(); it != l.end(); it++)
				//	cout << *it << endl;
				//cout << "---\n";

				//insert tree node
				fpgrowth->createDataTable();	//create Data Table
				FPNode* root = fpgrowth->createRoot();
				HeaderTable* table = fpgrowth->getHeaderTable();
				int freq = 1;
				fpgrowth->createFPtree(root,table,l,freq);
				l.clear();	//initailize list
			}
			fclose(market);
			flog << "=========LOAD==========" << endl;
			printSuccessCode();
			
		}
		//BTLOAD
		else if (cmd[0] == 'B' && cmd[1] == 'T' && cmd[2] == 'L' && cmd[3] == 'O' && cmd[4] == 'A' && cmd[5] == 'D')
		{
			FILE* result_txt = fopen("result.txt", "r");
			if (result_txt == NULL) {
				flog << "==========BTLOAD=========" << endl;
				printErrorCode(200);
			}
			else {
				set <string> s;
				char buffer[100];
				while (!feof(result_txt)) {
					fgets(buffer, sizeof(buffer), result_txt);
					char* ptr = strtok(buffer, "\t");
					int count = 0;	//element's number
					int freq;	//Frequency
					while (ptr != NULL) {
						for (int i = 0; i < 200; i++) {
							if (ptr[i] == '\n') ptr[i] = '\0';
						}
						string str;
						str = ptr;	//char* to string
						if (count == 0) freq = stoi(str);
						else s.insert(str); //list insert
						count++;
						ptr = strtok(NULL, "\t");
					}
					if (count >= 3) bptree->Insert(freq, s);
					s.clear();
				}



				flog << "========BTLOAD=========" << endl;
				printSuccessCode();
			}

		}
		//PRINT
		else if (cmd[0] == 'P' && cmd[1] == 'R' && cmd[2] == 'I' && cmd[3] == 'N' && cmd[4] == 'T' && cmd[5] == '_') {
			//PRINT_ITEMLIST
			if (cmd[6] == 'I' && cmd[7] == 'T' && cmd[8] == 'E' && cmd[9] == 'M')
			{
				if (fpgrowth->printList() == true) {
					fpgrowth->Table_Descending();
					//print for test
					//fpgrowth->Print_ItemList_console();
					fpgrowth->Print_ItemList();
				}
				else {
					flog << "========PRINT_ITEMLIST========\n";
					printErrorCode(300);
				}
			}
			//PRINT_FPTREE
			else if (cmd[6] == 'F' && cmd[7] == 'P' && cmd[8] == 'T' && cmd[9] == 'R' && cmd[10] == 'E' && cmd[11] == 'E')
			{
				fpgrowth->printFPTree();
			}
			//PRINT_BPTREE
			else if (cmd[6] == 'B' && cmd[7] == 'P' && cmd[8] == 'T' && cmd[9] == 'R' && cmd[10] == 'E' && cmd[11] == 'E')
			{
				string word; int min_freq; string min_freq_str;
				int i = 13;
				while (cmd[i] != '\t') {
					word += cmd[i];
					i++;
				}
				i++;
				while (cmd[i] != '\n' && cmd[i] != '\0') {
					min_freq_str += cmd[i];
					i++;
				}
				min_freq = stoi(min_freq_str);
				//print for test
				//cout << word << " " << min_freq <<"\n";
				//print
				if (bptree->treeExist()) bptree->printFrequency(word, min_freq);
				else {
					flog << "========PRINT_BPTREE========" << endl;
					printErrorCode(500);
				}
			}
			//PRINT_CONFIDENCE
			else if (cmd[6] == 'C' && cmd[7] == 'O' && cmd[8] == 'N' && cmd[9] == 'F' && cmd[10] == 'I' && cmd[11] == 'D' && cmd[12] == 'E' && cmd[13] == 'N' && cmd[14] == 'C' && cmd[15] == 'E')
			{
				string word; double min_confidence; string min_confidence_str;
				int i = 17;
				while (cmd[i] != '\t') {
					word += cmd[i];
					i++;
				}
				i++;
				while (cmd[i] != '\n' && cmd[i] != '\0') {
					min_confidence_str += cmd[i];
					i++;
				}
				stringstream Double(min_confidence_str);
				Double >> min_confidence;
				//print

				double frequency = fpgrowth->find_frequency(word);
				if (bptree->treeExist()) bptree->printConfidence(word, frequency, min_confidence);
				else {
					flog << "========PRINT_CONFIDENCE========" << endl;
					printErrorCode(600);
				}

			}
			//PRINT_RANGE
			else if (cmd[6] == 'R' && cmd[7] == 'A' && cmd[8] == 'N' && cmd[9] == 'G' && cmd[10] == 'E')
			{
				string word; int min_freq; string min_freq_str;
				int max_freq; string max_freq_str;
				int i = 12;
				while (cmd[i] != '\t') {
					word += cmd[i];
					i++;
				}
				i++;
				while (cmd[i] != '\t') {
					min_freq_str += cmd[i];
					i++;
				}
				i++;
				min_freq = stoi(min_freq_str);
				while (cmd[i] != '\n' && cmd[i] != '\0') {
					max_freq_str += cmd[i];
					i++;
				}
				max_freq = stoi(max_freq_str);
				//cout << word << " " << min_freq << " " << max_freq << "\n";
				//print
				if (bptree->treeExist()) bptree->printRange(word, min_freq, max_freq);
				else {
					flog << "========PRINT_RANGE========" << endl;
					printErrorCode(700);
				}
			}
		}
		//EXIT
		else if (cmd[0] == 'E' && cmd[1] == 'X' && cmd[2] == 'I' && cmd[3] == 'T') {
			flog << "==========EXIT==========" << endl;
			printSuccessCode();
			break;
		}
	}

		fin.close();
		return;
}


bool Manager::LOAD()
{
	return true;
}




bool Manager::BTLOAD()
{
		return true;
}

bool Manager::PRINT_ITEMLIST() {
	return true;
}

bool Manager::PRINT_FPTREE() {
	return true;
}

bool Manager::PRINT_BPTREE(char* item, int min_frequency) {
	return true;
}

bool Manager::PRINT_CONFIDENCE(char* item, double rate) {
	return true;
}

bool Manager::PRINT_RANGE(char* item, int start, int end) {
	return true;
}

void Manager::printErrorCode(int n) {				//ERROR CODE PRINT
		flog << " << n << " << endl;
		flog << "=======================" << endl << endl;
}

void Manager::printSuccessCode() {//SUCCESS CODE PRINT 
	flog << "Success" << endl;
	flog << "=======================" << endl << endl;

}


/// ////////////////////////////////////////////


void Manager::modify_market() {
	//change "/t" to "/n"
	ifstream market;
	ofstream modified_market;
	char c;
	market.open("market.txt");
	modified_market.open("modified_market.txt");
	if (market.is_open()) {
		while (market.get(c)) {
			if (c == '\t') modified_market << '\n';
			else modified_market << c;
		}
	}
	market.close();
	modified_market.close();
}

bool Manager::checkExistinVector(vector<pair<int, string>> v, string ch) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i].second == ch) return true;	//it already exists
	}
	return false;//it doesn't exist
}

int Manager::findElemementinVector(vector<pair<int, string>> v, string ch) {
	int n = 0;
	for (int i = 0; i < v.size(); i++) {
		if (v[i].second == ch) n = i;	//found element
	}
	return n;
}
