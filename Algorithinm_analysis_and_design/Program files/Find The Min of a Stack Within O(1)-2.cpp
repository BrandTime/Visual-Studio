//运用双栈结构，一个栈专门用来储存前一个栈的当前最小值
#include<iostream>
#include<stdlib.h>
using namespace std;
typedef int Elem;
class Stack
{
public:
    bool Creat();
    bool Clear();
    bool Push(const Elem &it);
    bool Pop(Elem &it);
    bool Print();
    bool GetTopValue(Elem &it);
    int GetLength();
private:
    int length;
    typedef struct tagNode
    {
        Elem data;
        struct tagNode *next;
    }Node;
    Node *top;
};

int main(void)
{
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



























