#include<iostream>
#include<set>
#include<vector>
#include<map>
#include<fstream>
#include<algorithm>
using namespace std;


void preload(map<vector<char>, vector<char>> & ma, set<char>& attrs,fstream& fs) {
	enum State{INATTRS=0,INFDLEFT,INFDRIGHT};
	if (!fs) {
		cout << "no file!" << endl;
		return;
	}
	//DFA for recognizing input
	State state =INATTRS;
	char ch;
	pair<vector<char>, vector<char>> temp;//buff for FD
	while (!fs.fail()) {
		fs >> ch;
		switch (state) {
		case INATTRS:
			if (ch == '$') {
				state = INFDLEFT;
				break;
			}
			else {
				attrs.insert(ch);
				break;
			}
		case INFDLEFT:
			if (ch == '?') {
				state = INFDRIGHT;
				break;
			}
			else {
				temp.first.push_back(ch);
				break;
			}
		case INFDRIGHT:
			if (ch == '#') {
				ma.insert(temp);
				state = INFDLEFT;
				temp.first.clear();
				temp.second.clear();
				break;
			}
			else {
				temp.second.push_back(ch);
				break;
			}
		default:
			cerr << "error" << endl;
		}
	}
	
	return;
}
bool eaqual(char a, vector<char> b) {

	return false;
}
int main() {
	//attrs represents original attributes set, X represents the closure
	set<char> attrs,X;
	//FD--functional dependencies
	map<vector<char>, vector<char>> FD;
	fstream input;
	input.open("input.txt", ios::in);
	if (!input) {
		cerr << "file open fail" << endl;
	}
	preload(FD,attrs,input);

	cout << "Please input the attributes need to process:" << endl;
	char ch;
	while (!cin.fail()) {
		cin >> ch;
		X.insert(ch);
	}

	//compute the closure
	while (true) {
		set<char> temp = {};
		for (auto i : X) {
			vector<char> ivec = { i };
			map<vector<char>, vector<char>>::const_iterator iter =
				FD.find(ivec);
			if (iter!=FD.end()) {
				for (auto j : iter->second) {
					temp.insert(j);
				}
			}
		}
		size_t before = X.size();
		if (temp.size()) {
			for (auto i : temp) {
				if (X.find(i) == X.end()) {
					X.insert(i);
				}
			}
		}
		if (before == X.size()) {
			break;
		}
	}
	for (auto i : X) {
		cout << i << ends;
	}
	cout << endl;

	system("pause");
	return 0;
}