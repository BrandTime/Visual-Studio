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

class Person										//�շ�����
{
public:
	Person() {};
	void SetName(string name) { this->Name = name; }						//�趨����
	void SetAddress(string address) { this->Address = address; }			//�趨��ַ
	void SetNumber(string number) { this->Pnumber = number; }		//�趨�绰
	string ApiName() { return Name; }													//��������
	string ApiAddress() { return Address; }											//���ص�ַ
	string ApiNumber() { return Pnumber; }											//���ص绰
private:
	string Name;		//����
	string Address;		//��ַ
	string Pnumber;		//�绰
};

class Package									//������
{
public:
	Package() { this->status = put_in_storage; }
	void Setaddressorname(string name) { Addressor.SetName(name); }				//�趨 �ļ�������
	void Setaddressorphone(string phone) {															//�趨 �ļ��˵绰
		while (phone.size()!=11)
		{
			cout << "������У��绰��11λ���֡���" << endl;
			cin >> phone;
		}
		Addressor.SetNumber(phone); 
	}		
	void Setaddressorplace(string address) { Addressor.SetAddress(address); }	//�趨 �ļ��˵�ַ
	void Setreceivername(string name) { Reciever.SetName(name); }					//�趨 �ռ�������
	void Setreceiverphone(string phone) {															//�趨 �ռ��˵绰	
		while (phone.size() != 11)
		{
			cout << "������У��绰��11λ���֡���" << endl;
			cin >> phone;
		}
		Reciever.SetNumber(phone); 
	}			
	void Setreceiverplace(string address) { Reciever.SetAddress(address); }			//�趨 �ռ��˵�ַ
	void SetCost(double cost) { this->Cost = cost; }												//�趨����
	void SetID(string id) { 																						//�趨���
		while (id.size()!=10)	
		{
			cout << "������У���ݱ�ţ�10λ���֡�" << endl;
			cin >> id;
		}
		this->ID = id;
	}															
	void Setweight(double weight) { this->Weight = weight; }								//�趨����
	void SetStatus(Status s);																					//�趨���״̬
	string ApiRname() { return(Reciever.ApiName()); }											//�����ռ�������
	string ApiAname() { return(Addressor.ApiName()); }										//���ؼļ�������
	string ApiID() { return ID; }																				//���ر��
	double ApiCost() { return Cost; }																		//���ط���
	double ApiWeight() { return Weight; }																//��������
	Status ApiS() { return status; }																			//���ذ���״̬
	void Print();																										//��ʾ�������ȫ����Ϣ
private:
	Status status;
	Person Reciever;
	Person Addressor;
	string ID;
	double Cost;
	double Weight;
};

class Pack														//����Ԫ
{
public:
	Package p;
	Pack *next;
	Pack *pre;
	bool f;																										//��ʾ��ǰ������״̬��true��ʾ�ѱ����ҹ�
	void Ref()																								//��ת��ǰ����״̬
	{
		f = (f == false) ? true : false;
	}
	Pack(Package &p1)
	{
		p = p1;
		next = pre = NULL;
		f = false;
	}
};																			//����f

class Package_list													//����������洢��
{
private:
	Pack *cur;
	Pack *head;
	int num;																											//��ǰ���͵İ�������
	bool F;																									//��ǰ��ݵ�״̬
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
	bool Insert(Package p1);																						//�½�����
	bool Delete(string id);																							//ɾ������
	bool Search(bool i, string a);																				//i=false��ʾ���ռ��˽��в��ң�i=true��ʾ�÷����˽��в��ң������string ���ռ��˻�ļ��˵�����
	bool Search(string id);																							//�ñ�Ž�������
	bool Print();																									//��ʾ��ǰ���״̬
	int Getnum();
	void Re();                                                                                                      //��ת�������а����Ĳ�ѯ״̬
	void StatusUP(string id);																																			//��õ�ǰ���״̬
};

