#include<iostream>
#include<vector>
using namespace std;

//MATCHING_SERVICE �ȶϢ�黹(ÿ�µȶ�
//MATCHING_REPAYMENT �ȶ��黹(ÿ�µݼ����
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
	double owed=0;//��ǰǷ��
	double interest=0;//����Ϣ
	double interestRate = 0.049;
	MODE mode = MATCHING_SERVICE;//����ģʽ
	int years=1;//Ԥ�ƻ�������
	Date begin;//�״λ�������
	vector<pair<Date, double> > series;//�������У�
public:
	Loan() {};
	Loan(double, double, MODE,int, Date);
	Loan(const Loan&);
	Loan& operator=(const Loan&);
	double getOwed()const;
	double getInterest()const;
	double averageRetu()const;//����ÿ��ƽ���軹���
	void setMode(MODE);
	void showSeries()const;//չʾ������Ϣ
};
Loan::Loan(double owed, double interestRate, MODE mode,
	int years, Date begin) :owed(owed), interestRate(interestRate),
	mode(mode), years(years), begin(begin) {}
Loan::Loan(const Loan& copy) {
	if (&copy != this) {
		Loan(copy.owed, copy.interestRate, copy.mode, copy.years, copy.begin);
	}
}
