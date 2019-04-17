#include"Header.h"
int CEmployee::sNodenum = 0;
CEmployee::CEmployee(string name)
{
	m_name = new string(name);
	if (!m_name)
	{
		cout << "内存分配失败！" << endl;
		exit(0);
	}
	m_number = Getnumber();
	cout << "CEmpolyee 创建新节点，NO：" << m_number << ",Name:" << m_name << endl;
}
CEmployee::~CEmployee()
{
	cout << "CEmployee Destroy!" << endl;
	delete m_name;
}
const CEmployee& CEmployee::operator,(const CEmployee &obj)
{
	return obj;
}
CEmployee& CEmployee::operator=(const CEmployee &obj)
{
	if (this == &obj)
		return *this;
	delete m_name;
	m_name = new string(*obj.m_name);
	if (!m_name)
	{
		cout << "内存空间分配失败！" << endl;
		exit(0);
	}
	m_number = obj.m_number;
	cout << "复制对象，Name" << m_name << ",Number:" << m_number << endl;
	return *this;
}
ostream& operator<<(ostream& cou, CEmployee& obj)
{
	cou << "Name:" << obj.GetStr() << endl;
	cou << "Number:" << obj.m_number << endl;
}
istream& operator>>(istream& ci, CEmployee& obj)
{
	char s[81];
	cout << "Please Enter Your Name:";
	ci.getline(s, 81, '\n');
	*(obj.GetStr()) = s;
	cout << "Please Enter Your Number:";
	ci >> obj.GetNodeNum();
	return ci;
}
string* CEmployee::GetStr()
{
	return m_name;
}
int CEmployee::Getnumber()
{
	return sNodenum < LEN ? sNodenum++ : (sNodenum = 0);
}
int &CEmployee::GetNodeNum()
{
	return m_number;
}
CEmployee::CEmployee(const CEmployee &obj)
{
	m_name = new string(*obj.m_name);
	if (!m_name)
	{
		cout << "节点分配失败！" << endl;
		exit(0);
	}
	m_number = Getnumber();
	cout << "CEmployee 拷贝创建节点成功！NO：" << m_number <<
		",Name" << m_name << endl;
}

CSalesman::CSalesman(string name, double salsevalue)
	: CEmployee(name), m_salesValue(salsevalue) {}
CSalesman::~CSalesman()
{
	cout << "CSalesman Destroy!" << endl;
}
double CSalesman::Salary()
{
	return m_salesValue * 27.5;
}

CDeskman::CDeskman(string name, double officehour)
	:CEmployee(name), m_officeHour(officehour) {}
CDeskman::~CDeskman()
{
	cout << "CDeskman Destroy!" << endl;
}
double CDeskman::Salary()
{
	return m_officeHour*30.7;
}
CManager::CManager(string name, double salesvalue, double officehour)
	:CSalesman(name, salesvalue), CDeskman(name, officehour), CEmployee(name) {}
CManager::~CManager()
{
	cout << "CManager Destroy!" << endl;
}
double CManager::Salary()
{
	return m_officeHour*30.7 + m_salesValue*25.5;
}
Array::Array(int aLength = LEN)
{
	for (int i = 0; i < aLength; i++)
	{
		m_poCN[i] = NULL;
	}
	m_aLength = aLength;
	m_aIndex = 0;
	cout << "CEmplooyee，创建一个结点数组对象，legth=:" << m_aLength << endl;
}
Array::~Array()
{
	for (int i = 0; i < m_aLength; i++)
	{
		if (m_poCN[i])
		{
			delete m_poCN[i];
			m_poCN[i] = NULL;
			cout << "delete:m_pocN[" << i << "]." << endl;
		}
	}
	cout << "结点析构完成!" << endl;
}
