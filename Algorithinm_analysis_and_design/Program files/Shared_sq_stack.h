//该头文件实现了多个顺序栈共享同一个数组空间
//对于每一个子栈来说：未满时操作与普通栈相同，
//栈满时就向两边查找最近的未满的一个子栈，将该栈的空间向后挤压一个出来供给给当前栈
//当子栈数为1时该共享栈能像普通栈一样使用
//尽管在大多数情况下该共享栈都能当做普通栈使用，但有一个缺陷：类的cur和topsize为静态成员变量
//这意味着在源程序中尽量只有一个共享栈，如果有多个共享栈时可能会出错
#ifndef _SHARED_STACK_INCLUDED
#define _SHARED_STACK_INCLUDED
#include<iostream>
#include<string>
#include<algorithm>
#include<stdexcept>
using namespace std;
const int DEFAULTSIZE = 6;

template<class Elem>
class Shared_stack {
private:
	Elem *array;
	pair<int, int> *top;
	//用来储存子栈栈顶(second)和栈底(first)的信息,
	//该信息是在大栈中的下标
	static int cur;//cur表示默认插入第cur个栈
	int totalsize;
	static int topsize;//表示子栈的个数
	void Initop(int n);
	void Move(int i,bool direc);
	//direct 用来表示方向，true向后移，false向前移
	int Pushelp();
public:
	Shared_stack(int size = DEFAULTSIZE);
	Shared_stack(const Shared_stack<Elem>& copy);
	Shared_stack<Elem>& operator=(const Shared_stack<Elem>& copy);
	~Shared_stack();
	void Clear();
	bool Push(const Elem& elem,int i=cur,int n=topsize );
	auto Top(int i = cur)const;
	void Pop(Elem& elem,int i = cur);
	int Getcurlength()const;
	int Getotalength()const;
	int Getopsize()const;
	bool Curfull(int i=cur)const;
	bool Totalfull()const;
	bool Small_stack_empty(int i=cur)const;
	void Print()const;
};



template<class Elem>
int Shared_stack<Elem>::cur = 1;
template<class Elem>
int Shared_stack<Elem>::topsize = 1;
template<class Elem>
bool Shared_stack<Elem>::Small_stack_empty(int i)const {
	return top[i - 1].second == -1;
}
//Print all elements in the array
template<class Elem>
void Shared_stack<Elem>::Print()const {
	for (int i = 1;i<=topsize; ++i) {
		cout << "*";
		if (Small_stack_empty(i))
			cout << " ";
		else
			for (int j = top[i-1].first; j <= top[i-1].second; ++j)
				cout << array[j] << " ";
		cout << "*\t";
	}
	cout << endl;

	return;
}
template<class Elem>
void Shared_stack<Elem>::Pop(Elem& elem,int i) {
	if (i <= 0 || i > topsize)
		throw runtime_error("beyond the correct interval");
	else if (top[i - 1].second == top[i - 1].first) {
		elem = array[top[i - 1].second];
		top[i - 1].second = -1;
	}
	else
		elem = array[top[i-1].second--];
	return;
}
//对总的数组进行分配并在其中的一个子栈中插入元素,n表示将数组划分为n个栈
//i表示插入第i个栈中，elem表示要插入的元素
template<class Elem>
bool Shared_stack<Elem>::Push(const Elem& elem,int i,int n) {
	cur = i;
	if(topsize==1&&Small_stack_empty(1))
		Initop(n);
	if (Totalfull())
		throw runtime_error("no space");
	if (!Curfull(cur)) {
		if (Small_stack_empty(cur)) {
			top[cur-1].second = top[cur-1].first;
			if (cur != topsize&&top[cur].first == top[cur - 1].first) {
				int nextempty = Pushelp();
				if (!Small_stack_empty(nextempty))
					return false;
				else 
					Move(nextempty, (nextempty - cur));
			}
			array[top[cur-1].second] = elem;
		}
		else
			array[++top[cur-1].second] = elem;
	}
	else {
		int nextempty= Pushelp();
		if (!Small_stack_empty(nextempty))
			return false;
		else {
			Move(nextempty,(nextempty-cur));
			array[++top[cur-1].second] = elem;
		}
	}

	return true;
}
//判断整个大数组是否装满
template<class Elem>
bool Shared_stack<Elem>::Totalfull()const {
	for (int i = 1; i <= topsize; ++i) 
		if (!Curfull(i))
			return false;
	return true;
}
//判断第i个栈是否装满，将数组末尾的多余零碎空间默认为最后一个栈的空间
template<class Elem>
bool Shared_stack<Elem>::Curfull(int i)const {
	if (i <= 0 || i > topsize)
		throw runtime_error("beyond the correct interval");
	else if (i == topsize)
		return totalsize - 1 == top[i - 1].second;
	else if (Small_stack_empty(i))
		return false;
	else
		return top[i-1].second+1== top[i].first;
}

