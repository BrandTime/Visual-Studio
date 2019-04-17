#include<iostream>
#include<string>
using namespace std;

enum Status
{
	put_in_storage = 0,
	has_been_sent,
	on_the_road,
	arrive_in_storage,
	is_sending,
	sign_in,
};

class Person										//收发人类
{
public:
	Person() {};
	void SetName(string name) { this->Name = name; }						//设定姓名
	void SetAddress(string address) { this->Address = address; }			//设定地址
	void SetNumber(string number) { this->Pnumber = number; }		//设定电话
	string ApiName() { return Name; }													//返回姓名
	string ApiAddress() { return Address; }											//返回地址
	string ApiNumber() { return Pnumber; }											//返回电话
private:
	string Name;		//姓名
	string Address;		//地址
	string Pnumber;		//电话
};

class Package									//包裹类
{
public:
	Package() { this->status = put_in_storage; }
	void Setaddressorname(string name) { Addressor.SetName(name); }				//设定 寄件人姓名
	void Setaddressorphone(string phone) {															//设定 寄件人电话
		while (phone.size()!=11)
		{
			cout << "错误！请校验电话！11位数字。！" << endl;
			cin >> phone;
		}
		Addressor.SetNumber(phone); 
	}		
	void Setaddressorplace(string address) { Addressor.SetAddress(address); }	//设定 寄件人地址
	void Setreceivername(string name) { Reciever.SetName(name); }					//设定 收件人姓名
	void Setreceiverphone(string phone) {															//设定 收件人电话	
		while (phone.size() != 11)
		{
			cout << "错误！请校验电话！11位数字。！" << endl;
			cin >> phone;
		}
		Reciever.SetNumber(phone); 
	}			
	void Setreceiverplace(string address) { Reciever.SetAddress(address); }			//设定 收件人地址
	void SetCost(double cost) { this->Cost = cost; }												//设定费用
	void SetID(string id) { 																						//设定编号
		while (id.size()!=10)	
		{
			cout << "错误！请校验快递编号！10位数字。" << endl;
			cin >> id;
		}
		this->ID = id;
	}															
	void Setweight(double weight) { this->Weight = weight; }								//设定重量
	void SetStatus(Status s);																					//设定快递状态
	string ApiRname() { return(Reciever.ApiName()); }											//返回收件人姓名
	string ApiAname() { return(Addressor.ApiName()); }										//返回寄件人姓名
	string ApiID() { return ID; }																				//返回编号
	double ApiCost() { return Cost; }																		//返回费用
	double ApiWeight() { return Weight; }																//返回重量
	Status ApiS() { return status; }																			//返回包裹状态
	void Print();																										//显示包裹类的全部信息
private:
	Status status;
	Person Reciever;
	Person Addressor;
	string ID;
	double Cost;
	double Weight;
};

class Pack														//链表单元
{
public:
	Package p;
	Pack *next;
	Pack *pre;
	bool f;																										//表示当前包裹的状态，true表示已被查找过
	void Ref()																								//反转当前包裹状态
	{
		f = (f == false) ? true : false;
	}
	Pack(Package &p1)
	{
		p = p1;
		next = pre = NULL;
		f = false;
	}
};																			//定义f

class Package_list													//包裹的链表存储类
{
private:
	Pack *cur;
	Pack *head;
	int num;																											//当前运送的包裹总数
	bool F;																									//当前快递的状态
public:
	Package_list()
	{
		num = 0;
		cur = head = NULL;
		F=false;
	}
	~Package_list()
	{
		if (head)
		{
			cur = head;
			while (cur != NULL)
			{
				Pack *temp = cur;
				cur = cur->next;
				delete temp;
			}
			head = NULL;
			F=false;
			num = 0;
		}
	}
	bool Insert(Package p1);																						//新建包裹
	bool Delete(string id);																							//删除包裹
	bool Search(bool i, string a);																				//i=false表示用收件人进行查找，i=true表示用发件人进行查找，后面的string 是收件人或寄件人的名字
	bool Search(string id);																							//用编号进行搜索
	bool Print();																									//显示当前快递状态
	int Getnum();
	void Re();                                                                                                      //反转表中所有包裹的查询状态
	void StatusUP(string id);																																			//获得当前快递状态
};

class Sender :public Package_list								//邮递员类
{
public:
	Sender() { 
		Work = true;
		string name = "Jason";
		string address = "SCU";
		string phone = "12345678910";
		Worker.SetAddress(address);
		Worker.SetName(name);
		Worker.SetNumber(phone);
	}
	void Works(string id);															//快递运输到下一环节
	void Change() { Work = !Work; }											//改变快递员的工作状态
	void ApiWork() { if (Work) cout << "工作中。"; else cout << "休假中。"; cout << endl << endl; }						//返回快递员工作状态
	string ApiWname() { return (Worker.ApiName()); }				//返回快递员姓名
	string ApiWnumber() { return (Worker.ApiNumber()); }		//返回快递员电话
	string ApiWaddress() { return (Worker.ApiAddress()); }		//返回快递员地址
private:
	Person Worker;
	bool Work;
};

