#include<iostream>
#include<stdlib.h>
#define MAX_SIZE 10000
using namespace std;
typedef int Elem;
typedef struct Tagnode
{
    Elem data;
    struct Tagnode *next;
    struct Tagnode *prev;
}Node;
typedef struct
{
    Node *head;
    Node *tail;
    Node *cur;
    int length;
}List;
bool listCreat(List &L);
bool listClear(List &L);
bool listSetStart(List &L);
bool listSetEnd(List &L);
bool listSetPos(List &L,const int &pos);
bool listNext(List &L);
bool listPrev(List &L);
bool listDelete(List &L,Elem &it);
bool listInsert(List &L,const Elem &it);
bool listAppend(List &L,const Elem &it);
bool listGetValue(const List &L,Elem &it);
int listGetLength(const List &L);
bool listPrint(const List &L);

int main(void)
{
    List list;
    Elem elem;
    int i;
    listCreat(list);
    for(i=0;i<10;i++)
    {
        elem=rand()%100;
        listAppend(list,elem);
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

bool listCreat(List &L)
{
    L.head=NULL;
    L.head->next=NULL;
    L.head->prev=NULL;
    L.cur=L.head;
    L.tail=L.head;
    L.length=0;
    return true;
}
bool listClear(List &L)
{
    if(!L.head)
        return false;
    Node *temp,*head=L.head;
    listSetStart(L);
    while(L.cur!=NULL)
    {
        temp=L.cur;
        L.cur=L.cur->next;
        free(temp);
    }
    L.head=NULL;
    L.tail=NULL;
    L.cur=NULL;
    L.length=0;
    return true;
}
int listGetLength(const List &L)
{
    return L.length;
}
bool listGetValue(const List &L,Elem &it)
{
    if(!L.head)
        return false;
    it=L.cur->data;
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
    if(!L.head)
        return false;
    L.cur=L.tail;
    return true;
}
bool listSetPos(List &L,const int &it)
{
    if(!L.head)
        return false;
    int i;
    Node *temp=L.head;
    for(i=1;i<it;i++)
        temp=temp->next;
    L.cur=temp;
    return true;
}
bool listNext(List &L)
{
    if(!L.head)
        return false;
    L.cur=L.cur->next;
    if(L.head==L.cur)
        cout<<"回到了第一个结点："<<endl;
    return true;
}
bool listPrev(List &L)
{
    if(!L.head)
        return false;
    L.cur=L.cur->prev;
    if(L.head==L.cur)
        cout<<"回到了第一个结点："<<endl;
    return true;
}
bool listPrint(const List &L)
{
    if(!L.head)
        return false;
    Node *temp=L.head;
    cout<<"<";
    while(temp!=L.cur)
    {
        cout<<temp->data<<"  ";
        temp=temp->next;
    }
    cout<<"*";
    while(temp!=NULL)
    {
        cout<<temp->data<<"  ";
        temp=temp->next;
    }
    return true;
}
bool listInsert(List &L,const Elem &it)
{
    if(L.length>=MAX_SIZE)
        return false;
    Node *temp;
    temp=(Node *)malloc(sizeof(Node));
    if(!temp)
        return false;
    temp->data=it;
    temp->next=L.cur->next;
    L.cur->next->prev=temp;
    temp->prev=L.cur;
    L.cur->next=temp;
    if(NULL==temp->next)
        L.tail=temp;
    L.length++;
    return true;
}
bool listAppend(List &L,const Elem &it)
{
    if(L.length>=MAX_SIZE)
        return false;
    Node *temp;
    temp=(Node *)malloc(sizeof(Node));
    if(!temp)
        return false;
    temp->data=it;
    temp->next=NULL;
    if(L.head)
    {
        temp->prev=L.tail;
        L.tail->next=temp;
    }
    else
    {
        temp->prev=NULL;
        L.head=temp;
        L.cur=temp;
    }
    L.tail=temp;
    L.length++;
    return true;
}
bool listDelete(List &L,Elem &it)
{
    if(!L.head)
        return false;
    Node *temp=L.cur;
    it=temp->data;
    if(L.head==L.cur)
        L.head=L.cur->next;
    L.cur->prev->next=L.cur->next;
    L.cur->next->prev=L.cur->prev;
    L.cur=L.cur->next;
    free(temp);
    L.length--;
    return true;
}




