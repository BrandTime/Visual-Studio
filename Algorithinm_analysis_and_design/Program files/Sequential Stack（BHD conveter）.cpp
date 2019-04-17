#include<stdio.h>
#include<ctype.h>
#include<iostream>
#include<stdlib.h>
#define MAX_SIZE 10000
using namespace std;
typedef int Elem;
typedef class Stack
{
public:
    bool stackCreat(Stack &S,int maxsize);
    bool stackClear(Stack &S);
    bool stackGetTopValue(Stack &S,Elem &it);
    bool stackPop(Stack &S,Elem &it);
    bool stackPush(Stack &S,const Elem &it);
    int stackGetLength(const Stack &S);
private:
    int top;
    int size;
    Elem *array;
};

int main(void)
{
    int b,a,maxsize,it,count=0;
    Stack stack;
    printf("请输入需创建的栈大小(1~10000)：\n");
    scanf("%d",&maxsize);
    stack.stackCreat(stack,maxsize);
    printf("请输入想转换的数字:\n");
    scanf("%d",&a);
    printf("请输入需要的进制(2,8,16)：\n");
    scanf("%d",&b);
    while(a)
    {
        stack.stackPush(stack,a%b);
        a=a/b;
    }
    while(stack.stackGetLength(stack))
    {
        stack.stackPop(stack,it);
		if(0==count%4)
			printf("  ");
        printf("%d",it);
		count++;
    }
    printf("\n");
    stack.stackClear(stack);
    return 0;
}

bool Stack::stackCreat(Stack &S,int maxsize)
{
    if(maxsize<=0||maxsize>MAX_SIZE)
        return false;
    S.array=(Elem *)malloc(maxsize*sizeof(Elem));
    if(!S.array)
        return false;
    S.size=maxsize;
    S.top=0;
    return true;
}
bool Stack::stackClear(Stack &S)
{
    if(S.array)
        free(S.array);
    S.size=0;
    S.top=0;
    return true;
}
int Stack::stackGetLength(const Stack &S)
{
    return S.top;
}
bool Stack::stackGetTopValue(Stack &S,Elem &it)
{
    if(!S.array)
        return false;
    it=S.array[top-1];
    return true;
}
bool Stack::stackPop(Stack &S,Elem &it)
{
    if(0==top)
        return false;
    it=S.array[--top];
    return true;
}
bool Stack::stackPush(Stack &S,const Elem &it)
{
    if(S.size==top)
        return false;
    S.array[top++]=it;
    return true;
}

























