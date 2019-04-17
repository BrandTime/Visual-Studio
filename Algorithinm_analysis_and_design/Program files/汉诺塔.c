#include<stdio.h>
int x=0;
int move(char start,char goal)/*将一个柱子上的金片移到另一个柱子上并递增步数*/
{

    printf("%c-->%c\n",start,goal);
    x++;

    return ;
}
int finl(int n,char start,char temp,char goal)
{
    if(n==0)
        return;
    finl(n-1,start,temp,goal);//将n-1个金片以目标柱为中介移到中间柱上
    move(start,goal);//将最后一个金片时直接移到目标柱上
    finl(n-1,temp,goal,start);//再将前n-1个金片从中间柱以起始柱为中转移到目标柱上

    return;
}
int main(void)
{
    int n;
    char a='A',b='B',c='C';
    printf("本程序为三个柱的河内塔，请输入金片个数：");
    scanf("%d",&n);
    finl(n,a,b,c);
    printf("所需总步数为：%d",x);

    return 0;
}
