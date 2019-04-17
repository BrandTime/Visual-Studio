#include"class.h"

void Univer::Show()
{
	cout << "四川大学" << endl << endl;
}

bool Subj::operator>(Subj p)
{
	if (this->Mark > p.Mark)
		return true;
	else
		return false;
}
bool Subj::operator==(Subj p)
{
	if (p.ID == this->ID)
		return true;
	else
		return false;
}
ostream& operator<<(ostream&cou, Subj&obj)
{
	cou << "课程代码：" << obj.ID << endl;
	cou << "课程名：" << obj.Sub << endl;
	cou << "课程类别：";
	if (obj.Com)
		cout << "必修" << endl;
	else
		cout << "选修" << endl;
	cou << "课程学分" << obj.Fen << endl;
	cou << "课程成绩：" << obj.Mark << endl;
	return cou;
}
istream& operator>>(istream&ci, Subj&obj)
{
	cout << "修改后的成绩：" << endl;
	cin >> obj.Mark;
	return cin;
}
Subj::Subj(){}
void Subj::Set()
{
	cout << "请输入科目名称：" << endl;
	cin >> Sub;
	cout << "请输入课程代码：" << endl;
	cin >> ID;
	cout << "请输入该科目成绩：" << endl;
	cin >> Mark;
	cout << "请输入该科目学分：" << endl;
	cin >> Fen;
	cout << "该科目是必修还是选修？（必修请输入1，选修请输入0）" << endl;
	cin >> Com;
	Gpa_();
}
Subj::Subj(string a)//用于基本类型向类类型的转换
{
	ID = a;
}
double Subj::GetMark()
{
	return Mark;
}
double Subj::GetFen()
{
	return Fen;
}
string Subj::GetSub()
{
	return Sub;
}
double Subj::GetGpa()
{
	return Gpa;
}
string Subj::GetID()
{
	return ID;
}
void Subj::Gpa_()
{
	if (Mark >= 95)
		Gpa = 4.0;
	else if (Mark >= 90)
		Gpa = 3.8;
	else if (Mark >= 85)
		Gpa = 3.6;
	else if (Mark >= 80)
		Gpa = 3.2;
	else if (Mark >= 75)
		Gpa = 2.7;
	else if (Mark >= 70)
		Gpa = 2.2;
	else if (Mark >= 65)
		Gpa = 1.7;
	else if (Mark >= 60)
		Gpa = 1.0;
	else
		Gpa = 0.0;
}

Foundemental::Foundemental(){}
void Foundemental::Set()
{
	cout << "请输入学号：" << endl;
	cin >> ID;
	cout << "请输入姓名：" << endl;
	cin >> Name;
	cout << "请输入专业：" << endl;
	cin >> Major;
	cout << "请输入班级代号；" << endl;
	cin >> Class;
}
void Foundemental::Print()const
{
	cout << "学号：" << ID << endl;
	cout << "姓名：" << Name << endl;
	cout << "专业：" << Major << endl;
	cout << "班级号：" << Class << endl;
	cout << endl << endl << endl;
}

OrderDList::OrderDList() :DList<Subj>() {}
OrderDList::~OrderDList(){}
double OrderDList::GetMark()
{
	return cur->Node.GetMark();
}
double OrderDList::GetFen()
{
	return cur->Node.GetFen();
}
string OrderDList::GetSub()
{
	return cur->Node.GetSub();
}
double OrderDList::GetGpa()
{
	return cur->Node.GetGpa();
}
string OrderDList::GetID()
{
	return cur->Node.GetID();
}
bool OrderDList::Insert()//链表内部数据由大到小排列
{
	Subj *temp1 = new Subj;
	if (!temp1)
		exit(0);
	temp1->Set();
	cout << endl << endl << endl << endl;
	CNode<Subj> *temp = new CNode<Subj>(*temp1);
	if (!temp)
		exit(0);
	CNode<Subj> *p2,*p1;
	if (head == NULL)
	{
		temp->next = NULL;
		temp->pre = NULL;
		cur = head = temp;
	}
	else
	{
		if (temp->Node > head->Node)
		{
			temp->next = head;
			temp->pre = NULL;
			head->pre = temp;
			cur = head = temp;
		}
		else
		{
			for (p2 = head, p1 = head->next; p1 != NULL; p2 = p1, p1 = p1->next)
			{
				if (temp->Node > p1->Node)
				{
					temp->pre = p2;
					temp->next = p1;
					p2->next = temp;
					p1->pre = temp;
					break;
				}
			}
			if (p1 == NULL)
			{
				temp->next = NULL;
				temp->pre = p2;
				p2->next = temp;
			}
		}
	}
	length++;
	cout << endl<<"EOF" << endl;
	return true;
}

