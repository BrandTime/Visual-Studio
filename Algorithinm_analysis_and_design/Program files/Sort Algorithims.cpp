#include"Maxheap.h"
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#define N 100000
#define TESTCOUNT 5
#define THRESHOlD 20
#define MaxKeyValue 9
typedef int Elem;
using namespace std;
void Bubsort(int *a,int n);//冒泡排序法
void Selsort(int *a,int n);//选择排序法
void Inssort(int *a,int n);//插入排序法
void Shelsort(int *a,int n,int Incre);//希尔排序法，以输入的Incre为增量
void Heapsort(Elem a[],int n);//堆排序，加上前面实现的最大值堆
void Inssort2(int *a,int n,int incr);//希尔排序辅助函数
void Mergingsort(Elem a[],Elem temp[],int left,int right);//归并排序法1
void Mergesort(Elem a[],Elem temp[],int left,int right);//优化归并排序法2
void Quicksort(int *a,int l,int r);//快速排序法
int Findpivot(int *a,int i,int j);//快速排序法支持函数:找轴值
int Partition(int *a,int l,int r,Elem &p);//快速排序局部排序
void Binsort(Elem a[],int n);//分配排序法（运用线性表数组）
void Radixsort(Elem a[],int n,int k,int r);//基数排序法
void swap(int *a,int b,int c)
{
    int temp=a[b];
    a[b]=a[c];
    a[c]=temp;
    return ;
}
bool lt(const int &a,const int &b)
{
    return a<b;
}
bool gt(const int &a,const int &b)
{
    return a>b;
}

