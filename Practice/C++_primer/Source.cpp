#include"Header.h"

class Employee {
	string name;
	size_t id;
	static size_t count;
public:
	Employee() = default;
	Employee(const string& n) :name(n) {
		id = count++;
	}
	Employee& operator=(const Employee& copy) {
		if (&copy != this) {
			name = copy.name;
			id = count++;
		}
		return *this;
	}
	Employee(const Employee& copy) :name(copy.name) {
		id = count++;
	}
	~Employee() { --count; }
};
size_t Employee::count = 0;

class Foo {
public:
	Foo(initializer_list<int> a) {
		for (auto i : a)
			data.push_back(i);
	}
	Foo sorted() && {
		sort(data.begin(),data.end());
		return *this;
	};
	Foo sorted()const & {
		return Foo(*this).sorted();
	};
	
private:
	vector<int> data;
};

int main(){
	int i;
	double temp;
	cin >> i>>temp;
	cout << i << ends << temp << endl;

	system("pause");
	return 0;
}