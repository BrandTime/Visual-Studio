#ifndef _HEADER_H_
#define _HEADER_H_
#include<iostream>
#include<string>
using namespace std;
const int LEN = 26;
class Array;

class CEmployee
{
public:
	CEmployee(string name);
	CEmployee(const CEmployee &obj);
	virtual ~CEmployee();
	virtual double Salary() {}
	CEmployee& operator=(const CEmployee &obj);
	const CEmployee &operator,(const CEmployee &obj);
	static int Getnumber();
	string *GetStr();
	int &GetNodeNum();//验证传出引用对于封装特性的影响
protected:
	friend Array;
	friend ostream& operator<<(ostream& cou, CEmployee& obj);
	friend istream& operator>>(istream& cin, CEmployee& obj);
	static int sNodenum;
	string  *m_name;
	int m_number;
};

class CSalesman :virtual public CEmployee
{
public:
	CSalesman(string name, double salesvalue);
	~CSalesman();
	double Salary();
protected:
	double m_salesValue;
};

class CDeskman :virtual public CEmployee
{
public:
	CDeskman(string name, double officehour);
	~CDeskman();
	double Salary();
protected:
	double m_officeHour;
};

class CManager :public CSalesman, public CDeskman
{
public:
	CManager(string name, double salesvalue, double officehour);
	~CManager();
	double Salary();
};

class Array
{
	friend CEmployee;
public:
	Array(int aLength = LEN);
	virtual ~Array();
	CEmployee& operator[](int i);
	void *operator new(size_t size);
	void operator delete(void *p);
	bool Insert(CEmployee &oCN);
	bool Delete(int index);
private:
	CEmployee *m_poCN[LEN];
	int m_aLength;
	int m_aIndex;
};

#endif // !_HEADER_H_

