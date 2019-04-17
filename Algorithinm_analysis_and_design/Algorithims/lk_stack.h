#ifndef _HEADER_H_
#define _HEADER_H_
#include<iostream>
#include<string>
using namespace std;

template<class fir, class sec>
class Pair {
public:
	fir first;
	sec second;
	Pair<fir, sec>() {}
	Pair<fir, sec>(fir m_first, sec m_second) : first(m_first), second(m_second) {}
	friend ostream&operator<<(ostream& out, const Pair<fir, sec>& ori) {
		out << ori.first;
		return out;
	}
};
template<class Elem>
class Stack;
template<class Elem>
class Node {
	friend class Stack<Elem>;
private:
	Elem m_elem;
	Node<Elem> *next;
public:
	Node() :next(nullptr) {}
	Node(const Elem &elem) :m_elem(elem), next(nullptr) {}
	friend ostream& operator<<(ostream& out, const Node<Elem>& ori) {
		out << ori.m_elem;
		return out;
	}
};
template<class Elem>
class Stack {
protected:
	int length;
	Node<Elem> *top;
public:
	Stack();
	Stack(const Stack<Elem>& copy);
	Stack<Elem>& operator=(const Stack<Elem>& copy);
	virtual ~Stack();
	int Getlength()const;
	bool Empty()const;
	void Clear();
	bool Push(const Elem& elem);
	bool Pop(Elem& elem);
	Elem Top()const;
	void Print()const;
};


template<class first, class second>
Pair<first, second>& Make_pair(first m_first, second m_second) {
	Pair<first, second> *m_pair = new Pair<first, second>(m_first, m_second);
	return *m_pair;
}
template<class Elem>
void Stack<Elem> ::Print()const {
	Stack<Elem> temp;
	auto point = top;
	for (; point != nullptr; point = point->next)
		temp.Push(point->m_elem);
	for (point = temp.top; point != nullptr; point = point->next)
		cout << *point << endl;

	return;
}
template<class Elem>
Elem Stack<Elem>::Top()const {
	return top->m_elem;
}
template<class Elem>
bool Stack<Elem>::Pop(Elem& elem) {
	if (top) {
		elem = top->m_elem;
		Node<Elem> *temp = top;
		if (top->next)
			top = top->next;
		else
			top = nullptr;
		delete temp;
		length = (length - 1 < 0) ? 0 : (length - 1);
		return true;
	}
	else
		return false;
}
template<class Elem>
bool Stack<Elem>::Push(const Elem& elem) {
	Node<Elem> *temp = new Node<Elem>(elem);
	if (!temp)
		return false;
	if (top)
		temp->next = top;
	else
		temp->next = nullptr;
	top = temp;
	length++;
	return true;
}
template<class Elem>
void Stack<Elem>::Clear() {
	for (int i = 0; i < length; i++) {
		Elem temp;
		Pop(temp);
	}
	length = 0;
}
template<class Elem>
bool Stack<Elem>::Empty()const {
	return length == 0;
}
template<class Elem>
int Stack<Elem>::Getlength()const {
	return length;
}
template<class Elem>
Stack<Elem>& Stack<Elem>::operator=(const Stack<Elem>& copy) {
	if (this != &copy) {
		Clear();
		length = copy.length;
		auto temp = copy.top;
		for (temp; temp != nullptr; temp = temp->next) {
			Elem elem = temp->m_elem;
			Push(elem);
		}
	}
	return *this;
}
template<class Elem>
Stack<Elem>::Stack(const Stack<Elem>& copy) {
	Clear();
	length = copy.length;
	auto temp = copy.top;
	for (temp; temp != nullptr; temp = temp->next) {
		Elem elem = temp->m_elem;
		Push(elem);
	}
}
template<class Elem>
Stack<Elem>::Stack() :top(nullptr), length(0) {}
template<class Elem>
Stack<Elem>::~Stack() {
	Clear();
}

#if 0
//Debugger
Stack<int> stack;
int temp, i;
for (i = 0; i < 20; i++)
	stack.Push(i);
cout << "the Top element  " << stack.Top() << endl;
stack.Print();
cout << endl;
Stack<int> copy(stack), copy1;
copy.Print();
cout << endl;
copy1 = stack;
copy1.Print();
cout << endl;
#endif
#endif
