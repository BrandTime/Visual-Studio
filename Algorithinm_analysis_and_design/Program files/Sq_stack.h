#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include<iostream>
#include<stdexcept>
#include<string>
using namespace std;
const int DEFAULT_SIZE = 1000;

template<class Elem>
class Sq_stack {
	Elem *array;
	int top;
	int size;
	bool Full()const;
	void Init(int len = DEFAULT_SIZE);
public:
	Sq_stack();
	Sq_stack(int len);
	Sq_stack(const Sq_stack<Elem>& copy);
	Sq_stack<Elem>& operator=(const Sq_stack<Elem>& copy);
	void Clear();
	virtual ~Sq_stack();
	bool Empty()const;
	int Getlength()const;
	bool Push(const Elem& elem);
	bool Pop(Elem& elem);
	auto Top()const;
	void Print();
	//void Traverse(const Elem& (*Top)(Elem& elem))const;
};

template<class Elem>
void Sq_stack<Elem>::Print() {
	if (!top)
		return;
	for (int i = 0; i < top; i++) {
		cout << array[i] << endl;
	}
	return;
}
template<class Elem>
auto Sq_stack<Elem>::Top()const {
	if (top) {
		return array[top - 1];
	}
	else
		throw runtime_error("");
}
template<class Elem>
bool Sq_stack<Elem>::Pop(Elem& elem) {
	if (!top) {
		elem = array[top--];
		return true;
	}
	else
		return false;
}
template<class Elem>
bool Sq_stack<Elem>::Push(const Elem& elem) {
	if (!Full()) {
		array[top++] = elem;
		return true;
	}
	else
		return false;
}
template<class Elem>
int Sq_stack<Elem>::Getlength()const {
	return top;
}
template<class Elem>
bool Sq_stack<Elem>::Empty()const {
	return top == 0;
}
template<class Elem>
bool Sq_stack<Elem>::Full()const {
	return top == size;
}
template<class Elem>
Sq_stack<Elem>::~Sq_stack() {
	Clear();
}
template<class Elem>
void Sq_stack<Elem>::Clear() {
	if (array) {
		delete[] array;
		array = nullptr;
		top = 0;
		size = 0;
	}

	return;
}
template<class Elem>
Sq_stack<Elem>& Sq_stack<Elem>::operator=(const Sq_stack<Elem>& copy) {
	if (&copy != this) {
		Init(copy.size);
		for (int i = 0; i < copy.top; ++i)
			array[top++] = copy.array[i];
	}
	return *this;
}
template<class Elem>
Sq_stack<Elem>::Sq_stack(const Sq_stack<Elem>& copy) {
	Init(copy.size);
	for (int i = 0; i < copy.top; ++i)
		array[top++] = copy.array[i];
}
template<class Elem>
Sq_stack<Elem>::Sq_stack(int len) {
	Init(len);
}
template<class Elem>
Sq_stack<Elem>::Sq_stack() {
	Init();
}
template<class Elem>
void Sq_stack<Elem>::Init(int len) {
	Clear();
	size = len;
	top = 0;
	array = new Elem[len + 1];//多余的一个空间用来判断栈满
	if (!array)
		throw runtime_error("空间不足，无法分配空间");
	return;
}
#if 0
//调试代码
Sq_stack<int> stack;
int temp, i;
for (i = 0; i < 20; i++)
	stack.Push(i);
cout << "the Top element  " << stack.Top() << endl;
stack.Print();
cout << endl;
Sq_stack<int> copy(stack), copy1;
copy.Print();
cout << endl;
copy1 = stack;
copy1.Print();
cout << endl;
#endif



#endif // HEADER_H_INCLUDED