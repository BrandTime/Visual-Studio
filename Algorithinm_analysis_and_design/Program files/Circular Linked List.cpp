//该循环链表是无头结点和尾指针的双链表
#include<iostream>
#include<cstdlib>
#include"D:\OneDrive\program files\utility.h"
#define MAX_SIZE 10000
using namespace std;
//面向程序员，所有的position从0开始，和数组兼容
template< class Elem>
class Node
{
public:
	Elem data;
	class Node<Elem> *next;
	class Node<Elem> *prev;
	Node(Elem it = 0)
	{
		next = prev = NULL;
		data = it;
	}
	~Node()
	{
		next = prev = NULL;
	}
};
template< class Elem>
class DList
{
public:
    DList()
    {
        head=NULL;
        cur=head;
        length=0;
    }
	DList(DList<Elem> &copy);
	~DList();
	bool Clear();
    bool SetStart();
    bool SetEnd();
    bool SetPos(int pos);
    bool Next();
    bool Prev();
    bool Delete(Elem &it);
    bool Insert(const Elem &it);
    bool Append(const Elem &it);
    bool GetValue(Elem &it);
	bool Empty();
    int GetLength()const;
    bool Print()const;
	Elem &operator[](int i);
private:
    Node<Elem> *head;
    Node<Elem> *cur;
    int length;
};

#if 0
int main(void)
{
    DList<char> list;
    char elem;
    int i;
    for(i=0;i<10;i++)
    {
        elem=rand()%100;
        list.Append(elem);
        list.Print();
    }
    list.SetPos(list.GetLength()/2);
    list.Print();
    list.Insert(99);
    list.Print();
    list.Next();
    list.Print();
    list.Insert(100);
    list.Print();
    list.Prev();
    list.Print();
    list.Delete(elem);
    list.Print();
    list.Append(101);
    list.Print();
    list.SetEnd();
    list.Print();
    list.Delete(elem);
    list.Print();

    return 0;
}
#endif

template<class Elem>
DList<Elem>::~DList() {
	Clear();
}
template<class Elem>
int DList<Elem>::GetLength()const
{
    return length;
}
template< class Elem>
bool DList<Elem>::GetValue(Elem &it)
{
    if(!head)
        return false;
    it=cur->data;
    return true;
}
template< class Elem>
bool DList<Elem>::SetStart()
{
    if(!head)
        return false;
    cur=head;
    return true;
}
template< class Elem>
bool DList<Elem>::SetEnd()
{
    if(!head)
        return false;
    cur=head->prev;
    return true;
}
template< class Elem>
bool DList<Elem>::SetPos(int it)
{
    if(!head||(it+1>length))
        return false;
    int i;
    Node<Elem> *temp=head;
    for(i=0;i<it;i++)
        temp=temp->next;
    cur=temp;
    return true;
}
template< class Elem>
bool DList<Elem>::Next()
{
    if(!head)
        return false;
    cur=cur->next;
    //if(head==cur)
        //cout<<"回到了第一个结点："<<endl;
    return true;
}
template< class Elem>
bool DList<Elem>::Prev()
{
    if(!head)
        return false;
    cur=cur->prev;
    if(head==cur)
        cout<<"回到了第一个结点："<<endl;
    return true;
}
template< class Elem>
bool DList<Elem>::Print()const
{
    if(!head)
        return false;
    Node<Elem> *temp=head;
    if(1==length)
    {
        cout<<"<*"<<temp->data<<">"<<endl;
        return true;
    }
    cout<<"<";
    while(temp!=cur)
    {
        cout<<temp->data<<"  ";
        temp=temp->next;
    }
    cout<<"*";
    while(temp->next!=head)
    {
        cout<<temp->data<<"  ";
        temp=temp->next;
    }
    cout<<temp->data<<"  ";
    cout<<">\n";
    return true;
}
template< class Elem>
bool DList<Elem>::Insert(const Elem &it)
{
    if(length>=MAX_SIZE)
        return false;
    Node<Elem> *temp=new Node<Elem>(it);
    if(!temp)
        return false;
    if(!head)
    {
        cur=temp;
        head=temp;
        cur->next=cur;
        cur->prev=cur;
    }
    else
    {
        temp->next=cur->next;
		cur->next->prev = temp;
        temp->prev=cur;
        cur->next=temp;
    }
    length++;
    return true;
}
template< class Elem>
bool DList<Elem>::Append(const Elem &it)
{
    if(length>=MAX_SIZE)
        return false;
    Node<Elem> *temp=new Node<Elem>(it);
    if(!temp)
        return false;
    if(!head)
    {
        head=temp;
        head->next=head;
        head->prev=head;
        cur=head;
    }
    else
    {
        temp->next=head;
        temp->prev=head->prev;
        head->prev->next=temp;
        head->prev=temp;
    }
    length++;
    return true;
}
template< class Elem>
bool DList<Elem>::Delete(Elem &it)
{
    if(!head)
        return false;
    Node<Elem> *temp=cur;
    it=temp->data;
    if(head==cur)
        head=cur->next;
    cur->prev->next=cur->next;
    cur->next->prev=cur->prev;
    cur=cur->next;
    delete temp;
    length--;
    return true;
}
template<class Elem>
bool DList<Elem>::Clear() {
	if (head)
	{
		Node<Elem> *temp;
		cur = head->next;
		if (length>1)
			do
			{
				temp = cur;
				cur = cur->next;
				delete temp;
			} while (cur != head);
			temp = cur;
			cur = cur->next;
			delete temp;
			cur = head = NULL;
			length = 0;
	}
	return true;
}
template<class Elem>
Elem& DList<Elem>::operator[](int i) {
	//此时采用的下标与数组类似
	if(!head)
		throw Error("链表并未建立！");
	if (i >= length || i < 0)
		throw Error("下标错误，超界");
	SetPos(i);
	return cur->data;
}
template<class Elem>
DList<Elem>::DList(DList<Elem> &copy) {
	cur = head = nullptr;
	length = copy.GetLength();
	cout << "the length " << length << endl;
	if (length == 0)
		DList<Elem>();
	else{
		for (int i = 0; i < length; i++) {
			char temp;
			copy.SetPos(i);
			copy.GetValue(temp);
			Append(temp);
		}
	}
	cout << "after the copy, the length " << length << endl;
}
template<class Elem>
bool DList<Elem>::Empty() {
	return length == 0;
}