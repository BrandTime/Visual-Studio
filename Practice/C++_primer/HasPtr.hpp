#ifndef  _HASPTR_HPP_
#define _HASPTR_HPP_
#include"Header.h"

class HasPtr {
	//pointerlike class
private:
	string *ps;
	int i;
	size_t *use;
public:
	HasPtr(const string&);
	HasPtr(const HasPtr&);
	HasPtr& operator=(const HasPtr& );
	~HasPtr();
	string getStr()const;
	size_t getUse()const;
	inline friend void swap(HasPtr&, HasPtr&);
	inline bool operator<(const HasPtr&);
};
void swap(HasPtr& a, HasPtr& b) {
	cout << "Execute swap!" << endl;
	swap(a.i, b.i);
	swap(a.ps, b.ps);
	swap(a.use, b.use);
}
bool HasPtr::operator<(const HasPtr& a) {
	
}










HasPtr::HasPtr(const string& s = string()) :
	ps(new string(s)), i(0), use(new size_t(1)) {}
HasPtr::HasPtr(const HasPtr& p) :
	ps(new string(*(p.ps))), i(p.i), use(new size_t(*(p.use))) {
	++*use;
}
HasPtr& HasPtr::operator=(const HasPtr& p) {
	if (&p != this) {
		if (--*use == 0) {
			delete use;
			delete ps;
		}
		this->ps = new string(*(p.ps));
		this->i = p.i;
		this->use = new size_t(*(p.use));
		++*use;
	}
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
