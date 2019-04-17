#include<iostream>
using namespace std;
#define N 20
main()
{
    int a[N],n,i,count=0,s=0;
    cout<<"Please input an integer"<<endl;
    cin>>n;
    for(i=0;i<N;i++)
        a[i]=0;
    for(i=1;i<n;i++)
    {
        if(n%i==0)
          {
            a[count]=i;
            count++;
          }
    }
    for(count-1;count>=0;count--)
        s+=a[count];
    if(s==n)
       {
        for(i=0;i<=N;i++)
            if(a[i]!=0&&a[i]!=n)
            {
              cout<<a[i];
              if(a[i+1]!=0)
                cout<<"+";
            }
            cout<<"="<<n<<endl;
       }
       else cout<<"This integer is not a perfect number!"<<endl;
}