class Manage :public Sender									//管理类
{
public:
	Sender *s1, *s2;
	Manage() { s1 = new Sender; s2 = new Sender; };
};

// Package类 //

void Package::SetStatus(Status s)
{
	this->status = s;
}

void Package::Print()												//显示包裹类的全部信息
{
	cout << "寄件人姓名： " << ApiAname() << endl;
	cout << "寄件人电话： " << Addressor.ApiNumber() << endl;
	cout << "寄件人地址： " << Addressor.ApiAddress() << endl << endl;
	cout << "收件人姓名： " << ApiRname() << endl;
	cout << "收件人电话： " << Reciever.ApiNumber() << endl;
	cout << "收件人地址： " << Reciever.ApiAddress() << endl << endl;
	cout << "编号： " << ApiID() << endl;
	cout << "费用： " << ApiCost() << endl;
	cout << "重量： " << ApiWeight() << endl << endl;
}

void Package_list::StatusUP(string id)
{
	if(!head)
		return ;
	if(!Search(id))
		return ;
	int x = cur->p.ApiS();
	x++;
	switch (x)
	{
	case 0:cur->p.SetStatus(put_in_storage); cout << "包裹已经入库" << endl; break;
	case 1:cur->p.SetStatus(has_been_sent); cout << "包裹已经取出" << endl; break;
	case 2:cur->p.SetStatus(on_the_road); cout << "包裹正在路上" << endl; break;
	case 3:cur->p.SetStatus(arrive_in_storage); cout << "包裹已经送达仓库" << endl; break;
	case 4:cur->p.SetStatus(is_sending); cout << "包裹开始配送" << endl; break;
	default:
	case 5:cur->p.SetStatus(sign_in); cout << "包裹已签收" << endl; break;
	}
}


// Package_list类 //

int Package_list::Getnum()
{
	return num;
}

bool Package_list::Insert(Package p1)
{
	Pack *temp = new Pack(p1);
	if (!temp)
	{
		cout << "分配空间失败！\n";
		return false;
	}
	if (head == NULL)
		head = cur = temp;
	else
	{
		temp->next = cur->next;
		temp->pre = cur;
		if (cur->next)
			cur->next->pre = temp;
		cur->next = temp;
		cur = temp;
	}
	num++;
	return true;
}

bool Package_list::Delete(string id)
{
	if (!head)
	{
		cout << "无包裹！\n";
		return false;
	}
	if(!Search(id))
		return false;
	if (cur == head)
		head = cur->next;
	Pack *temp = cur;
	if (cur->pre)
		cur->pre->next = cur->next;
	if(cur->next)
		cur->next->pre = cur->pre;
	cur = cur->next;
	delete temp;
	num--;
	return true;
}
bool Package_list::Print()
{
	if (!head)
	{
		cout << "无包裹！\n";
		return false;
	}
	cur->p.Print();
	return true;
}
bool Package_list::Search(bool i, string a)
{
	if (!head)
	{
		cout << "无包裹！\n";
		return false;
	}
	cur = head;
	while (cur != NULL)
	{
		if (cur->f == true)
			continue;
		if (i)
		{
			if (cur->p.ApiAname() == a)
			{
				cur->Ref();
				cur->p.Print();
				F=true;
			}
		}
		else 
			if (cur->p.ApiRname() == a)
			{
				cur->Ref();
				cur->p.Print();
				F=true;
			}
		cur = cur->next;
	}
	if(F==false)
	{
		cout<<"404 NOT FOUND!\n";
		return false;
	}
	cur = head;
	F=false;
	Re();
	return true;
}
bool Package_list::Search(string id)
{
	if (!head)
	{
		cout << "无包裹！\n";
		return false;
	}
	cur = head;
	while (cur != NULL)
	{
		if (cur->p.ApiID() == id)
		{
			F=true;
			break;
		}
		cur = cur->next;
	}
	if(F==false)
	{
		cout<<"404 NOT FOUND!\n";
		return false;
	}
	F=false;
	return true;
}


void Package_list::Re()
{
	Pack *temp = head;
	while (temp != NULL)
	{
		if (temp->f == true)
			temp->Ref();
		temp = temp->next;
	}
}

// sender类 //

void Sender::Works(string id)
{
	Search(id);
	StatusUP(id);
}


// 操作模块 //
void MSender(Manage &m);               //对快递员管理
void MPackage(Manage &m);				//对包裹管理
void Mappend(Manage &m);				//添加包裹
void Msearch(Manage &m);				//查询包裹
void Mdelate(Manage &m);				//删除包裹
void Mchange(Manage &m);				//更改包裹状态

