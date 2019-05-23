﻿#include"HasPtr.hpp"

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

int main() {
	HasPtr has("temp");
	has = has;

	system("pause");
	return 0;
}