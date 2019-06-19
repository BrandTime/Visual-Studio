#ifndef  _TESTQUERY_H_
#define  _TESTQUERY_H_
#include"Header.h"
#include"StrVec.hpp"
//#include"StrVec.hpp"
using line_no =size_t;
class TextQuery {
private:
	shared_ptr<StrVec> file;
	map<string, shared_ptr<pair<size_t,set<line_no>>>> wm;
	class QueryResult;
public:
	TextQuery() = delete;
	TextQuery(istream&);
	virtual ~TextQuery();
	QueryResult query(const string&)const;
};

class TextQuery::QueryResult {
	size_t count;
	set<line_no> line;
	shared_ptr<StrVec> lines;
	string sought;
public:
	ostream& print(ostream&)const;
	QueryResult(const string& sough, size_t coun,set<line_no> lin,
		shared_ptr<StrVec> lie) :
		sought(sough),count(coun),line(lin),lines(lie) {};
	set<line_no>::iterator begin();
	set<line_no>::iterator end();
	shared_ptr<StrVec> get_file();
};

void runQuery(istream&);


















shared_ptr<StrVec> TextQuery::QueryResult::get_file() {
	return lines;
}
set<line_no>::iterator TextQuery::QueryResult::end() {
	return line.end();
}
set<line_no>::iterator TextQuery::QueryResult::begin() {
	return line.begin();
}
TextQuery::TextQuery(istream& in) :file(new StrVec) {
	string text;
	while (getline(in, text)) {
		file->push_back(text);
		int n = file->getSize()-1;
		istringstream lin(text);
		string word;
		while (lin >> word) {
			for (auto i = word.begin(); i != word.end(); ) {
				if (isalpha(*i)) {
					*i = toupper(*i);
				}
				else if (!isdigit(*i)) {
					i = word.erase(i);
					continue;
				}
				++i;
			}
			auto &lines = wm[word];
			if (!lines) {
				lines = make_shared<pair<size_t,set<line_no>>>();
				lines->first = 1;
			}
			else {
				lines->first++;
			}
			lines->second.insert(n);
		}
	}
}
TextQuery::~TextQuery() {
	file.reset();
	wm.clear();
}
TextQuery::QueryResult TextQuery::query(const string& str)const {
	static set<line_no> nodata;
	string word = str;
	for (auto& i : word)
		i=toupper(i);
	const auto& loc = wm.find(word);
	if (loc == wm.end())
		return QueryResult(word, loc->second->first, nodata, file);
	else
		return QueryResult(word, loc->second->first, 
			loc->second->second, file);
}
ostream& TextQuery::QueryResult::print(ostream& out)const {
	out << "Word " << sought << " occured " << count << " times:" << endl;
	for (auto i : line) {
		out << "line: " << i+1 << ends << lines->at(i) << endl;
	}
	return out;
}

void runQuery(istream& infile) {
	TextQuery tq(infile);
	while (true) {
		cout << "Enter word to look for, or q to quit: ";
		string s;
		if (!(cin >> s) || s == "q")
			break;
		tq.query(s).print(cout);
	}
}



#if 0
//debugging program
#include"TestQuery.h"

int main() {
	fstream in("output1.txt", ios::in);
	fstream out("output2.txt", ios::out);
	if (!in || !out) {
		cerr << "file open fail" << endl;
	}
	try {
		runQuery(in);
	}
	catch (exception& e) {
		cerr << e.what() << endl;
	}
	in.close();

	system("pause");
	return 0;
}
#endif
#endif // ! _TESTQUERY_H_