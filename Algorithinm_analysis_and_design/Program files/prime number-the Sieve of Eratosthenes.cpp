#include<stdio.h>
#include<math.h>
#include<windows.h>
#define N 1000000
int prime[N];
int find(int *prime);
int main(void)
{
    LARGE_INTEGER freq,begin,end;
    int i,count=0;
    double time;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&begin);
    for(i=0;i<N;i++)
    {
        if(i%2==0)
            prime[i]=0;
        else
            prime[i]=1;
    }
    find(prime);
    for(i=0;i<N;i++)
    {
        if(prime[i])
            count++;
    }
    QueryPerformanceCounter(&end);
    time=(end.QuadPart-begin.QuadPart)/(double)freq.QuadPart;
    printf("\n0--%d之间的素数总数为：%d\n",N,count);
    printf("执行这个程序所时间为：%lf\n",time);

    return 0;
}
int find(int *prime)
{
    int outer,inner;
    for(outer=3;outer<sqrt(N);outer+=2)
        if(prime[outer])
        {
            for(inner=outer*2;inner<N;inner+=outer)
                prime[inner]=0;
        }

    return 0;
}

