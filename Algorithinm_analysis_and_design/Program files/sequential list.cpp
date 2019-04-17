#include<iostream>
#include<stdlib.h>
#define bool int
#define true 1
#define false 0
#define MAX_SIZE 10000
using namespace std;
typedef int Elem;
typedef struct
{
    Elem *array;
    int length;
    int cur;
    int size;
}List;
bool listCreat(List &L,int maxsize);
bool listClear(List &L);
bool listSetStart(List &L);
bool listSetEnd(List &L);
bool listNext(List &L);
bool listPrev(List &L);
bool listSetPos(List &L,int pos);
bool listGetValue(const List &L,Elem &it);
int listGetLength(const List &L);
bool listInsert(List &L,const Elem &it);
bool listAppend(List &L,const Elem &it);
bool listDelete(List &L,Elem &it);
bool listPrint(const List &L);
int main(void)
{
    int i;
    Elem elem;
    List list;

    listCreat(list,100); listPrint(list);
    for(i=0;i<10;i++)
    {
            elem=rand()%100;
            listInsert(list,elem);
             listPrint(list);
    }
    listSetPos(list, listGetLength(list)/2); listPrint(list);
    listInsert(list, 99); listPrint(list);
    listNext(list); listPrint(list);
    listInsert(list,100); listPrint(list);
    listPrev(list); listPrint(list);
    listDelete(list,elem); listPrint(list);
    listAppend(list,101); listPrint(list);
    listSetEnd(list); listDelete(list,elem); listPrint(list);
    listClear(list);

    return 0;
}
bool listCreat(List &L,int maxsize)
{
    if(maxsize<0||maxsize>MAX_SIZE)
        return false;
    L.array=(Elem *)malloc(maxsize*sizeof(Elem));
    if(NULL==L.array)
        return false;
    L.length=0;
    L.cur=0;
    L.size=maxsize;
    return true;
}
bool listClear(List &L)
{
    if(L.array)
    {
        free(L.array);
        L.array=NULL;
        return true;
    }
    return false;
}
bool listSetstart(List &L)
{
    if(NULL!=L.array)
    {
        L.cur=0;
        return true;
    }
    return false;
}
bool listSetEnd(List &L)
{
    if(L.array!=NULL)
    {
        L.cur=L.length-1;
        return true;
    }
    return false;
}
bool listNext(List &L)
{
    if(L.cur<L.length-1)
    {
        L.cur++;
        return true;
    }
    return false;
}
bool listPrev(List &L)
{
    if(L.cur>0)
    {
       L.cur--;
       return true;
    }
    return false;
}
bool listSetPos(List &L,int pos)
{
    if(pos>=0&&pos<L.length)
    {
        L.cur=pos;
        return true;
    }
    return false;
}
bool listGetValue(const List &L,Elem &it)
{
    if(L.length>0)
    {
        it=L.array[L.cur];
        return true;
    }
    return false;
}
int listGetLength(const List &L)
{
    return L.length;
}
bool listPrint(const List &L)
{
    int i;
    if(L.length<=0)
        return false;
    cout<<"<";
    for(i=0;i<L.cur;i++)
        cout<<L.array[i]<<" ";
    cout<<"*";
    for(i=L.cur;i<L.length;i++)
        cout<<L.array[i]<<" ";
    cout<<">"<<endl;
    return true;
}
bool listInsert(List &L,const Elem &it)
{
    int i;
    if(L.length>=L.size)
        return false;
    for(i=L.length;i>L.cur;i--)
        L.array[i]=L.array[i-1];
    L.array[L.cur]=it;
    L.length++;
    return true;
}
bool listDelete(List &L,Elem &it)
{
    int i;
    if(L.length<=0)
        return false;
    it=L.array[L.cur];
    for(i=L.cur;i<L.length;i++)
        L.array[i]=L.array[i+1];
    L.length--;
    return true;
}
bool listAppend(List &L,const Elem &it)
{
    if(L.length>=L.size)
        return false;
    L.array[L.length]=it;
    L.length++;
    return true;
}






















































































