class Sender :public Package_list								//�ʵ�Ա��
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
	void Works(string id);															//������䵽��һ����
	void Change() { Work = !Work; }											//�ı���Ա�Ĺ���״̬
	void ApiWork() { if (Work) cout << "�����С�"; else cout << "�ݼ��С�"; cout << endl << endl; }						//���ؿ��Ա����״̬
	string ApiWname() { return (Worker.ApiName()); }				//���ؿ��Ա����
	string ApiWnumber() { return (Worker.ApiNumber()); }		//���ؿ��Ա�绰
	string ApiWaddress() { return (Worker.ApiAddress()); }		//���ؿ��Ա��ַ
private:
	Person Worker;
	bool Work;
};

class Manage :public Sender									//������
{
public:
	Sender *s1, *s2;
	Manage() { s1 = new Sender; s2 = new Sender; };
};

// Package�� //

void Package::SetStatus(Status s)
{
	this->status = s;
}

void Package::Print()												//��ʾ�������ȫ����Ϣ
{
	cout << "�ļ��������� " << ApiAname() << endl;
	cout << "�ļ��˵绰�� " << Addressor.ApiNumber() << endl;
	cout << "�ļ��˵�ַ�� " << Addressor.ApiAddress() << endl << endl;
	cout << "�ռ��������� " << ApiRname() << endl;
	cout << "�ռ��˵绰�� " << Reciever.ApiNumber() << endl;
	cout << "�ռ��˵�ַ�� " << Reciever.ApiAddress() << endl << endl;
	cout << "��ţ� " << ApiID() << endl;
	cout << "���ã� " << ApiCost() << endl;
	cout << "������ " << ApiWeight() << endl << endl;
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
	case 0:cur->p.SetStatus(put_in_storage); cout << "�����Ѿ����" << endl; break;
	case 1:cur->p.SetStatus(has_been_sent); cout << "�����Ѿ�ȡ��" << endl; break;
	case 2:cur->p.SetStatus(on_the_road); cout << "��������·��" << endl; break;
	case 3:cur->p.SetStatus(arrive_in_storage); cout << "�����Ѿ��ʹ�ֿ�" << endl; break;
	case 4:cur->p.SetStatus(is_sending); cout << "������ʼ����" << endl; break;
	default:
	case 5:cur->p.SetStatus(sign_in); cout << "������ǩ��" << endl; break;
	}
}


// Package_list�� //

int Package_list::Getnum()
{
	return num;
}