int main(void)
{
    int i,data[N],test[N],temp[N];
    double tim,ave;
    LARGE_INTEGER freq,begin,end;
    srand((unsigned)time(NULL));
    for(i=0;i<N;i++)
        data[i]=rand()%N;
    QueryPerformanceFrequency(&freq);
    for(i=0,ave=0;i<TESTCOUNT;i++)
    {
		for(int j=0;j<N;j++)
			test[j]=data[j];
		QueryPerformanceCounter(&begin);
        Radixsort(test,N,3,10);
		QueryPerformanceCounter(&end);
		tim=(end.QuadPart-begin.QuadPart)/(double)freq.QuadPart;
		ave+=tim/TESTCOUNT;
		cout<<tim<<endl;
    }
	cout<<"基数排序法所花平均时间为：  "<<ave<<endl;
	for(i=0,ave=0;i<TESTCOUNT;i++)
    {
		for(int j=0;j<N;j++)
			test[j]=data[j];
		QueryPerformanceCounter(&begin);
        Heapsort(test,N);
		QueryPerformanceCounter(&end);
		tim=(end.QuadPart-begin.QuadPart)/(double)freq.QuadPart;
		ave+=tim/TESTCOUNT;
		cout<<tim<<endl;
    }
	cout<<"堆排序所花平均时间为：  "<<ave<<endl;
    for(i=0,ave=0;i<TESTCOUNT;i++)
    {
		for(int j=0;j<N;j++)
			test[j]=data[j];
		QueryPerformanceCounter(&begin);
        Mergingsort(test,temp,0,N-1);
		QueryPerformanceCounter(&end);
		tim=(end.QuadPart-begin.QuadPart)/(double)freq.QuadPart;
		ave+=tim/TESTCOUNT;
		cout<<tim<<endl;
    }
	cout<<"归并排序法1所花平均时间为：  "<<ave<<endl;
	for(i=0,ave=0;i<TESTCOUNT;i++)
    {
		for(int j=0;j<N;j++)
			test[j]=data[j];
		QueryPerformanceCounter(&begin);
        Mergesort(test,temp,0,N-1);
		QueryPerformanceCounter(&end);
		tim=(end.QuadPart-begin.QuadPart)/(double)freq.QuadPart;
		ave+=tim/TESTCOUNT;
		cout<<tim<<endl;
    }
	cout<<"归并排序法2所花平均时间为：  "<<ave<<endl;
    for(i=0,ave=0;i<TESTCOUNT;i++)
    {
		for(int j=0;j<N;j++)
			test[j]=data[j];
		QueryPerformanceCounter(&begin);
        Shelsort(test,N,2);
		QueryPerformanceCounter(&end);
		tim=(end.QuadPart-begin.QuadPart)/(double)freq.QuadPart;
		ave+=tim/TESTCOUNT;
		cout<<tim<<endl;
    }
	cout<<"以2为增量的希尔排序法所花平均时间为：  "<<ave<<endl;
	for(i=0,ave=0;i<TESTCOUNT;i++)
    {
		for(int j=0;j<N;j++)
			test[j]=data[j];
		QueryPerformanceCounter(&begin);
        Shelsort(test,N,3);
		QueryPerformanceCounter(&end);
		tim=(end.QuadPart-begin.QuadPart)/(double)freq.QuadPart;
		ave+=tim/TESTCOUNT;
		cout<<tim<<endl;
    }
	cout<<"以3为增量的希尔排序法所花平均时间为：  "<<ave<<endl;
	for(i=0,ave=0;i<TESTCOUNT;i++)
    {
		for(int j=0;j<N;j++)
			test[j]=data[j];
		QueryPerformanceCounter(&begin);
        Shelsort(test,N,22);
		QueryPerformanceCounter(&end);
		tim=(end.QuadPart-begin.QuadPart)/(double)freq.QuadPart;
		ave+=tim/TESTCOUNT;
		cout<<tim<<endl;
    }
	cout<<"以22为增量的希尔排序法所花平均时间为：  "<<ave<<endl;
	for(i=0,ave=0;i<TESTCOUNT;i++)
    {
		for(int j=0;j<N;j++)
			test[j]=data[j];
		QueryPerformanceCounter(&begin);
        Shelsort(test,N,9);
		QueryPerformanceCounter(&end);
		tim=(end.QuadPart-begin.QuadPart)/(double)freq.QuadPart;
		ave+=tim/TESTCOUNT;
		cout<<tim<<endl;
    }
	cout<<"以9为增量的希尔排序法所花平均时间为：  "<<ave<<endl;
	for(i=0,ave=0;i<TESTCOUNT;i++)
    {
		for(int j=0;j<N;j++)
			test[j]=data[j];
		QueryPerformanceCounter(&begin);
        Quicksort(test,0,N-1);
		QueryPerformanceCounter(&end);
		tim=(end.QuadPart-begin.QuadPart)/(double)freq.QuadPart;
		ave+=tim/TESTCOUNT;
		cout<<tim<<endl;
    }
	cout<<"快速排序法所花平均时间为：  "<<ave<<endl;
	for(i=0,ave=0;i<TESTCOUNT;i++)
	{
		for(int j=0;j<N;j++)
			test[j]=data[j];
		QueryPerformanceCounter(&begin);
		Selsort(test,N);
		QueryPerformanceCounter(&end);
		tim=(end.QuadPart-begin.QuadPart)/(double)freq.QuadPart;
		ave+=tim/TESTCOUNT;
		cout<<tim<<endl;
	}
	cout<<"选择排序法所花平均时间为：  "<<ave<<endl;
	for(i=0,ave=0;i<TESTCOUNT;i++)
	{
		for(int j=0;j<N;j++)
			test[j]=data[j];
		QueryPerformanceCounter(&begin);
		Inssort(test,N);
		QueryPerformanceCounter(&end);
		tim=(end.QuadPart-begin.QuadPart)/(double)freq.QuadPart;
		ave+=tim/TESTCOUNT;
		cout<<tim<<endl;
	}
	cout<<"插入排序法所花平均时间为：  "<<ave<<endl;
	for(i=0,ave=0;i<TESTCOUNT;i++)
    {
		for(int j=0;j<N;j++)
			test[j]=data[j];
		QueryPerformanceCounter(&begin);
		Bubsort(test,N);
		QueryPerformanceCounter(&end);
		tim=(end.QuadPart-begin.QuadPart)/(double)freq.QuadPart;
		ave+=tim/TESTCOUNT;
		cout<<tim<<endl;
	}
	cout<<"冒泡排序法所花平均时间为：  "<<ave<<endl;
    return 0;
}

