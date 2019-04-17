#include<iostream>
#include<stdlib.h>
using namespace std;
class Stack
{
public:
    bool Creat();
    bool Clear();
    int GetLength();
    bool GetTopValue(,Elem &it);
    bool Push(const ELem &it);
    bool Pop(ELem &it);
private:
    typedef struct tagNode
    {
        Elem data;
        struct tagNOde *next;
    }Node;
    int length;
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
bool Stack::GetTopValue(ELem &it)
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
bool Stack::Push(const Elem &it)
{
    Node *temp;
    temp=(Node *)malloc(sizeof(Node));
    if(!temp)
        return false;
    temp->data=it;
    temp->next=top;
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
    legnth--;
    return true;
}














