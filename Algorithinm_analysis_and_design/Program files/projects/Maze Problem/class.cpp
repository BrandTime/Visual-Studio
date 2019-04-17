#include"class.h"
bool Queue::Enqueue(int i,int j)
{
    Node *temp=new Node(i,j);
    if(!temp)
        return false;
    if(head==NULL)
        tail=head=cur=temp;
    else
    {
        tail->next=temp;
        tail=temp;
    }
    tail->pre=cur;
    length++;
    return true;
}
int Queue::Getlength()
{
    return length;
}
bool Queue::Dequeue()
{
    if(!head)
        return false;
    if(cur->next!=NULL)
        cur=cur->next;
    return true;
}
void Queue::Reflag()
{
    flag=(flag==false)?true:false;
}
void Path(int **a,int i,int j,const Queue &q)
{
    if(!q.head)
        return ;
    if(a[i][j]!=3)
        return ;
    Node *temp=q.cur;
    while(temp!=NULL)
    {
        cout<<"\t("<<temp->x<<","<<temp->y<<")";
        temp=temp->pre;
    }
}

int Stack::GetLength()
{
    return length;
}
bool Stack::Push(const Elem &x_,const Elem &y_)
{
    Node *temp;
    temp=new Node;
    if(!temp)
        return false;
    temp->x=x_;
    temp->y=y_;
    temp->next=top;
    top=temp;
    length++;
    return true;
}
bool Stack::Pop(Elem &x_,Elem &y_)
{
    if(!top)
        return false;
    Node *temp=top;
    x_=temp->x;
    y_=temp->y;
    top=top->next;
    delete temp;
    length--;
    return true;
}
bool Stack::Pop()
{
    if(!top)
        return false;
    Node *temp=top;
    top=top->next;
    delete temp;
    length--;
    return true;
}
bool Stack::Print(int i)
{
    if(!top)
        return false;
    Node *temp;
    cout<<"<  ";
    while(top)
    {
        temp=top;
        cout<<"("<<temp->x-i<<", "<<temp->y-i<<") ";
        top=top->next;
        delete temp;
    }
    cout<<"  >";
    top=NULL;
    length=0;
    return true;
}

