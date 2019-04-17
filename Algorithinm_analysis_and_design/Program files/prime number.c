#include<stdio.h>
#include<math.h>
#include<windows.h>
#define num 100000
int verify(int i,int flag);

int main(void)
{
    LARGE_INTEGER begin,end,freq;
    int i,n=0,flag;
    double time;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&begin);
    for(i=1;i<=num;i++)
    {
        flag=verify(i,0);
        if(flag==0)
            n++;
    }
    QueryPerformanceCounter(&end);
    time=(end.QuadPart-begin.QuadPart)/(double)freq.QuadPart;
    printf("\n1-%ld的素数个数为:%d\n",num,n);
    printf("执行这个程序所花时间为：%lf\n",time);
}
int verify(int i,int flag)
{
    int j;
    for(j=2;j<=sqrt(i);j++)
    {
      if(i%j==0)
        {
          flag=1;
          break;
        }
      else
        flag=0;
     }

    return flag;
}
