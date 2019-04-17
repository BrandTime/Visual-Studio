#include<iostream>
#include<stdlib.h>
#include<time.h>
#define MAX_SIZE 10000
using namespace std;
typedef int Elem;
class Stack
{
public:
    bool Creat(int maxsize);
    bool Clear();
    bool GetTopValue(Elem &it);
    bool Pop(Elem &it);
    bool Push(const Elem &it);
    int GetLength();
private:
    int top;
    int size;
    Elem *array;
};
class List
{
public:
    bool Creat();
    bool Clear();
    bool SetStart();
    bool SetEnd();
    bool SetPos(int pos);
    bool Prev();
    bool Next();
    bool GetValue(Elem &it);
    int GetLength();
    bool Insert(const Elem &it);
    bool Delete(Elem &it);
    bool Append(const Elem &it);
    bool Print();
private:
    typedef struct tagLink
    {
        Elem data;
        struct tagLink *next;
    }Link;
    int length;
    Link *head;
    Link *cur;
    Link *tail;
};

int main(void)
{
    Elem elem;
    List list;
    Stack stack;
    int i,j;

    srand((unsigned)time(NULL));
    cout<<"请输入单链表的长度："<<endl;
    cin>>j;
    list.Creat();
    for(i=0;i<j;i++)
    {
        elem=rand()%200;
        list.Insert(elem);
    }
    stack.Creat(list.GetLength());
    do
    {
        list.GetValue(elem);
        stack.Push(elem);
    }while(list.Next());
    i=list.GetLength();
    list.SetEnd();
    while(1)
    {
        if(!stack.Pop(elem))
            break;
        list.Print();
        cout<<"该单链表第"<<i<<"个数据是--"<<elem<<endl;
        i--;
        list.Prev();
    }
    return 0;
}

bool Stack::Creat(int maxsize)
{
    if(maxsize<=0||maxsize>MAX_SIZE)
        return false;
    array=(Elem *)malloc(maxsize*sizeof(Elem));
    if(!array)
        return false;
    size=maxsize;
    top=0;
    return true;
}
bool Stack::Clear()
{
    if(array)
        free(array);
    size=0;
    top=0;
    return true;
}
int Stack::GetLength()
{
    return top;
}
bool Stack::GetTopValue(Elem &it)
{
    if(!array)
        return false;
    it=array[top-1];
    return true;
}
bool Stack::Pop(Elem &it)
{
    if(0==top)
        return false;
    it=array[--top];
    return true;
}
bool Stack::Push(const Elem &it)
{
    if(size==top)
        return false;
    array[top++]=it;
    return true;
}

bool List::Creat()
{
    head=NULL;
    tail=NULL;
    cur=NULL;
    length=0;
    return true;
}
bool List::Clear()
{
    Link *temp,*head;
    head=head;
    while(head!=NULL)
    {
        temp=head;
        head=head->next;
        free(temp);
    }
    head=NULL;
    cur=head;
    tail=head;
    length=0;
    return true;
}
bool List::SetStart()
{
    if(!head)
        return false;
    cur=head;
    return true;
}
bool List::SetEnd()
{
    if(length<=0)
        return false;
    cur=tail;
    return true;
}
bool List::Next()
{
    if(cur!=tail)
    {
        cur=cur->next;
        return true;
    }
    return false;
}
bool List::Prev()
{
    Link *temp;
    if(head==cur)
        return  false;
    temp=head;
    while(temp->next!=cur)
        temp=temp->next;
    cur=temp;
    return true;
}
bool List::SetPos(int pos)
{
    int i;
    if(pos>=0&&pos<length)
    {
        cur=head;
        for(i=0;i<pos;i++)
            cur=cur->next;
        return true;
    }
    return false;
}
int List::GetLength()
{
    return length;
}
bool List::GetValue(Elem &it)
{
    if(cur)
    {
        it=cur->data;
        return true;
    }
    return false;
}
bool List::Print()
{
    Link *temp=head;
    if(!head)
        return false;
    if(1==length)
    {
        cout<<"<"<<"*"
        <<temp->data<<">"<<endl;
        return true;
    }
    cout<<"<";
    while(temp!=cur)
    {
        cout<<temp->data<<" ";
        temp=temp->next;
    }
    cout<<"*";
    while(temp!=NULL)
    {
        cout<<temp->data<<" ";
        temp=temp->next;

    }
    cout<<">"<<endl;
    return true;
}
bool List::Append(const Elem &it)
{
    Link *temp;
    if(length>=MAX_SIZE)
        return false;
    temp=(Link *)malloc(sizeof(Link));
    if(!temp)
        return false;
    temp->next=NULL;
    temp->data=it;
    if(!head)
    {
        head=temp;
        cur=temp;
    }
    else
        tail->next=temp;
    tail=temp;
    length++;
    return true;
}
bool List::Insert(const Elem &it)
{
    Link *temp;
    if(length>=MAX_SIZE)
        return false;
    temp=(Link *)malloc(sizeof(Link));
    if(!temp)
        return false;
    temp->data=it;
    if(!head)
    {
        head=temp;
        cur=temp;
        tail=temp;
    }
    else
    {
        temp->next=cur->next;
        cur->next=temp;
    }
    if(tail==cur)
        tail=temp;
    length++;
    return true;
}
bool List::Delete(Elem &it)
{
    Link *prev=head,*temp=cur;
    if(!cur)
        return false;
    while(prev->next!=cur)
        prev=prev->next;
    it=cur->data;
    prev->next=cur->next;
    if(NULL!=cur->next)
         cur=cur->next;
    else
    {
        cur=prev;
        tail=cur;
    }
    free(temp);
    length--;
    return true;
}
