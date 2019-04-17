#include<iostream>
#include<stdlib.h>
#include<time.h>
#define N 1000
using namespace std;
typedef int Elem;
class maxHeap
{
    Elem *array;
    int num;
    int size;
public:
    bool Creat(Elem *arr,int number,int size);
    bool Clear();
    bool Print();
    bool Insert(const Elem &it);
    bool Delete(int pos,Elem &it);
    bool DeleteMax(Elem &it);
protected:
    void Build();
    void Shiftdown(int pos);
    bool ClearHelp();
    bool lt(Elem a,Elem b)
    {
        return a<b;
    }
    bool gt(const Elem &a,const Elem &b)
    {
        return a>b;
    }
    bool eq(const Elem &a,const Elem &b)
    {
        return a==b;
    }
    bool isleaf(int number,int pos)
    {
        return (pos>(number/2-1)&&(pos<number));
    }
    int leftchild(int pos)
    {
        return 2*pos+1;
    }
    int rightchild(int pos)
    {
        return 2*pos+2;
    }
    int parent(int pos)
    {
        return (pos-1)/2;
    }
    bool swap(Elem *arr,int a,int b)
    {
        Elem temp;
        temp=arr[a];
        arr[a]=arr[b];
        arr[b]=temp;
        return true;
    }
};
void Heapsort(Elem a[],int n)
{
    maxHeap H;
    Elem elem;
    H.Creat(a,n,n);
    while(H.DeleteMax(elem))
        continue;
    H.Clear();
    return ;
}

int main(void)
{
    Elem data[N];
    int i;
    for(i=0;i<N;i++)
        data[i]=rand()%N;
    Heapsort(data,N);
    for(i=0;i<N;i++)
        cout<<data[i]<<"  ";
    return 0;
}

bool maxHeap::Creat(Elem *arr,int number,int maxsize)
{
    array=arr;
    num=number;
    size=maxsize;
    Build();
    return true;
}
void maxHeap::Build()
{
    for(int i=num/2-1;i>=0;i--)
        Shiftdown(i);
    return ;
}
void maxHeap::Shiftdown(int pos)
{
    while(!isleaf(num,pos))
    {
        int i=leftchild(pos),j=rightchild(pos);
        if(j<num&&lt(array[i],array[j]))
            i=j;
        if(!lt(array[pos],array[i]))
            return ;
        swap(array,i,pos);
        pos=i;
    }
    return ;
}
bool maxHeap::ClearHelp()
{
    Elem temp;
    if(0==num)
        return false;
    DeleteMax(temp);
    ClearHelp();
    return true;
}
bool maxHeap::Clear()
{
    if(!num)
        return false;
    if(ClearHelp())
    {
        num=size=0;
        array=NULL;
        return true;
    }
    return false;
}
bool maxHeap::Insert(const Elem &it)
{
    int cur;
    if(num>=size)
        return false;
    cur=num++;
    array[cur]=it;
    while(cur!=0&&gt(array[cur],array[parent(cur)]))
    {
        swap(array,parent(cur),cur);
        cur=parent(cur);
    }
    return true;
}
bool maxHeap::DeleteMax(Elem &it)
{
    if(0==num)
        return false;
    swap(array,0,--num);
    if(num!=0)
        Shiftdown(0);
    it=array[num];
    return true;
}
bool maxHeap::Delete(int pos,Elem &it)
{
    if(pos<0||pos>=num)
        return false;
    swap(array,pos,--num);

    while(pos!=0&&gt(array[pos],array[parent(pos)]))
    {
        swap(array,pos,parent(pos));
        pos=parent(pos);
    }
    Shiftdown(pos);
    it=array[num];
    return true;
}
bool maxHeap::Print()
{
    if(0==num)
        return false;
    cout<<"<";
    for(int i=0;i<num;i++)
        cout<<array[i]<<"\t";
    cout<<">";

    for(int level=1,i=0;i<num;i++)
    {
        if(level-1==i)
        {
            cout<<endl;
            level*=2;
        }
        cout<<array[i]<<"\t";
    }
    cout<<"number:"<<num;
    cout<<endl;
    return true;
}















