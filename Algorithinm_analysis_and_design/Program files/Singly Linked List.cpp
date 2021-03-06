#include<iostream>
#include<stdlib.h>
#define MAX_SIZE 10000
using namespace std;
typedef int Elem;
typedef struct tagNode
{
    Elem data;
    struct tagNode *next;
}Node;
typedef struct
{
    Node *head;
    Node *tail;
    Node *cur;
    int length;
}List;
bool listCreat(List &L,int maxsize);
bool listClear(List &L);
bool listSetStart(List &L);
bool listSetEnd(List &L);
bool listSetPos(List &L,int pos);
bool listPrev(List &L);
bool listNext(List &L);
bool listGetValue(const List &L,Elem &it);
int listGetLength(const List &L);
bool listInsert(List &L,const Elem &it);
bool listDelete(List &L,Elem &it);
bool listAppend(List &L,const Elem &it);
bool listPrint(const List &L);
int main(void)
{
    Elem elem;
    List list;
    int i;

    listCreat(list,100);
    listPrint(list);
    for(i=0;i<10;i++)
    {
        elem=rand()%100;
        listInsert(list,elem);
        listPrint(list);
    }
    listSetPos(list, listGetLength(list)/2);
    listPrint(list);
    listInsert(list, 99);
    listPrint(list);
    listNext(list);
    listPrint(list);
    listInsert(list,100);
    listPrint(list);
    listPrev(list);
    listPrint(list);
    listDelete(list,elem);
    listPrint(list);
    listAppend(list,101);
    listPrint(list);
    listSetEnd(list);
    listDelete(list,elem);
    listPrint(list);
    listClear(list);

    return 0;
}
bool listCreat(List &L,int maxsize)
{
    if(maxsize>MAX_SIZE)
        return false;
    L.head=(Node *)malloc(sizeof(Node));
    if(!L.head)
        return false;

    L.head->data=-1;
    L.head->next=NULL;
    L.tail=L.head;
    L.cur=L.head;
    L.length=0;
    return true;
}
bool listClear(List &L)
{
    Node *temp,*head;
    head=L.head;
    while(head!=NULL)
    {
        temp=head;
        head=head->next;
        free(temp);
    }
    L.head=NULL;
    L.cur=L.head;
    L.tail=L.head;
    L.length=0;
    return true;
}
bool listSetStart(List &L)
{
    if(!L.head)
        return false;
    L.cur=L.head;
    return true;
}
bool listSetEnd(List &L)
{
    if(L.length<=0)
        return false;
    L.cur=L.tail;
    return true;
}
bool listNext(List &L)
{
    if(L.cur!=L.tail)
    {
        L.cur=L.cur->next;
        return true;
    }
    return false;
}
bool listPrev(List &L)
{
    Node *temp;
    if(L.head==L.cur)
        return  false;
    temp=L.head;
    while(temp->next!=L.cur)
        temp=temp->next;
    L.cur=temp;
    return true;
}
bool listSetPos(List &L,int pos)
{
    int i;
    if(pos>=0&&pos<L.length)
    {
        L.cur=L.head;
        for(i=0;i<=pos;i++)
            L.cur=L.cur->next;
        return true;
    }
    return false;
}
int listGetLength(const List &L)
{
    return L.length;
}
bool listGetValue(List &L,Elem &it)
{
    if(L.cur)
    {
        it=L.cur->data;
        return true;
    }
    return false;
}
bool listPrint(const List &L)
{
    Node *temp=L.head;
    if(!L.head)
        return false;
    cout<<"<";
    while(temp!=L.cur)
    {
        cout<<temp->data<<"\t";
        temp=temp->next;
    }
    cout<<"*";
    while(temp!=NULL)
    {
        cout<<temp->data<<"\t";
        temp=temp->next;

    }
    cout<<">"<<endl;
    return true;
}
bool listAppend(List &L,const Elem &it)
{
    Node *temp;
    if(L.length>=MAX_SIZE)
        return false;
    temp=(Node *)malloc(sizeof(Node));
    if(!temp)
        return false;

    L.tail->next=temp;
    temp->next=NULL;
    temp->data=it;
    L.tail=temp;
    L.length++;
    return true;
}
bool listInsert(List &L,const Elem &it)
{
    Node *temp;
    if(L.length>=MAX_SIZE)
        return false;
    temp=(Node *)malloc(sizeof(Node));
    if(!temp)
        return false;
    temp->data=it;
    temp->next=L.cur->next;
    L.cur->next=temp;
    if(L.tail==L.cur)
        L.tail=temp;
    L.length++;
    return true;
}
bool listDelete(List &L,Elem &it)
{
    Node *prev=L.head,*temp=L.cur;
    if(!L.cur)
        return false;
    while(prev!=L.cur)
        prev=prev->next;
    it=L.cur->data;
    prev->next=L.cur->next;
    if(NULL!=L.cur->next)
        L.cur=L.cur->next;
    else
    {
        L.cur=prev;
        L.tail=L.cur;
    }
    free(temp);
    L.length--;
    return true;
}























