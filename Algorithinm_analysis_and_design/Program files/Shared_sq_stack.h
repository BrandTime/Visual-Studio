//��ͷ�ļ�ʵ���˶��˳��ջ����ͬһ������ռ�
//����ÿһ����ջ��˵��δ��ʱ��������ͨջ��ͬ��
//ջ��ʱ�������߲��������δ����һ����ջ������ջ�Ŀռ����ѹһ��������������ǰջ
//����ջ��Ϊ1ʱ�ù���ջ������ͨջһ��ʹ��
//�����ڴ��������¸ù���ջ���ܵ�����ͨջʹ�ã�����һ��ȱ�ݣ����cur��topsizeΪ��̬��Ա����
//����ζ����Դ�����о���ֻ��һ������ջ������ж������ջʱ���ܻ����
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
	//����������ջջ��(second)��ջ��(first)����Ϣ,
	//����Ϣ���ڴ�ջ�е��±�
	static int cur;//cur��ʾĬ�ϲ����cur��ջ
	int totalsize;
	static int topsize;//��ʾ��ջ�ĸ���
	void Initop(int n);
	void Move(int i,bool direc);
	//direct ������ʾ����true����ƣ�false��ǰ��
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
//���ܵ�������з��䲢�����е�һ����ջ�в���Ԫ��,n��ʾ�����黮��Ϊn��ջ
//i��ʾ�����i��ջ�У�elem��ʾҪ�����Ԫ��
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
//�ж������������Ƿ�װ��
template<class Elem>
bool Shared_stack<Elem>::Totalfull()const {
	for (int i = 1; i <= topsize; ++i) 
		if (!Curfull(i))
			return false;
	return true;
}
//�жϵ�i��ջ�Ƿ�װ����������ĩβ�Ķ�������ռ�Ĭ��Ϊ���һ��ջ�Ŀռ�
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

//�ж���һ�β���Ӧ�ò���ڼ���ջ�У���ʱ��ǰջ������,
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
//�õ�����������ĳ���
template<class Elem>
int Shared_stack<Elem>::Getotalength()const {
	return totalsize;
}
//�õ���ǰ��ջ�ĳ���
template<class Elem>
int Shared_stack<Elem>::Getcurlength()const {
	return top[cur-1].second - top[cur-1].first + 1;
}
//��ʼ����¼����ջ��ָ�������
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
//����i��ջ�е�Ԫ��ȫ������ƶ�һλ����ѹ��i����ջ�Ŀռ�)
//��ȷ���п����ƶ��Ŀռ�ʱ�ŵ��ô˺������ú��������пռ��Ƿ������ж�
template<class Elem>
void Shared_stack<Elem>::Move(int i,bool direct) {
	int j;
	if (direct)
		for (; i != cur; --i) {
			//�����ǰ�ƶ���ջΪ�գ���Ϊsecondָ��Ϊ-1����ֱ���ƶ�firstָ�뼴��
			++top[i - 1].first;
			if (!Small_stack_empty(i))
				for (j=++top[i-1].second; j != top[i-1].first; --j)
					array[j] = array[j - 1];
		}
	else {
		//��ǰ�ƶ�ʱ��nextempty�ĺ�һ��ջ��ʼ�ƶ�
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
//���Դ���
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