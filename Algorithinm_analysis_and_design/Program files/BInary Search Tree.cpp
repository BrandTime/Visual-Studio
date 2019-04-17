#include<iostream>
#include<stdlib.h>
#include<queue>
#include<vector>
using namespace std;
typedef int Elem;
typedef struct BST
{
    Elem data;
    struct BST *lc;
    struct BST *rc;
}BST,*BSTree;//�˴�ָ�����ں���ĵݹ���ã�Ϊ�˺��ڲ���lc rcָ�����������ϣ������������ڴ����½��
bool bstInsert(BSTree &T,const &it);
bool bstCreat(BSTree &T);
bool bstClear(BSTree &T);
bool bstPrint(const BSTree &T);//��ӡʱ����level=0����
bool bstFind(BSTree &T,const Elem &it);//�ڶ���������Ѱһ��ֵ���ҵ��ͷ���1�����򷵻�0
bool bstDelete(BSTree &T,const Elem &it);
bool bstInterval(BSTree &T,const Elem &a,const Elem &b);//�ҵ�������������λ��a--b�Ľڵ㲢��ӡ
int bstGetSize(BSTree &T);
int bstDepth(const BSTree &T);
//֧�ֺ���
bool lt(const Elem &k,const Elem &e);
bool gt(const Elem &k,const Elem &e);
bool eq(const Elem &k,const Elem &e);
void bstPrintHelp(const BSTree &T,int level);
void bstPrintCeng(const BSTree &T,vector<int> &v,queue<Elem> &q);//����δ�ӡ������
BSTree bstDeleteMin(BSTree &T,BSTree &min);//ɾ��Сֵ���,������Сֵ����min,ͬʱ����ɾ����Сֵ����������ĸ����
BSTree bstDeleteHelp(BSTree &T,const Elem &it,BSTree &t);

int main(void)
{
    int a[]={80,82,85,75,82,68,71,77,88,100,100,500,499,60,4565,1000,599};
    BSTree bst;
    bstCreat(bst);
    for(int i=0;i<(int)sizeof(a)/(int)sizeof(int);i++)
    {
        bstInsert(bst,a[i]);
    }
    bstPrint(bst);
    if(bstFind(bst,88))
        cout<<"Found!"<<endl;
    else
        cout<<"Not Found!"<<endl;
    bstInterval(bst,70,600);
    bstDelete(bst,88);
    bstPrint(bst);
    if(bstFind(bst,88))
        cout<<"Found!"<<endl;
    else
        cout<<"Not Found!"<<endl;
    bstClear(bst);
    return 0;
}

bool lt(const Elem &k,const Elem &e)
{
    return k<e;
}
bool gt(const Elem &k,const Elem &e)
{
    return k>e;
}
bool eq(const Elem &k,const Elem &e)
{
    return k==e;
}
bool bstCreat(BSTree &T)
{
    T=NULL;
    return true;
}
bool bstClear(BSTree &T)
{
    if(NULL==T)
        return false;
    bstClear(T->lc);
    bstClear(T->rc);
    free(T);
    T=NULL;
    return true;
}
int bstGetSize(BSTree &T)
{
    if(NULL==T)
        return 0;
    else
        return 1+bstGetSize(T->lc)+bstGetSize(T->rc);
}
int bstDepth(const BSTree &T)
{
    if(NULL==T)
        return 0;
    int left=1,right=1;

    left+=bstDepth(T->lc);
    right+=bstDepth(T->rc);
    return right>left?right:left;
}
bool bstInsert(BSTree &T,const Elem &it)
{
    if(NULL==T)
    {
        BST *temp=(BST *)malloc(sizeof(BST));
        if(temp)
        {
            temp->data=it;
            temp->lc=NULL;
            temp->rc=NULL;
            T=temp;
        }
        return true;
    }
    if(T->data<=it)
        bstInsert(T->rc,it);
    else
        bstInsert(T->lc,it);
    return true;
}
bool bstPrint(const BSTree &T)
{
    int i,j=0;
    if(NULL==T)
        return false;
    cout<<"��������ʾ��ʽ   1----��ͨ������ʾ��2-----�����������ʾ"<<endl;
    cin>>i;
    if(1==i)
        bstPrintHelp(T,0);
    else
    {
        queue<Elem>q;
        vector<int>v;
        bstPrintCeng(T,v,q);
        for(j;j<v.size();j++)
        {
            for(i=0;i<v[j];i++)
            {
                cout<<q.front()<<"   ";
                q.pop();
            }
            cout<<endl;
        }
    }
    return true;
}
void bstPrintCeng(const BSTree &T,vector<int> &v,queue<Elem> &q)
{
    queue<BSTree>temp;
    int i=0,temp1,temp2;
    temp.push(T);
    v.push_back(1);
    while(!temp.empty())
    {
        temp1=v[i];
        temp2=0;
        while(temp1)
        {
            q.push(temp.front()->data);
            if(temp.front()->rc!=NULL)
            {
                temp.push(temp.front()->rc);
                temp2++;
            }
            if(temp.front()->lc!=NULL)
            {
                temp.push(temp.front()->lc);
                temp2++;
            }
            temp.pop();
            temp1--;
        }
        v.push_back(temp2);
        i++;
    }

    return ;
}
void bstPrintHelp(const BSTree &T,int level)
{
    if(NULL==T)
        return ;
    bstPrintHelp(T->lc,level+1);
    for(int i=0;i<level;i++)
        cout<<"   ";
    cout<<T->data<<endl;
    bstPrintHelp(T->rc,level+1);
    return ;
}
bool bstInterval(BSTree &T,const Elem &a,const Elem &b)
{
    if(NULL==T)
        return false;

    if(T->data>=a&&T->data<=b)
    {
        bstInterval(T->lc,a,b);
        cout<<T->data<<endl;
        bstInterval(T->rc,a,b);
    }
    else if(T->data<a)
        bstInterval(T->rc,a,b);
    else if(T->data>b)
        bstInterval(T->lc,a,b);
    return true;
}
bool bstFind(BSTree &T,const Elem &it)
{
    if(NULL==T)
        return false;
    if(eq(it,T->data))
        return true;
    else if(lt(it,T->data))
        return bstFind(T->lc,it);
    return bstFind(T->rc,it);
}
BSTree bstDeleteMin(BSTree &T,BSTree &min)
{
    if(NULL==T->lc)
    {
        min=T;
        return T->rc;
    }
    T->lc=bstDeleteMin(T->lc,min);
    return T;
}
BSTree bstDeleteHelp(BSTree &T,const Elem &it,BSTree &t)
{
    if(NULL==T)
        return NULL;
    if(lt(it,T->data))
        return bstDeleteHelp(T->lc,it,t);
    else if(gt(it,T->data))
        return bstDeleteHelp(T->rc,it,t);
    else
    {
        Elem x;
        T->rc=bstDeleteMin(T->rc,t);
        x=T->data;
        T->data=t->data;
        t->data=x;
    }
    return T;
}
bool bstDelete(BSTree &T,const Elem &it)
{
    BSTree t;
    bstDeleteHelp(T,it,t);
    if(!t)
        return false;
    free(t);
    return true;
}















