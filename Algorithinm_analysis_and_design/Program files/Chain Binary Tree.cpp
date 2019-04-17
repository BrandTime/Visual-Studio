#include<iostream>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;
typedef char Elem;
typedef struct tagBinNode
{
    Elem data;
    struct tagBinNode *lc;
    struct tagBinNode *rc;
}BinNode,*BinTree;
bool bintreeCreat(BinTree &T);
bool bintreeClear(BinTree &T);
bool bintreePreorder(BinTree &T);
bool bintreeInorder(BinTree &T);
bool bintreePosorder(BinTree &T);
bool bintreeBanlanceTree(BinTree &T);//�жϸ����Ƿ�Ϊƽ�������
int bintreeCount(BinTree &T);
int bintreeDepth(BinTree &T);

int main(void)
{
    BinTree tree;
    string *str;
    cout<<"�밴����������������������Ԫ��ֵ����#����ʾ�ڵ�Ϊ�գ�"<<endl;
    bintreeCreat(tree);
    cout<<"���������";
    bintreePreorder(tree);
    cout<<endl<<"���������";
    bintreeInorder(tree);
    cout<<endl<<"���������";
    bintreePosorder(tree);
    cout<<endl<<"�ö������Ľڵ���Ϊ��"<<bintreeCount(tree)<<endl;
    cout<<"�ö����������Ϊ��"<<bintreeDepth(tree)<<endl;
    if(bintreeBanlanceTree(tree))
        cout<<"������ƽ�������"<<endl;
    else
        cout<<"��������ƽ�������"<<endl;
    bintreeClear(tree);
    return 0;
}

bool bintreeCreat(BinTree &T)
{
    Elem a;
    cout<<"input:"<<endl;
    a=getchar();getchar();
    if('#'==a)
        T=NULL;
    else
    {
        T=(BinNode *)malloc(sizeof(BinNode));
        if(!T)
            return false;
        T->data=a;
        bintreeCreat(T->lc);
        bintreeCreat(T->rc);
    }
    return true;
}
bool bintreeClear(BinTree &T)
{
    if(!T)
        return false;
    if(T->lc)
        bintreeClear(T->lc);
    if(T->rc)
        bintreeClear(T->rc);
    free(T);
    return true;
}
int bintreeCount(BinTree &T)
{
    if(NULL==T)
        return 0;
    return 1+bintreeCount(T->rc)+bintreeCount(T->lc);
}
bool bintreePreorder(BinTree &T)
{
    if(NULL==T)
        return true;
    cout<<T->data<<"\t";
    bintreePreorder(T->lc);
    bintreePreorder(T->rc);
    return true;
}
bool bintreeInorder(BinTree &T)
{
    if(NULL==T)
        return true;
    bintreeInorder(T->lc);
    cout<<T->data<<"\t";
    bintreeInorder(T->rc);
    return true;
}
bool bintreePosorder(BinTree &T)
{
    if(NULL==T)
        return true;
    bintreePosorder(T->lc);
    bintreePosorder(T->rc);
    cout<<T->data<<"\t";
    return true;
}
int bintreeDepth(BinTree &T)
{
    if(NULL==T)
        return 0;
    int left=1,right=1;

    left+=bintreeDepth(T->lc);
    right+=bintreeDepth(T->rc);
    return right>left?right:left;
}
bool bintreeBanlanceTree(BinTree &T)
{
     if(NULL==T)
        return false;
     int left=0,right=0;
     left=bintreeDepth(T->lc);
     right=bintreeDepth(T->rc);
     if(1==abs(left-right))
        return true;
     else

        return false;
}















