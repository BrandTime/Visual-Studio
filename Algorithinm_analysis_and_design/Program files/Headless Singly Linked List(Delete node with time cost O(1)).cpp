//the listDelete function has been modified to satisfy the requirement.
//the delete function can remove node within O(1) except for the last node.
#include<iostream>
#include<stdlib.h>
#include<time.h>
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
    Node *first;
    Node *last;
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
bool listRoundingDown(List &L,Elem &it);
bool listAppend(List &L,const Elem &it);
bool listPrint(const List &L);
bool listSetValue(List &L,const Elem &it);//重新设定当前节点的数据值
int main(void)
{
    Elem elem;
    List list;
    int i;

    srand((unsigned)time(NULL));
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
    L.first=(Node *)malloc(sizeof(Node));
    if(!L.first)
        return false;

    L.first->next=NULL;
    L.last=L.first;
    L.cur=L.first;
    L.length=0;
    return true;
}
bool listClear(List &L)
{
    Node *temp,*head;
    head=L.first;
    while(head!=NULL)
    {
        temp=head;
        head=head->next;
        free(temp);
    }
    L.first=NULL;
    L.cur=L.first;
    L.last=L.first;
    L.length=0;
    return true;
}
bool listSetStart(List &L)
{
    if(!L.first)
        return false;
    L.cur=L.first;
    return true;
}
bool listSetEnd(List &L)
{
    if(L.length<=0)
        return false;
    L.cur=L.last;
    return true;
}
bool listNext(List &L)
{
    if(L.cur!=L.last)
    {
        L.cur=L.cur->next;
        return true;
    }
    return false;
}
bool listPrev(List &L)
{
    Node *temp;
    if(L.first==L.cur)
        return  false;
    temp=L.first;
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
        L.cur=L.first;
        for(i=0;i<pos;i++)
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
    Node *temp=L.first;
    if(!L.first)
        return false;
    cout<<"<";
    while(temp!=L.cur)
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
bool listAppend(List &L,const Elem &it)
{
    Node *temp;
    if(L.length>=MAX_SIZE)
        return false;
    temp=(Node *)malloc(sizeof(Node));
    if(!temp)
        return false;

    L.last->next=temp;
    temp->next=NULL;
    temp->data=it;
    L.last=temp;
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
    if(L.last==L.cur)
        L.last=temp;
    L.length++;
    return true;
}
bool listDelete(List &L,Elem &it)
{
    if(!L.cur)
        return false;
    Node *temp=L.cur->next;
    if(L.last==L.cur)
    {
        listRoundingDown(L,it);
    }
    else
    {
        it=L.cur->data;
        L.cur->data=temp->data;
        L.cur->next=temp->next;
        free(temp);
        L.length--;
    }
    return true;
}
bool listSetValue(List &L,const Elem &it)
{
    if(!L.first)
        return false;
    L.cur->data=it;
    return true;
}
bool listRoundingDown(List &L,Elem &it)
{
    Node *prev=L.first,*temp=L.cur;
    while(prev->next!=L.cur)
        prev=prev->next;
    prev->next=L.cur->next;
    it=L.cur->data;
    free(temp);
    L.cur=prev;
    L.length--;
    return true;
}
