#include<iostream>
using namespace std;

class Account {
private:
	long id;
	static long count;
	double money;
	double annualInterest;
public:
	Account(double money = 0,double annualInterest=0.015):
		money(money),annualInterest(annualInterest){
		id = ++count;
	}
	~Account() {}
	void printAnnualInterest()const {
		cout << "年利率：" << annualInterest << endl;
	}
	void printMoney()const {
		cout << "余额：" << money << endl;
	}
	double getAnnualInterest()const {
		return annualInterest;
	}
	double getMoney()const {
		return money;
	}
	void deposit(double de) {
		money += de;
	}
	void withdraw(double wi) {
		money -= wi;
	}
};
long Account::count = 0;


int main(void) {
	Account ac(2000);
	ac.withdraw(1500);
	ac.deposit(10000);
	cout << "账户余额：" << ac.getMoney() << endl;
	cout << "月利率：" << ac.getAnnualInterest() / 12 << endl;

	system("pause");
	return 0;
}