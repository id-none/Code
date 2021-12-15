//tesr.cpp
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdlib>

using namespace std;

string miwen = "";
string PinLv = "ETAOINRSHDCLMPUFGWYBKJVXQZ";
string mingwen = "";

void swap(char a, char b) {
	for (int i = 0; i < mingwen.size(); ++i) {
		if (mingwen[i] == a)
			mingwen[i] = '#';
		if (mingwen[i] == b)
			mingwen[i] = a;
	}
	for (int i = 0; i < mingwen.size(); ++i) {
		if (mingwen[i] == '#')
			mingwen[i] = b;
	}
}

int main() {
	ifstream iFile(".//ciphertext.txt", ios::binary);
	if(!iFile){
		cerr << "ERROR:ifstream open fail!" << endl; 
		exit(1);
	}
	else{
		string s;
		while(getline(iFile,s)) { miwen += (s+'\n');}
		iFile.close();
	}

	map<char, int, greater<char>> TongJi1 = {};
	map<char, int, greater<char>>::iterator iter;
	vector<pair<char, int>> TongJi2 = {};
	map<char, char> duiZhaoBiao = {};

	for (int i = 0; i < miwen.size(); ++i) {
		if (miwen[i] == '\n' || miwen[i] == '\t' || miwen[i] == ' ')
			continue;
		iter = TongJi1.find(miwen[i]);
		if (iter != TongJi1.end()) {
			++TongJi1[miwen[i]];
		}
		else {
			TongJi1[miwen[i]] = 1;
		}
	}
	for (iter = TongJi1.begin(); iter != TongJi1.end(); ++iter) {
		TongJi2.push_back(pair<char, int>{iter->first, iter->second});
		//cout << iter->first << '\t' << iter->second << endl;
	}
	sort(TongJi2.begin(), TongJi2.end(), [](pair<char, int>& a, pair<char, int>& b)->bool {return a.second > b.second; });

	// cout << "频率统计：" << endl;
	int i = 0;
	for (auto veciter : TongJi2) {
		// cout << i+1 << '\t' << veciter.first << '\t' << veciter.second << endl;
		duiZhaoBiao[veciter.first] = PinLv[i];
		++i;
	}
	for (auto striter : miwen) {
		if (striter == '\n' || striter == '\t' || striter == ' '){
			mingwen += striter;
			continue;
		}
		mingwen += char(duiZhaoBiao[striter] + 32);
	}
	// cout << "初步解密：" << endl;
	// cout << mingwen << endl << endl;

	ofstream oFile(".//result.out", ios::binary);
	if(!oFile)
	{
		cerr << "ERROR:ofstream open fail!" << endl; 
		exit(1);
	}
	else{
		oFile << "频率统计：" << endl;
		int i = 0;
		for (auto veciter : TongJi2) {
			oFile << i+1 << '\t' << veciter.first << '\t' << veciter.second << endl;
			++i;
		}
		oFile << "解密：" << endl;
		oFile << mingwen;
		oFile.close();
	}

	return 0;
}
