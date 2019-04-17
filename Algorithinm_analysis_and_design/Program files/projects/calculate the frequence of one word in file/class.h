#ifndef CLASS_H_INCLUDED
#define CLASS_H_INCLUDED

#include<iostream>
#include<string.h>
using namespace std;

struct Pair
{
    char *name;//单词
    int val=0;//单词出现的次数
};
class assoc_iterator;
class assoc
{
    int max;//vec数组允许装的最大值
    int free;//vec数组内装的单词数
    Pair *vec;
    friend class assoc_iterator;
public:
    assoc(int i)
    {
        max=(i>16)?i:16;
        free=0;
        vec=new Pair[max];
    }
    int& operator[](char *a);
};
class assoc_iterator
{
    assoc *ass;
    int i;
public:
    assoc_iterator(assoc &a)
    {
        ass=&a;
        i=0;
    }
    Pair* operator()()
    {
        return (i<ass->free)?(&ass->vec[i++]):0;
    }
};
int& assoc::operator[](char *p)
{
    Pair *pp;
    for(pp=vec;pp<vec+free;pp++)
        if(strcmp(p,pp->name)==0)
            return pp->val;
    if(free==max)
    {
        Pair *temp=new Pair[max*2];
        for(int i=0;i<max;i++)
            temp[i]=vec[i];
        delete vec;
        vec=temp;
        max*=2;
    }
    pp=&vec[free++];
    pp->name=new char[strlen(p)+1];
    strcpy(pp->name,p);
    return pp->val;
}

#endif // CLASS_H_INCLUDED

