int main()
{
	Manage m;
	int ops;
	cout << "欢迎进入快递管理系统！" << endl << endl;
	while (1)
	{
		cout << "命令1：对快递员管理；" << endl;
		cout << "命令2：对包裹管理；" << endl;
		cout << "命令0：退出系统。" << endl << endl;
		cout << "请输入命令：";
		cin >> ops;
		switch (ops)
		{
		default:cout << "无法识别的命令！" << endl << endl; break;
		case 0: {
			cout << "已退出系统！" << endl;
			return 0;
		}
		case 1:MSender(m); break;
		case 2:MPackage(m); break;
		}
	}

}


///////////// 操作模块 //////////////
void MSender(Manage &m)
{
	cout << "命令0：回到主菜单；" << endl;
	cout << "命令1：显示快递员信息；" << endl;
	cout << "命令2：显示快递员工作状态；" << endl;
	cout << "命令3：更改快递员工作状态。" << endl << endl;
	int op;
	cout << "请输入命令：";
	cin >> op;
	switch (op)
	{
	case 0:break;
	default:cout << "无法识别的命令！" << endl; break;
	case 1: {
		cout << "姓名： " << m.ApiWname() << endl; 
		cout << "电话： " << m.ApiWnumber() << endl;
		cout << "住址： " << m.ApiWaddress() << endl << endl;
		break;
	}
	case 2:cout << "工作状态： "; m.ApiWork();cout<< endl << endl;
	case 3:cout << "状态更改："; m.Change(); m.ApiWork(); cout << endl << endl;
	}
}

void MPackage(Manage &m)
{
	cout << "命令0：回到主菜单；" << endl;
	cout << "命令1：添加包裹；" << endl;
	cout << "命令2：查询包裹；" << endl;
	cout << "命令3：删除包裹；" << endl;
	cout << "命令4：更改包裹状态。" << endl << endl;
	int op;
	cout << "输入命令：";
	cin >> op;
	switch (op)
	{
	case 0:break;
	default:cout << "无法识别的命令！" << endl;	break;
	case 1:Mappend(m); break;
	case 2:Msearch(m); break;
	case 3:Mdelate(m); break;
	case 4:Mchange(m); break;
	}
}


void Mappend(Manage & m)
{
	Package newPack;
	string addressorname, addressorphone, addressoradd, recievername, recieverphone, recieveradd, id;
	double weight, cost;
	cout << "输入寄件人姓名：";
	cin >> addressorname;
	newPack.Setaddressorname(addressorname);
	cout << "输入寄件人电话：";
	cin >> addressorphone;
	newPack.Setaddressorphone(addressorphone);
	cout << "输入寄件人地址：";
	cin >> addressoradd;
	newPack.Setaddressorplace(addressoradd);
	cout << "输入收件人姓名：";
	cin >> recievername;
	newPack.Setreceivername(recievername);
	cout << "输入收件人电话：";
	cin >> recieverphone;
	newPack.Setreceiverphone(recieverphone);
	cout << "输入收件人地址：";
	cin >> recieveradd;
	newPack.Setreceiverplace(recieveradd);
	cout << "输入包裹编号：";
	cin >> id;
	newPack.SetID(id);
	cout << "输入包裹重量：";
	cin >> weight;
	newPack.Setweight(weight);
	cout << "输入包裹费用：";
	cin >> cost;
	newPack.SetCost(cost);
	m.Insert(newPack);
	cout << "添加成功！" << endl;
}

void Msearch(Manage & m)
{
	cout << "命令0：回到主菜单；" << endl;
	cout << "命令1：按编号查找；" << endl;
	cout << "命令2：按寄件人姓名查找；" << endl;
	cout << "命令3：按收件人姓名查找。" << endl << endl;
	cout << "输入命令：";
	int op;
	cin >> op;
	switch (op)
	{
	case 0:break;
	default:cout << "无法识别的命令！" << endl << endl; break;
	case 1: 
		{
			string id; 			
			cout << "输入编号：";
			cin >> id;
			while (id.size() != 10)
			{	
				cout << "错误！请校验快递编号！10位数字。" << endl;
				cin >> id;
			}
			if(m.Search(id))
				m.Print();
		}
		break;
	case 2: 
		{
			string name;
			cout << "输入姓名：";
			cin >> name;
			m.Search(1, name);
		}
		break;
	case 3:
		{
			string name;
			cout << "输入姓名：";
			cin >> name;
			m.Search(0, name);
		}
		break;
	}
}

void Mdelate(Manage & m)
{
	cout << "输入包裹编号：";
	string id;
	cin >> id;
	while (id.size() != 10)
	{
		cout << "错误！请校验快递编号！10位数字。" << endl;
		cin >> id;
	}
	if(m.Delete(id))
		cout<<"删除成功！\n";
}

void Mchange(Manage & m)
{
	cout << "输入包裹编号：";
	string id;
	cin >> id;
	while (id.size() != 10)
	{
		cout << "错误！请校验快递编号！10位数字。" << endl;
		cin >> id;
	}
	m.Works(id);
}