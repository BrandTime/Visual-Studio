#ifndef  _TESTQUERY_H_
#define  _TESTQUERY_H_
#include"Header.h"
#include"StrBlob.h"

using line_no = vector<string>::size_type;
class TextQuery {
private:
	shared_ptr<StrBlob> file;
	map<string, shared_ptr<set<line_no>>> wm;
	class QueryResult;
public:
	TextQuery() = delete;
	TextQuery(istream&);
	virtual ~TextQuery();
	QueryResult query(const string&)const;
};

class TextQuery::QueryResult {
	shared_ptr<set<line_no>> line;
	shared_ptr<StrBlob> lines;
	string sought;
public:
	ostream& print(ostream&)const;
	QueryResult(const string& sough,shared_ptr<set<line_no>> lin,
		shared_ptr<StrBlob> lie) :
		sought(sough),line(lin),lines(lie) {};
	set<line_no>::iterator begin();
	set<line_no>::iterator end();
	shared_ptr<StrBlob> get_file();
};

void runQuery(istream&);
#endif // ! _TESTQUERY_H_