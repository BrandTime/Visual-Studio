#ifndef CLASS_H_INCLUDED
#define CLASS_H_INCLUDED

#include<iostream>
#include<stdlib.h>
using namespace std;
typedef int Elem;
class Node
{
public:
    int x;
    int y;
    Node *pre;
    Node *next;
    Node(int i=1,int j=1)
    {
        x=i;
        y=j;
        pre=next=NULL;
    }
};
class Queue
{
    Node *head;
    Node *cur;
    Node *tail;
    int length;
    static bool flag;
public:
    Queue()
    {
        tail=head=cur=NULL;
        length=0;
    }
    ~Queue()
    {
        cur=head;
        while(cur!=NULL)
        {
            Node *temp=cur;
            cur=cur->next;
            delete temp;
        }
        length=0;
        tail=cur=head=NULL;
    }
    bool Enqueue(int i,int j);
    bool Dequeue();
    int Getlength();
    friend void Path(int **a,int i,int j,const Queue &q);
    static void Reflag();
};
bool Queue::flag=false;

class Stack
{
public:
    Stack()
    {
        top=NULL;
        length=0;
    }
    ~Stack()
    {
         if(top)
         {
            Node *temp;
            while(top)
            {
                temp=top;
                top=top->next;
                free(temp);
            }
            top=NULL;
            length=0;
         }
    }
    int GetLength();
    bool Push(const Elem &x_,const Elem &y_);
    bool Pop();
    bool Pop(Elem &x_,Elem &y_);
    bool Print(int i=0);
    static bool Getflag()
    {
        return flag;
    }
    static void Setflag(bool a)
    {
        flag=a;
    }
private:
    typedef struct tagNode
    {
        int x;
        int y;
        struct tagNode *next;
    }Node;
    Node *top;
    int length;
    static bool flag;
};
bool Stack::flag=false;

#endif // CLASS_H_INCLUDED
