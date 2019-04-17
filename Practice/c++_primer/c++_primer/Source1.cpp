#include"first.h"
#include"second.h"
#include<time.h>
class Employee {
private:
	string name;
	int id;
	static int iter;
public:
	Employee() :id(iter++) {}
	Employee(string na) :name(na),id(iter++) {}
	Employee(const Employee& copy) {
		this->name = copy.name;
		this->id = iter++;
	}
	Employee& operator=(const Employee& copy) {
		if (&copy != this) {
			this->name = copy.name;
			this->id = iter++;
		}
		return *this;
	}
};
int Employee::iter = 0;
class HasPtr {
	//valuelike class
private:
	string *ps;
	int i;
public:
	friend void swap(HasPtr& first, HasPtr& second);
	//static bool operator<(const HasPtr& first,const HasPtr& second);
	HasPtr(const string& s = string()) :
		ps(new string(s)), i(0) {}
	HasPtr(const HasPtr& p) :
		ps(new string(*(p.ps))), i(p.i){}
	HasPtr& operator=(const HasPtr& p) {
		if (&p != this) {
			delete this->ps;
			this->ps = new string(*p.ps);
			this->i = p.i;
		}
		return *this;
	}
	~HasPtr() {
		delete ps;
	}
	string getStr()const {
		return *ps;
	}
};

inline void swap(HasPtr& first, HasPtr& second) {
	//using std::swap;
	swap(first.ps, second.ps);
	swap(first.i, second.i);
	cout << "Swap is activated" << endl;
}
bool lower(const HasPtr& first,const HasPtr& second) {
	return first.getStr() < second.getStr();
}
int main(void) {
	srand(time(NULL));
	fstream in("input.txt"), out1("output1.txt"), out2("output2.txt");
	if (!(in&&out1&&out2)) {
		cerr << "File open fail" << endl;
		return -1;
	}
	vector<HasPtr> ivec;
	for (int i = 0; i < 100; ++i)
		ivec.push_back(to_string(500-i));
	std::sort(ivec.begin(), ivec.end(), lower);
	for (auto j : ivec)
		cout << j.getStr() << ends;
	 
	in.close(); 
	out1.close();
	out2.close();
	system("pause");
	return 0;
}