void Bubsort(int *a,int n)
{
    int i,j;
    for(i=0;i<n-1;i++)
        for(j=n-1;j>i;j--)
            if(lt(a[j],a[j-1]))
                swap(a,j,j-1);
    return ;
}
void Selsort(int *a,int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        int flag=i;
        for(j=n-1;j>i;j--)
            if(lt(a[j],a[flag]))
                flag=j;
        if(lt(a[flag],a[i]))
            swap(a,flag,i);
    }
    return ;
}
void Inssort(int *a,int n)
{
    int i,j;
    for(i=0;i<n;i++)
        for(j=i;j>0&&(lt(a[j],a[j-1]));j--)
            swap(a,j-1,j);
    return ;
}
void Shelsort(int *a,int n,int Incre)
{
    int i,j;
    for(j=n/Incre;j>Incre;j/=Incre)
        for(i=0;i<j;i++)
            Inssort2(&a[i],n-i,j);
    Inssort2(a,n,1);
    return ;
}
void Inssort2(int *a,int n,int incr)
{
    int i,j;
    for(i=incr;i<n;i+=incr)
        for(j=i;j>=incr&&(lt(a[j],a[j-incr]));j-=incr)
            swap(a,j,j-incr);
    return ;
}
int Findpivot(int *a,int i,int j)
{
    return (i+j)/2;
}
void Quicksort(int *a,int l,int r)
{
    if(r<=l)
        return ;
    int p=Findpivot(a,l,r);
    swap(a,r,p);
    int k=Partition(a,l-1,r,a[r]);
    swap(a,k,r);
    Quicksort(a,l,k-1);
    Quicksort(a,k+1,r);
}
int Partition(int *a,int l,int r,Elem &p)
{
    do
    {
        while(lt(a[++l],p));
        while(gt(a[--r],p));
        swap(a,l,r);
    }while(l<r);
    swap(a,l,r);
    return l;
}
void Mergingsort(Elem a[],Elem temp[],int left,int right)
{
    int i,j,mid=(left+right)/2,cur;
    if(left==right)
        return ;
    Mergingsort(a,temp,left,mid);
    Mergingsort(a,temp,mid+1,right);
    for(i=left;i<=right;i++)
        temp[i]=a[i];
    i=left;
    j=mid+1;
    for(cur=left;cur<=right;cur++)
    {
        if(i>mid)
            a[cur]=temp[j++];
        else if(j>right)
            a[cur]=temp[i++];
        else if(lt(temp[i],temp[j]))
            a[cur]=temp[i++];
        else
            a[cur]=temp[j++];
    }
    return ;
}
void Mergesort(Elem a[],Elem temp[],int left,int right)
{
    int i,j,cur,mid=(left+right)/2;
    if(left==right)
        return ;
    if((right-left)<=10)
    {
        Inssort(&a[left],right-left+1);
        return ;
    }
    Mergesort(a,temp,left,mid);
    Mergesort(a,temp,mid+1,right);
    for(i=left;i<=mid;i++)
        temp[i]=a[i];
    for(i=1;i<=right-mid;i++)
        temp[right-i+1]=a[i+mid];
    for(i=left,j=right,cur=left;cur<=right;cur++)
    {
        if(lt(temp[i],temp[j]))
            a[cur]=temp[i++];
        else
            a[cur]=temp[j--];
    }
    return ;
}
/*引入前面实现的顺序表才能使用
void Binsort(Elem a[],int n)
{
    List b[MaxKeyValue];
    Elem elem;
    for(int i=0;i<n;i++)
        b[a[i]].append(a[i]);
    for(i=0;i<=MaxKeyValue;i++)
        for(b[i].setStart();b[i].getValue(elem);b[i].next())
            cout<<elem<<"  ";
    return ;
}
*/
void Radixsort(Elem a[],int n,int k,int r)//r为盒子数，k为关键码的位数
{
    Elem b[n],temp[r],kok=1;
    for(int i=0,j;i<k;i++,kok*=r)
    {
        for(j=0;j<r;j++)
            temp[j]=0;
        for(j=0;j<n;j++)
            temp[(a[j]/kok)%r]++;
        for(j=1;j<r;j++)
            temp[j]=temp[j]+temp[j-1];
        for(j=n-1;j>=0;j--)
            b[--temp[(a[j]/kok)%r]]=a[j];
        for(j=0;j<n;j++)
            a[j]=b[j];
    }
    return ;
}
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