//判断下一次插入应该插入第几个栈中（此时当前栈已满）,
//return the number of the nextpush,if the totalarray is full,return -1;
template<class Elem>
int Shared_stack<Elem>::Pushelp() {
	int right_empty, left_empty;
	for (right_empty = cur + 1; right_empty != topsize + 1; ++right_empty)
		if (!Curfull(right_empty))
			break;
	for (left_empty = cur - 1; left_empty != 0; --left_empty)
		if (!Curfull(left_empty))
			break;
	if (left_empty == 0 && right_empty == topsize + 1)
		return -1;
	else if (left_empty == 0 && right_empty != topsize + 1)
		return right_empty;
	else if (right_empty == topsize + 1 && left_empty != 0)
		return left_empty;
	else
		return ((cur - left_empty) < (right_empty - cur)) ? left_empty : right_empty;
}
template<class Elem>
auto Shared_stack<Elem>::Top(int i)const {
	if (i <= 0 || i > topsize)
		throw runtime_error("beyond the correct interval");
	if (Small_stack_empty(i))
		throw runtime_error("this stack is empty");
	else
		return array[top[i-1].second];
}
//get the number of small stack
template<class Elem>
int Shared_stack<Elem>::Getopsize()const {
	return topsize;
}
//得到整个大数组的长度
template<class Elem>
int Shared_stack<Elem>::Getotalength()const {
	return totalsize;
}
//得到当前子栈的长度
template<class Elem>
int Shared_stack<Elem>::Getcurlength()const {
	return top[cur-1].second - top[cur-1].first + 1;
}
//初始化记录所有栈顶指针的数组
template<class Elem>
void Shared_stack<Elem>::Initop(int n) {
	delete[] top;
	top = new pair<int,int>[n];
	topsize = n;
	cur = 1;
	for (int i = 1; i <= n; ++i) {
		top[i-1].first = i*(totalsize / n);
		top[i-1].second =-1;//-1 stands for empty
	}

	return;
}
//将第i个栈中的元素全部向后移动一位（挤压第i个子栈的空间)
//当确认有可以移动的空间时才调用此函数，该函数不进行空间是否充足的判断
template<class Elem>
void Shared_stack<Elem>::Move(int i,bool direct) {
	int j;
	if (direct)
		for (; i != cur; --i) {
			//如果当前移动的栈为空，因为second指针为-1，故直接移动first指针即可
			++top[i - 1].first;
			if (!Small_stack_empty(i))
				for (j=++top[i-1].second; j != top[i-1].first; --j)
					array[j] = array[j - 1];
		}
	else {
		//向前移动时从nextempty的后一个栈开始移动
		for (++i; i != cur; ++i) {
			--top[i - 1].first;
			if (!Small_stack_empty(i))
				for (j = top[i - 1].first; j != top[i - 1].second; ++j)
					array[j] = array[j +1];
		}
	}

	return;
}
template<class Elem>
Shared_stack<Elem>& Shared_stack<Elem>::operator=(const Shared_stack<Elem>& copy) {
	if (&copy != this) {
		Clear();
		totalsize = copy.Getotalength();
		array = new Elem[totalsize];
		Initop(copy.Getopsize());
		cur = copy.cur;
		for (int i = 0; i < totalsize; ++i)
			array[i] = copy.array[i];
		for (int i = 1; i <= topsize; ++i)
			top[i-1] = copy.top[i-1];
	}
	return *this;
}
template<class Elem>
Shared_stack<Elem>::Shared_stack(const Shared_stack<Elem>& copy) {
	Clear();
	totalsize = copy.Getotalength();
	array = new Elem[totalsize];
	Initop(copy.Getopsize());
	cur = copy.cur;
	for (int i = 0; i < totalsize; ++i)
		array[i] = copy.array[i];
	for (int i = 1; i <=topsize; ++i)
		top[i-1].second = copy.top[i-1].second;
}
template<class Elem>
Shared_stack<Elem>::Shared_stack(int m_size) {
	array = new Elem[m_size];
	totalsize = m_size;
	top = nullptr;
	Initop(1);
}
template<class Elem>
void Shared_stack<Elem>::Clear() {
	if (array) {
		delete[] array;
		delete[] top;
		totalsize = 0;
		top = nullptr;
		array = nullptr;
		topsize = 1;
		cur = 1;
	}
	return;
}
template<class Elem>
Shared_stack<Elem>::~Shared_stack() {
	Clear();
}

#if 0
//调试代码
#include"Shared_stack.h"
int main(void) {

	try {
		Shared_stack<int> stack;
		int temp;
		stack.Push(1, 4, 1);
		cout << stack.Top() << endl;
		stack.Push(2, 1);
		cout << stack.Top() << endl;
		stack.Push(3, 4);
		cout << stack.Top() << endl;
		stack.Print();
		cout << endl;
		cout << stack.Top() << endl << endl;
		for (int i = 5; i < 9; ++i)
			stack.Push(i, 4, 4);
		stack.Print();
		cout << endl;
		while (!stack.Small_stack_empty())
			stack.Pop(temp);
		stack.Print();
		cout << endl;
		Shared_stack<int> copy(stack), copy1;
		copy.Print();
		cout << endl;
		copy1 = stack;
		copy1.Print();
		cout << endl;
		cout << "the total small stack number " << copy1.Getopsize() << endl;
		cout << "the current small stack length " << copy1.Getcurlength() << endl;
		copy.Clear();
		copy1.Clear();
	}
	catch (const runtime_error& error) {
		cout << error.what() << endl;
	}

	//system("PAUSE");
	return 0;
}
#endif

#endif