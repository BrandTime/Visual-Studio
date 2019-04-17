#pragma once
#include<iostream>
#include<string>
using namespace std;

enum Major_//考虑可以将所有的专业枚举出来
{

};
class Univer
{
protected:
	string Uni = "四川大学";
public:
	Univer() {}
	virtual ~Univer() {}
	void Show();
};

class Subj//单科成绩
{
private:
	string Sub;
	double Mark;
	double Fen;
	bool Com;
	string ID;
	double Gpa;
	friend ostream& operator<<(ostream&cout, Subj&obj);
	friend istream& operator>>(istream&ci, Subj&obj);
	void Gpa_();
public:
	Subj();
	Subj(string a);
	void Set();
	double GetMark();
	double GetFen();
	string GetSub();
	double GetGpa();
	string GetID();
	bool operator==(Subj p);
	bool operator>(Subj p);
};

template<class Type>
class DList;
template<class Type>
class CNode//如何将有一个数据和多个数据的不同节点抽象化？
{
	friend class DList<Type>;
	friend class OrderDList;
public:
	CNode();
	CNode(Type &T);
	~CNode();
private:
	Type Node;
	CNode *next;
	CNode *pre;
};

template<class Type>
class DList
{
protected:
	int length;
	CNode<Type> *cur;
	CNode<Type> *head;
public:
	DList();
	virtual ~DList();//基类指针可以指向派生类的对象（多态性），如果删除该指针就会调用派生类的析构函数，而派生类又会调用基类的析构函数，这样派生类对象就被完全释放；如果基类的析构函数不是虚函数，那么在经由指向基类指针删除派生类对象时由于编译器实行静态绑定，就只会调用基类的析构函数而不调用派生类析构函数，最终派生类对象释放不完全，导致内存泄漏。

	virtual bool Insert(CNode<Type> val);
	bool Delete();
	bool Search(Type val);
	bool Next();
	bool Prev();
	bool SetStart();
	int Getlength();

	virtual bool Modify();//修改当前节点的数据
	virtual void Print();
};

class OrderDList:public DList<Subj>//专门用来统计四年成绩
{
public:
	OrderDList();
	~OrderDList();
	double GetMark();
	double GetFen();
	string GetSub();
	double GetGpa();
	string GetID();
	bool Insert();//有序插入首-》尾从大到小
};

class Score//表示四年的成绩情况
{
	OrderDList score[4];
public:
	Score();
	void Printyear(int i=1);
	void Printall();
	bool Add(int i=1);
	bool Remove();
	bool Modify();
	double GetGPA();
	double GetAve();
};

class Foundemental
{
	string ID;
	string Name;
	string Major;
	string Class;
public:
	Foundemental();
	void Set();
	void Print()const;
};

class Complement//表示特长、目标、参加的社会活动、获得的奖励、接受的处分等附加信息
{
	DList<string> Goal;
	DList<string>  Strength;//特长
	DList<string> Acitivity;
	DList<string> Award;
	DList<string> Punish;
public:
	Complement(){}
	~Complement(){}
	bool SetG();//均未添加删除，修改功能
	bool SetS();
	bool SetAc();
	bool SetAw();
	bool SetP();
	void Show();
};

class Info :virtual public Univer
{
	Foundemental Fun;
	Score  S;
	Complement C;
public:
	Info(){}
	void ShowF();
	void ShowS();
	void Showall();
	void ShowC();
	void SetF();
	void SetC();
	double GetGPA();
	double GetAve();
	bool AddS(int i = 1);
};
