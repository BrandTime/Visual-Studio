//一个栈的数据域力量有两个元素，一个是输入的值，另一个是当前栈中的最小值
#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
typedef int Elem;
class Stack
{
public:
    bool Creat();
    bool Clear();
    bool GetTopValue(Elem &it);
    bool Push(const Elem &it);
    bool Pop(Elem &it);
    bool Print();
    int GetLength();
    Elem Min();
private:
    typedef struct tagNode
    {
        Elem data,min;
        struct tagNode *next;
    }Node;
    int length;
    Node *top;
};

int main(void)
{
    Elem min,elem;
    int i;
    Stack stack;
    srand((unsigned)time(NULL));
    stack.Creat();
    for(i=0;i<=10;i++)
    {
        elem=rand()%100;
        stack.Push(elem);
        stack.Print();

    }
    cout<<"该堆栈的最小值为："<<endl;
    cout<<stack.Min()<<endl;
    stack.Clear();
    return 0;
}

bool Stack::Creat()
{
    top=NULL;
    length=0;
    return true;
}
bool Stack::Clear()
{
    if(!top)
        return false;
    Node *temp;
    while(top)
    {
        temp=top;
        top=top->next;
        free(temp);
    }
    top=NULL;
    length=0;
    return true;
}
bool Stack::GetTopValue(Elem &it)
{
    if(!top)
        return false;
    it=top->data;
    return true;
}
int Stack::GetLength()
{
    return length;
}
bool Stack::Print()
{
    if(!top)
        return false;
    Node *temp=top;
    while(temp)
    {
        cout<<temp->data<<" "<<temp->min<<"\t";
        temp=temp->next;
    }
    cout<<endl;
    return true;
}
bool Stack::Push(const Elem &it)
{
    Node *temp;
    temp=(Node *)malloc(sizeof(Node));
    if(!temp)
        return false;
    temp->data=it;
    if(top)
    {
        if(it<top->min)
            temp->min=it;
        else
            temp->min=top->min;
        temp->next=top;
    }
    else
    {
        temp->min=it;
        temp->next=NULL;
    }
    top=temp;
    length++;
    return true;
}
bool Stack::Pop(Elem &it)
{
    if(!top)
        return false;
    Node *temp=top;
    it=temp->data;
    top=top->next;
    free(temp);
    length--;
    return true;
}
Elem Stack::Min()
{
    return top->min;
}
















