#pragma once
#include<iostream>
#include<string>
using namespace std;

enum Major_//���ǿ��Խ����е�רҵö�ٳ���
{

};
class Univer
{
protected:
	string Uni = "�Ĵ���ѧ";
public:
	Univer() {}
	virtual ~Univer() {}
	void Show();
};

class Subj//���Ƴɼ�
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
class CNode//��ν���һ�����ݺͶ�����ݵĲ�ͬ�ڵ���󻯣�
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
	virtual ~DList();//����ָ�����ָ��������Ķ��󣨶�̬�ԣ������ɾ����ָ��ͻ������������������������������ֻ���û���������������������������ͱ���ȫ�ͷţ����������������������麯������ô�ھ���ָ�����ָ��ɾ�����������ʱ���ڱ�����ʵ�о�̬�󶨣���ֻ����û��������������������������������������������������ͷŲ���ȫ�������ڴ�й©��

	virtual bool Insert(CNode<Type> val);
	bool Delete();
	bool Search(Type val);
	bool Next();
	bool Prev();
	bool SetStart();
	int Getlength();

	virtual bool Modify();//�޸ĵ�ǰ�ڵ������
	virtual void Print();
};

class OrderDList:public DList<Subj>//ר������ͳ������ɼ�
{
public:
	OrderDList();
	~OrderDList();
	double GetMark();
	double GetFen();
	string GetSub();
	double GetGpa();
	string GetID();
	bool Insert();//���������-��β�Ӵ�С
};

class Score//��ʾ����ĳɼ����
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

class Complement//��ʾ�س���Ŀ�ꡢ�μӵ��������õĽ��������ܵĴ��ֵȸ�����Ϣ
{
	DList<string> Goal;
	DList<string>  Strength;//�س�
	DList<string> Acitivity;
	DList<string> Award;
	DList<string> Punish;
public:
	Complement(){}
	~Complement(){}
	bool SetG();//��δ���ɾ�����޸Ĺ���
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
