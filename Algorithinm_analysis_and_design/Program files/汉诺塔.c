#include<stdio.h>
int x=0;
int move(char start,char goal)/*��һ�������ϵĽ�Ƭ�Ƶ���һ�������ϲ���������*/
{

    printf("%c-->%c\n",start,goal);
    x++;

    return ;
}
int finl(int n,char start,char temp,char goal)
{
    if(n==0)
        return;
    finl(n-1,start,temp,goal);//��n-1����Ƭ��Ŀ����Ϊ�н��Ƶ��м�����
    move(start,goal);//�����һ����Ƭʱֱ���Ƶ�Ŀ������
    finl(n-1,temp,goal,start);//�ٽ�ǰn-1����Ƭ���м�������ʼ��Ϊ��ת�Ƶ�Ŀ������

    return;
}
int main(void)
{
    int n;
    char a='A',b='B',c='C';
    printf("������Ϊ�������ĺ��������������Ƭ������");
    scanf("%d",&n);
    finl(n,a,b,c);
    printf("�����ܲ���Ϊ��%d",x);

    return 0;
}
