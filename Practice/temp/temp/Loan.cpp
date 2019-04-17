#include<iostream>
#include<vector>
using namespace std;

//MATCHING_SERVICE 等额本息归还(每月等额还款）
//MATCHING_REPAYMENT 等额本金归还(每月递减还款）
enum MODE{MATCHING_SERVICE=0,MATCHING_REPAYMENT};

class Date {
private:
	int year;
	int month;
public:
	Date(int y = 2019, int month = 1) :year(y), month(month) {}
	void setYear(int y) {
		year = y;
	}
	void setMonth(int m) {
		month = m;
	}
	int getYear()const {
		return year;
	}
	int getMonth()const {
		return month;
	}
};

class Loan {
private:
	double owed=0;//当前欠账
	double interest=0;//年利息
	double interestRate = 0.049;
	MODE mode = MATCHING_SERVICE;//还款模式
	int years=1;//预计还款年数
	Date begin;//首次还款年月
	vector<pair<Date, double> > series;//还款序列；
public:
	Loan() {};
	Loan(double, double, MODE,int, Date);
	Loan(const Loan&);
	Loan& operator=(const Loan&);
	double getOwed()const;
	double getInterest()const;
	double averageRetu()const;//返回每月平均需还金额
	void setMode(MODE);
	void showSeries()const;//展示还款信息
};
Loan::Loan(double owed, double interestRate, MODE mode,
	int years, Date begin) :owed(owed), interestRate(interestRate),
	mode(mode), years(years), begin(begin) {}
Loan::Loan(const Loan& copy) {
	if (&copy != this) {
		Loan(copy.owed, copy.interestRate, copy.mode, copy.years, copy.begin);
	}
}