Score::Score(){}
bool Score::Modify()
{
	string a;
	cout << "请输入想管理的课程代码：(仅能修改成绩)" << endl;
	cin >> a;
	for (int i = 0; i <= 3; i++)
	{
		if (score[i].Getlength() == 0)
			continue;
		if (score[i].Search(a))
		{
			score[i].Modify();
			break;
		}
		else
			cout << "无此课程，请添加！" << endl;
	}
	return true;
}
bool Score::Add(int i )
{
	if (score[i-1].Insert())
		return true;
	else
		return false;
}
bool Score::Remove()
{
	string a;
	cout << "请输入想删除的课程代码：" << endl;
	cin >> a;
	for (int i = 0; i <= 3; i++)
	{
		if (score[i].Getlength() == 0)
			continue;
		if (score[i].Search(a))
		{
			cout << "Delete……" << endl;
			if (score[i].Delete())
			{
				cout << "Sucess!" << endl;
				return true;
			}
		}
	}
	return false;
}
void Score::Printyear(int i )
{
	score[i - 1].Print();
}
void Score::Printall()
{
	for (int i = 0; i <= 3; i++)
		score[i].Print();
	cout << "所有科目平均分：" << GetAve() << endl;
	cout << "平均绩点：" << GetGPA() << endl<<endl;
}
double Score::GetAve()
{
	double M = 0;
	double F = 0;
	for (int i = 0; i <= 3; i++)
	{
		if (score[i].Getlength() == 0)
			continue;
		score[i].SetStart();
		do
		{
			M += score[i].GetMark()*score[i].GetFen();
			F += score[i].GetFen();
		} while (score[i].Next());
	}
	M /= F;
	return M;
}
double Score::GetGPA()
{
	double G = 0;
	double F = 0;
	for (int i = 0; i <= 3; i++)
	{
		if (score[i].Getlength() == 0)
			continue;
		score[i].SetStart();
		do
		{
			G += score[i].GetGpa()*score[i].GetFen();
			F += score[i].GetFen();
		} while (score[i].Next());
	}
	G /= F;
	return G;
}

bool Complement::SetAc()
{
	string a;
	cout << "请输入：" << endl;
	cin >> a;
	if (Acitivity.Insert(a))
		return true;
	return false;
}
bool Complement::SetAw()
{
	string a;
	cout << "请输入：" << endl;
	cin >> a;
	if (Award.Insert(a))
		return true;
	return false;
}
bool Complement::SetS()
{
	string a;
	cout << "请输入：" << endl;
	cin >> a;
	if (Strength.Insert(a))
		return true;
	return false;
}
bool Complement::SetP()
{
	string a;
	cout << "请输入：" << endl;
	cin >> a;
	if (Punish.Insert(a))
		return true;
	return false;
}
bool Complement::SetG()
{
	string a;
	cout << "请输入：" << endl;
	cin >> a;
	if (Goal.Insert(a))
		return true;
	return false;
}
void Complement::Show()
{
	cout << "附加信息如下：" << endl;
	Goal.Print();
	Strength.Print();
	Acitivity.Print();
	Award.Print();
	Punish.Print();
}

