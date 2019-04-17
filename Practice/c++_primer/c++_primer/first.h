#ifndef _FIRST_H_
#define _FIRST_H_
#include"Header.h"
class StrBlobPtr;
class StrBlob {
public:
	typedef vector<string>::size_type size_type;
	StrBlob();
	StrBlob(initializer_list<string> il);
	StrBlob(const StrBlob& copy);
	~StrBlob() = delete;
	StrBlob& operator=(const StrBlob& copy);
	size_type size()const { return data->size(); }
	bool empty()const { return data->empty(); }
	void push_back(const string& t) { data->push_back(t); }
	void pop_back();
	string& front();
	string& back();
	StrBlobPtr begin()const;
	StrBlobPtr end()const;
private:
	friend class StrBlobPtr;
	shared_ptr<vector<string>> data;
	void check(size_type i, const string& msg) const;
};
#if 0
StrBlob& StrBlob::operator=(const StrBlob& copy) {
	if (&copy != this) {
		this->data = make_shared<vector<string>>(copy.data);
	}
	return *this;
}
StrBlob::StrBlob(const StrBlob& copy) {
	this->data = make_shared<vector<string>>(copy.data);
}
#endif
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