#include"class.h"
void Path1(Queue &q,int **a,int i,int j);
void Path2(Stack &s,int **a,int i,int j);
void Pathhelp(Queue &a,int i,int j);

int main(void)
{
	int a,b,**Mi,c,k;
	cout<<"请分别输入迷宫的长和宽：\n";
	cin>>c>>k;
	Mi=(int **)malloc(sizeof(int)*(k+2));
	for(a=0;a<k+2;a++)
		Mi[a]=(int *)malloc(sizeof(int)*(c+2));
	for(a=0,b=0;b<c+2;b++)
			Mi[a][b]=1;
	for(a=k+1,b=0;b<c+2;b++)
			Mi[a][b]=1;
	for(b=0,a=0;a<k+2;a++)
			Mi[a][b]=1;
	for(b=c+1,a=0;a<k+2;a++)
			Mi[a][b]=1;
	for(a=1;a<=k;a++)
		for(b=1;b<=c;b++)
		{
			cout<<"请输入第"<<a<<"行第"<<b<<"列迷宫格的值：\n";
			cin>>Mi[a][b];
		}
    Mi[c][k]=3;//将终点的值置为3
	for(a=0;a<k+2;a++)
	{
		for(b=0;b<c+2;b++)
			cout<<Mi[a][b]<<"  ";
		cout<<endl;
	}
	Stack s,s1;
	Path2(s,Mi,1,1);
    if(!Stack::Getflag())
        cout<<"无法走出该迷宫！\n";
    else
    {
        while(s.Pop(a,b))
        {
            s1.Push(a,b);
        }
        cout<<"走出迷宫的路线为：\n";
        s1.Print(1);
    }
	return 0;
}
void Path2(Stack &s,int **a,int i,int j)
{
    if(s.Getflag())
        return ;
    if(3==a[i][j])
    {
        s.Push(i,j);
        s.Setflag(true);
        return ;
    }
    if(a[i][j])
        return ;
    a[i][j]=2;
    s.Push(i,j);
    Path2(s,a,i+1,j+1);
    Path2(s,a,i+1,j);
    Path2(s,a,i,j+1);
    Path2(s,a,i+1,j-1);
    Path2(s,a,i-1,j+1);
    Path2(s,a,i,j-1);
    Path2(s,a,i-1,j);
    Path2(s,a,i-1,j-1);
    if(!s.Getflag())
    {
        s.Pop();
        a[i][j]=0;
    }
    return ;
}
void Pathhelp(Queue &a,int i,int j,int **a)
{
    a.Enqueue(i,j);
    Path(a,i,j);
}
void Path1(Queue &q,int **a,int i,int j)
{
    do
    {
    }while(q.Getlength()!=0)
}








