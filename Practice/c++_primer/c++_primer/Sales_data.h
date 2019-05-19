#ifndef _SECOND_H_
#define _SECOND_H_
#include"Header.h"
class Sales_data {
private:
	string ISBN;
	double avePrice;
	int saleNumber;
public:
	explicit Sales_data(string isbn = "", double ave = 0.0, int num = 0) :
		ISBN(isbn), avePrice(ave), saleNumber(num) {}
	string getISBN()const { return ISBN; }
	double getPrice()const { return avePrice; }
	int getCopies()const { return saleNumber; }
	void setISBN(string set) { ISBN = set; }
	void setPrice(double price) { avePrice = price; }
	void addSales(int i = 1) { saleNumber += i; }
	Sales_data& operator+(const Sales_data& s);
	friend istream& operator>>(istream& in, Sales_data& ob);
	friend ostream& operator<<(ostream& out, const Sales_data& ob);
};
#if 0
class HasPtr {
	//pointerlike class
private:
	string *ps;
	int i;
	size_t *use;
public:
	friend void swap(HasPtr& first, HasPtr& second);
	HasPtr(const string& s = string()) :
		ps(new string(s)), i(0), use(new size_t(1)) {}
	HasPtr(const HasPtr& p) :
		ps(new string(*(p.ps))), i(p.i), use(p.use) {
		++*use;
	}
	HasPtr& operator=(const HasPtr& p) {
		if (&p != this) {
			if (--*use == 0) {
				delete use;
				delete ps;
			}
			this->ps = p.ps;
			this->i = p.i;
			this->use = p.use;
			++*use;
		}
		return *this;
	}
	~HasPtr() {
		if (--*use == 0) {
			delete use;
			delete ps;
		}
	}
	string getStr()const {
		return *ps;
	}
	size_t getUse()const {
		return *use;
	}
};
#endif
#endif // ! _SECOND_H_