bool Package_list::Insert(Package p1)
{
	Pack *temp = new Pack(p1);
	if (!temp)
	{
		cout << "����ռ�ʧ�ܣ�\n";
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
		cout << "�ް�����\n";
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
		cout << "�ް�����\n";
		return false;
	}
	cur->p.Print();
	return true;
}
bool Package_list::Search(bool i, string a)
{
	if (!head)
	{
		cout << "�ް�����\n";
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
		cout << "�ް�����\n";
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

// sender�� //

void Sender::Works(string id)
{
	Search(id);
	StatusUP(id);
}


// ����ģ�� //
void MSender(Manage &m);               //�Կ��Ա����
void MPackage(Manage &m);				//�԰�������
void Mappend(Manage &m);				//��Ӱ���
void Msearch(Manage &m);				//��ѯ����
void Mdelate(Manage &m);				//ɾ������
void Mchange(Manage &m);				//���İ���״̬

int main()
{
	Manage m;
	int ops;
	cout << "��ӭ�����ݹ���ϵͳ��" << endl << endl;
	while (1)
	{
		cout << "����1���Կ��Ա����" << endl;
		cout << "����2���԰�������" << endl;
		cout << "����0���˳�ϵͳ��" << endl << endl;
		cout << "���������";
		cin >> ops;
		switch (ops)
		{
		default:cout << "�޷�ʶ������" << endl << endl; break;
		case 0: {
			cout << "���˳�ϵͳ��" << endl;
			return 0;
		}
		case 1:MSender(m); break;
		case 2:MPackage(m); break;
		}
	}

}


///////////// ����ģ�� //////////////
void MSender(Manage &m)
{
	cout << "����0���ص����˵���" << endl;
	cout << "����1����ʾ���Ա��Ϣ��" << endl;
	cout << "����2����ʾ���Ա����״̬��" << endl;
	cout << "����3�����Ŀ��Ա����״̬��" << endl << endl;
	int op;
	cout << "���������";
	cin >> op;
	switch (op)
	{
	case 0:break;
	default:cout << "�޷�ʶ������" << endl; break;
	case 1: {
		cout << "������ " << m.ApiWname() << endl; 
		cout << "�绰�� " << m.ApiWnumber() << endl;
		cout << "סַ�� " << m.ApiWaddress() << endl << endl;
		break;
	}
	case 2:cout << "����״̬�� "; m.ApiWork();cout<< endl << endl;
	case 3:cout << "״̬���ģ�"; m.Change(); m.ApiWork(); cout << endl << endl;
	}
}

void MPackage(Manage &m)
{
	cout << "����0���ص����˵���" << endl;
	cout << "����1����Ӱ�����" << endl;
	cout << "����2����ѯ������" << endl;
	cout << "����3��ɾ��������" << endl;
	cout << "����4�����İ���״̬��" << endl << endl;
	int op;
	cout << "�������";
	cin >> op;
	switch (op)
	{
	case 0:break;
	default:cout << "�޷�ʶ������" << endl;	break;
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
	cout << "����ļ���������";
	cin >> addressorname;
	newPack.Setaddressorname(addressorname);
	cout << "����ļ��˵绰��";
	cin >> addressorphone;
	newPack.Setaddressorphone(addressorphone);
	cout << "����ļ��˵�ַ��";
	cin >> addressoradd;
	newPack.Setaddressorplace(addressoradd);
	cout << "�����ռ���������";
	cin >> recievername;
	newPack.Setreceivername(recievername);
	cout << "�����ռ��˵绰��";
	cin >> recieverphone;
	newPack.Setreceiverphone(recieverphone);
	cout << "�����ռ��˵�ַ��";
	cin >> recieveradd;
	newPack.Setreceiverplace(recieveradd);
	cout << "���������ţ�";
	cin >> id;
	newPack.SetID(id);
	cout << "�������������";
	cin >> weight;
	newPack.Setweight(weight);
	cout << "����������ã�";
	cin >> cost;
	newPack.SetCost(cost);
	m.Insert(newPack);
	cout << "��ӳɹ���" << endl;
}

void Msearch(Manage & m)
{
	cout << "����0���ص����˵���" << endl;
	cout << "����1������Ų��ң�" << endl;
	cout << "����2�����ļ����������ң�" << endl;
	cout << "����3�����ռ����������ҡ�" << endl << endl;
	cout << "�������";
	int op;
	cin >> op;
	switch (op)
	{
	case 0:break;
	default:cout << "�޷�ʶ������" << endl << endl; break;
	case 1: 
		{
			string id; 			
			cout << "�����ţ�";
			cin >> id;
			while (id.size() != 10)
			{	
				cout << "������У���ݱ�ţ�10λ���֡�" << endl;
				cin >> id;
			}
			if(m.Search(id))
				m.Print();
		}
		break;
	case 2: 
		{
			string name;
			cout << "����������";
			cin >> name;
			m.Search(1, name);
		}
		break;
	case 3:
		{
			string name;
			cout << "����������";
			cin >> name;
			m.Search(0, name);
		}
		break;
	}
}

void Mdelate(Manage & m)
{
	cout << "���������ţ�";
	string id;
	cin >> id;
	while (id.size() != 10)
	{
		cout << "������У���ݱ�ţ�10λ���֡�" << endl;
		cin >> id;
	}
	if(m.Delete(id))
		cout<<"ɾ���ɹ���\n";
}

void Mchange(Manage & m)
{
	cout << "���������ţ�";
	string id;
	cin >> id;
	while (id.size() != 10)
	{
		cout << "������У���ݱ�ţ�10λ���֡�" << endl;
		cin >> id;
	}
	m.Works(id);
}