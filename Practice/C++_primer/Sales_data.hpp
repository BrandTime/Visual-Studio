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
#endif // ! _SECOND_H_