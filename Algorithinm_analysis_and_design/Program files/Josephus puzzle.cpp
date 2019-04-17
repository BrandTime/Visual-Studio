//ע�⣺��˳���Ϊѭ��˳���
//�ñ��ǰ�ƣ����Ʋ�������˵�ʱ����������һλ�����һλ��ɾ������ʱ��ɾ����Ϊ���һλ����Զ���ָ��������λ
//�����Ĳ���������listIsEnd�������жϵ�ǰλ�Ƿ�Ϊĩβ�����Ը���
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
bool listIsEnd(List &L);
int main(void)
{
    int i,m,n,k;
    Elem elem;
    List list;

    while(1)
    {
        cout<<"������������   n:"<<endl;
        cin>>n;
        cout<<"������ÿ�μ���������   m"<<endl;
        cin>>m;
        cout<<"������ӵڼ��˿�ʼ��ɱ��"<<endl;
        cin>>k;
        if(n<=MAX_SIZE&&n>0)
            if(m>0&&m<=n)
                if(k>=1&&k<=n)
                    break;
        else
            cout<<"����������������롣"<<endl;
    }

    listCreat(list,MAX_SIZE);
    for(i=1;i<=n;i++)
        listAppend(list,i);
    listSetPos(list,k-1);
    listPrint(list);
    cout<<"���ǵ�����˳���������£�"<<endl;
    while(listGetLength(list)>0)
    {
        for(i=0;i<m-1;i++)
            listNext(list);
        listDelete(list,elem);
        cout<<elem<<"\t";
    }
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
bool listSetStart(List &L)
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
    if(L.cur<=L.length-1)
    {
        if(L.length-1==L.cur)
            L.cur=0;
        else
            L.cur++;
        return true;
    }
    return false;
}
bool listPrev(List &L)
{
    if(L.cur>=0)
    {
       if(0==L.cur)
          L.cur=L.length-1;
       else
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
    if(L.length-1==L.cur)
        L.cur=0;
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
bool listIsEnd(List &L)
{
    if(L.length>0&&L.length-1==L.cur)
        return true;
    else
        return false;
}

















