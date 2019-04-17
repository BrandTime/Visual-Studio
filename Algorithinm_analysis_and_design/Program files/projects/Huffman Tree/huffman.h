#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED

#include<iostream>
using namespace std;
typedef int Elem;
class HuffNode
{
public:
    virtual ~HuffNode(){}
    virtual int weight()=0;
    virtual bool isleaf()=0;
};

class LeafNode:public HuffNode
{
public:
    LeafNode(const E& val,int freq)
    {
        it=val;
        wgt=freq;
    }
    int weeight()
    {
        return wgt;
    }
    Elem val()
    {
        return it;
    }
    bool isleaf()
    {
        return true;
    }
private:
    int wgt;
    Elem it;
};

class InitNode:public HuffNode
{
public:
    InitNode(HuffNode *l,HuffNode *r)
    {
        lc=l;
        rc=r;
        wgt=l->weight()+r->weight();
    }
    ~InitNode(){}
    bool isleaf()
    {
        return false;
    }
    int weight()
    {
        return wgt;
    }
    void setleft(HuffNode *b)
    {
        lc=(HuffNode *)b;
    }
    void setright(HuffNode *a)
    {
        rc=(HuffNode *)a;
    }
    HuffNode* left()const
    {
        return lc;
    }
    HuffNode* right()const
    {
        return rc;
    }
private:
    HuffNode *lc;
    HuffNode *rc;
    int wgt;
};
class HuffTree
{
private:
    HuffNode *root;
public:
    HuffTree(Elem &val,int freq)
    {
        root=new LeafNode(val,freq);
    }
    HuffNode(HuffTree *l,HuffTree *r)
    {
        root=new InitNode(l->root,r->root);
    }
    ~HuffTree(){}
    HuffNode* root()
    {
        return root;
    }
    int weight()
    {
        return wgt;
    }
};

#endif // HUFFMAN_H_INCLUDED




