void Info::Showall()
{
	Show();
	Fun.Print();
	S.Printall();
}
void Info::ShowF()
{
	Fun.Print();
}
void Info::ShowS()
{
	S.Printall();
}
void Info::SetF()
{
	Fun.Set();
}
double Info::GetAve()
{
	return S.GetAve();
}
double Info::GetGPA()
{
	return S.GetGPA();
}
bool Info::AddS(int i)
{
	S.Add(i);
	return true;
}
void Info::ShowC()
{
	C.Show();
}
void Info::SetC()
{
	int a;
	do
	{
		cout << "要添加那种项目？（1----特长，2---目标，3---参加的社会活动，4-----获得的奖励，5-----处分,其他----退出）" << endl;
		cin >> a;
		switch (a)
		{
		case 1:
			C.SetS();
			break;
		case 2:
			C.SetG();
			break;
		case 3:
			C.SetAc();
			break;
		case 4:
			C.SetAw();
			break;
		case 5:
			C.SetP();
			break;
		default:
			;
		}
	} while (a>0 && a<6);
}


//以下是类模板的成员函数
template<class Type>
CNode<Type>::CNode(Type &T)
{
	Node = T;
	pre = NULL;
	next = NULL;
}
template<class Type>
CNode<Type>::CNode()
{
	pre = NULL;
	next = NULL;
}
template<class Type>
CNode<Type>::~CNode()
{
	Type *temp = &Node;
	delete temp;
	next = pre = NULL;
}
template<class Type>
DList<Type>::DList()
{
	length = 0;
	cur = head = NULL;
}
template<class Type>
DList<Type>::~DList()
{
	CNode<Type> *temp = cur = head;
	while (temp != NULL)
	{
		cur = cur->next;
		delete temp;
		temp = cur;
	}
	cur = head = NULL;
	length = 0;
}
template<class Type>
int DList<Type>::Getlength()
{
	return length;
}
template<class Type>
bool DList<Type>::Insert(CNode<Type> val)//将新节点的分配放在其他地方
{
	CNode<Type> *temp = &val;
	if (head == NULL)
	{
		temp->next = temp->pre = temp;
		head = temp;
	}
	else
	{
		temp->next = cur->next;
		temp->pre = cur;
		if (cur->next != NULL)
			cur->next->pre = temp;
		if (cur->pre != NULL)
			cur->pre->next = temp;
	}
	cur = temp;
	length++;
	return true;
}
template<class Type>
bool DList<Type>::Delete()
{
	if (head == NULL)
		return false;
	CNode<Type> *temp = cur;
	if (cur->pre != NULL)
	{
		if (cur->next != NULL)
		{
			cur->pre->next = cur->next;
			cur->next->pre = cur->pre;
		}
		else
			cur->pre->next = NULL;
	}
	else
	{
		if (cur->next != NULL)
		{
			cur->next->pre = NULL;
			head = cur = cur->next;
		}
		else
			head = cur = NULL;
	}
	delete temp;
	length--;
	return true;
}
template<class Type>
bool DList<Type>::Search(Type val)//对于课程的查找仅能根据课程代码进行
{
	if (head == NULL)
		return false;
	cur = head;
	while (cur != NULL)
	{
		if (cur->Node == val)//要求重载“==”运算符
			break;
	}
	if (cur == NULL)
	{
		cout << "NOT FOUND！" << endl;
		return false;
	}
	else
		cout << cur->Node;//要求重载“<<"运算符
	cur = head;
	return true;
}
template<class Type>
bool DList<Type>::SetStart()
{
	if (!head)
		return false;
	cur = head;
	return true;
}
template<class Type>
bool DList<Type>::Next()
{
	if (!head)
		return false;
	if (cur->next != NULL)
	{
		cur = cur->next;
		return true;
	}
	else
		return false;
}
template<class Type>
bool DList<Type>::Prev()
{
	if (!head)
		return false;
	if (cur->pre != NULL)
	{
		cur = cur->pre;
		return true;
	}
	else
		return false;
}
template<class Type>
void DList<Type>::Print()
{
	if (head == NULL)
	{
		cout << "无!" << endl;
		return;
	}
	cur = head;
	while (cur != NULL)
	{
		cout << cur->Node << endl << end;
		cur = cur->next;
	}
	cur = head;
	return;
}
template<class Type>
bool DList<Type>::Modify()//对于科目来说仅能修改成绩
{
	if (head == NULL)
		return false;
	if (cur != NULL)
	{
		cout << "请输入：";
		cin >> cur->Node;//require overload operator ">>"
		return true;
	}
	else
		return false;
}