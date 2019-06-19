#ifndef  _HASPTR_HPP_
#define _HASPTR_HPP_
#include"Header.h"

class HasPtr {
	//pointerlike class
private:
	string *ps;
	size_t *use;
public:
	HasPtr() = delete;
	explicit HasPtr(const string&);
	HasPtr(const HasPtr&);
	HasPtr(HasPtr&&)noexcept;
	HasPtr& operator=(HasPtr );
	~HasPtr();
	string getStr()const;
	size_t getUse()const;
	inline friend void swap(HasPtr&, HasPtr&);
	inline bool operator<(const HasPtr&);
};









void swap(HasPtr& a, HasPtr& b) {
	cout << "Execute swap!" << endl;
	swap(a.ps, b.ps);
	swap(a.use, b.use);
}
bool HasPtr::operator<(const HasPtr& a) {
	return *ps < *(a.ps);
}
HasPtr::HasPtr(const string& s = string()) :
	ps(new string(s)), use(new size_t(1)) {}
HasPtr::HasPtr(const HasPtr& p) :
	ps(new string(*(p.ps))),use(new size_t(*(p.use))) {
	++*use;
}
HasPtr::HasPtr(HasPtr&& copy)noexcept {
	delete use;
	delete ps;
	use = copy.use;
	ps = copy.ps;
	copy.use = nullptr;
	copy.ps = nullptr;
}
HasPtr& HasPtr::operator=(HasPtr p) {
	swap(*this, p);
	return *this;
}
HasPtr::~HasPtr() {
	if (--*use == 0) {
		delete use;
		delete ps;
	}
}
string HasPtr::getStr()const {
	return *ps;
}
size_t HasPtr::getUse()const {
	return *use;
}
#endif // ! _HASPTR_HPP_
