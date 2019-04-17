#include"class.h"

int main(void)
{
    const int MAX=256;
    char buf[MAX];
    assoc vecc(512);
    while(cin>>buf)
        vecc[buf]++;
    Pair *p;
    assoc_iterator vex(vecc);
    while((p=vex())!=0)
    {
        cout<<p->name<<"F->"<<p->val<<endl;
        delete p->name;
    }
    return 0;
}
