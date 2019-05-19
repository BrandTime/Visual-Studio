#ifndef _FIRST_H_
#define _FIRST_H_
#include"Header.h"
//C++ Primer P475, English version
class StrBlobPtr;
using size_type = vector<string>::size_type;

class StrBlob {
public:
	StrBlob();
	StrBlob(initializer_list<string> il);
	~StrBlob() = default;
	size_type size()const { return data->size(); }
	bool empty()const { return data->empty(); }
	void push_back(const string& t) { data->push_back(t); }
	void pop_back();
	string& front();
	string& back();
	string& at(size_type);
	StrBlobPtr begin()const;
	StrBlobPtr end()const;
private:
	friend class StrBlobPtr;
	shared_ptr<vector<string>> data;
	void check(size_type i, const string& msg) const;
};

class StrBlobPtr {
private:
	shared_ptr<vector<string>> check(size_t, const string& i="")const;
	weak_ptr<vector<string>> wptr;
	size_t curr;
public:
	StrBlobPtr() :curr(0) {}
	StrBlobPtr(const StrBlob &a, size_t sz = 0) :
		wptr(a.data), curr(sz) {}
	string& deref()const;
	StrBlobPtr& incr();
	friend bool operator==(const StrBlobPtr& first,
		const StrBlobPtr& second);
	friend bool operator!=(const StrBlobPtr& first,
		const StrBlobPtr& second);
};

#endif // !_FIRST_H_