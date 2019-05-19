#include "TestQuery.h"

shared_ptr<StrBlob> TextQuery::QueryResult::get_file() {
	return lines;
}
set<line_no>::iterator TextQuery::QueryResult::end() {
	return line->end();
}
set<line_no>::iterator TextQuery::QueryResult::begin() {
	return line->begin();
}
TextQuery::TextQuery(istream& in) :file(new StrBlob) {
	string text;
	while (getline(in, text)) {
		file->push_back(text);
		int n = file->size() - 1;
		istringstream line(text);
		string word;
		while (line >> word) {
			for (auto& i : word)
				toupper(i);
			auto &lines = wm[word];
			if (!lines) {
				lines.reset(new set<line_no>);
			}
			lines->insert(n);
		}
	}
}
TextQuery::~TextQuery() {
	file.reset();
	wm.clear();
}
TextQuery::QueryResult TextQuery::query(const string& str)const {
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	string word = str;
	for (auto& i : word)
		toupper(i);
	auto loc = wm.find(word);
	if (loc == wm.end())
		return QueryResult(word, nodata,file);
	else
		return QueryResult(word, loc->second,file);
}
ostream& TextQuery::QueryResult::print(ostream& out)const {
	out << "Word " << sought << " occured " << line->size() << " times:" << endl;
	for (auto &i : *line) {
		out << "line: " << i+1 << ends <<lines->at(i) << endl;
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
	if (!in) {
		cerr << "file open fail" << endl;
	}
	runQuery(in);
	in.close();

	system("pause");
	return 0;
}
#endif