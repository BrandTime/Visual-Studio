#ifndef _FIRST_H_
#define _FIRST_H_
#include"Header.h"
//C++ Primer P475, English version
class StrBlobPtr;
using size_type = vector<string>::size_type;

class StrBlob {
public:
	StrBlob();
	StrBlob(initializer_list<string>);
	~StrBlob() = default;
	size_type size()const { return data->size(); }
	bool empty()const { return data->empty(); }
	void push_back(const string& t) { data->push_back(t); }
	void push_back(string&&) ;
	void pop_back();
	string& front();
	string& back();
	string& at(size_type);
	string& operator[](size_t);
	const string& operator[](size_t)const;
	StrBlobPtr begin()const;
	StrBlobPtr end()const;
	friend bool operator==(const StrBlob&, const StrBlob&);
	friend bool operator!=(const StrBlob&, const StrBlob&);
	friend bool operator<(const StrBlob&, const StrBlob&);
private:
	friend class StrBlobPtr;
	shared_ptr<vector<string>> data;
	void check(size_type, const string&="") const;
};

class StrBlobPtr {
private:
	shared_ptr<vector<string>> check(size_t, const string& i="")const;
	weak_ptr<vector<string>> wptr;
	size_t curr;
public:
	StrBlobPtr() :curr(0) {}
	StrBlobPtr(const StrBlob& , size_t);
	string& deref()const;
	StrBlobPtr& incr();
	string& operator[](size_t);
	const string& operator[](size_t)const;
	friend bool operator==(const StrBlobPtr&,
		const StrBlobPtr& second);
	friend bool operator!=(const StrBlobPtr& ,
		const StrBlobPtr&);
	friend bool operator<(const StrBlobPtr& , 
		const StrBlobPtr&);
};
 



const string& StrBlobPtr::operator[](size_t s)const {
	check(s, "subscript out of range");
	return wptr.lock()->operator[](s);
}
string& StrBlobPtr::operator[](size_t s) {
	check(s, "subscript out of range");
	return wptr.lock()->operator[](s);
}
string& StrBlob::operator[](size_t s) {
	check(s, "subscript out of range");
	return data->operator[](s);
}
const string& StrBlob::operator[](size_t s)const {
	check(s, "subscript out of range");
	return data->at(s);
}
bool operator<(const StrBlobPtr& a, const StrBlobPtr& b) {
	if (a.wptr.lock() == b.wptr.lock()) {
		if (!(a.wptr.lock()))
			return false;
		return a.curr < b.curr;
	}
	else
		return false;
}
bool operator<(const StrBlob& a, const StrBlob& b) {
	return *(a.data) < *(b.data);
}
bool operator!=(const StrBlob& a, const StrBlob& b) {
	return !(a == b);
}
bool operator==(const StrBlob& a, const StrBlob& b) {
	if (a.data->size() != b.data->size())
		return false;
	else {
		return equal(a.data->begin(), a.data->end(), b.data->begin());
	}
}
StrBlob::StrBlob() :data(make_shared<vector<string>>()) {}
StrBlob::StrBlob(initializer_list<string> il) :
	data(make_shared<vector<string>>(il)) {}
void StrBlob::check(size_type i, const string& msg="")const {
	if (i >= data->size())
		throw out_of_range(msg);
}
void StrBlob::push_back(string&& s) {
	data->push_back(std::move(s));
}
void StrBlob::pop_back() {
	check(0, "Pop_back on empty StrBlob");
	data->pop_back();
}
string& StrBlob::front() {
	check(0, "front on empty StrBlob");
	return data->front();
}
string& StrBlob::at(size_type i) {
	return data->at(i);
}
string& StrBlob::back() {
	check(0, "back on empty StrBlob");
	return data->back();
}
StrBlobPtr StrBlob::begin()const {
	return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::end()const {
	return StrBlobPtr(*this, data->size());
}

StrBlobPtr::StrBlobPtr(const StrBlob &a, size_t sz = 0) :
	wptr(a.data), curr(sz) {}
StrBlobPtr& StrBlobPtr::incr() {
	check(curr, "increment past end");
	++curr;
	return *this;
}
string& StrBlobPtr::deref()const {
	//auto p = check(curr, "dereference past end");
	//return (*p)[curr];
	return (*check(curr, "dereference past end"))[curr];
}
shared_ptr<vector<string>> StrBlobPtr::check(size_t i, const string& msg)const {
	auto ret = wptr.lock();
	if (!ret)
		throw runtime_error("unbounded StrBlobPtr");
	if (i >= ret->size())
		throw out_of_range(msg);
	return ret;
}
bool operator==(const StrBlobPtr& first,
	const StrBlobPtr& second) {
	auto first_p = first.check(0),
		second_p = second.check(0);
	if (first_p == second_p && first.curr == second.curr)
		return true;
	else
		return false;
}
bool operator!=(const StrBlobPtr& first,
	const StrBlobPtr& second) {
	return !(first == second);
}






//StrBlob debug program
#if 0
#include"StrBlob.h"

int main() {
	try {
		fstream in("output1.txt", ios::in);
		if (!in) {
			throw runtime_error("file open fail");
		}
		const StrBlob str({ "hello","ggg" });
		list<string> li;
		while (!in.fail()) {
			string line;
			getline(in, line);
			li.push_back(line);
		}
		StrBlobPtr ptr = str.begin(), end = str.end();
		while (ptr != end) {
			cout << ptr.deref() << endl;
			ptr.incr();
		}

	}
	catch (exception &e) {
		cout << e.what() << endl;
	}

	system("pause");
	return 0;
}
#endif
#endif // !_FIRST_H_