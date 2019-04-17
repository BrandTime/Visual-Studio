#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
static unsigned g_aPrimeList[] = {2,3,5,7,11,17,19,23,29,31,41,43,47,53,59,67,71,73,79,83,89,97};
int Montgomery(int n,int p,int m)    //�ɸ�����������ģ�㷨�����ں��������ж�
{ //���ټ���(n^e)%m��ֵ,�����ƽ����
  int k=1;
  n%=m;
  while(p!=1)
    {
     if(0!=(p&1))
        k=(k*n)%m;
        n=(n*n)%m;
        p>>=1;
    }
 return(n*k)%m;
}
__int64 qpow(int a,int b,int r)//������
{
    __int64 ans=1,buff=a;
	while(b)
	{
        if(b&1)ans=(ans*buff)%r;
		buff=(buff*buff)%r;
		b>>=1;
	}
    return ans;
}
bool Miller_Rabbin(int n,int a)//����������������
{
    int r=0,s=n-1,j;
	if(!(n%a))
    	return false;
	while(!(s&1))
	{
    	s>>=1;
		r++;
	}
    __int64 k=qpow(a,s,n);
	if(k==1)
	  return true;
    for(j=0;j<r;j++,k=k*k%n)
	  if(k==n-1)
     	  return true;

	return false;
}
bool IsPrime(int n)//�ж��Ƿ�������
{
    int tab[]={2,3,5,7};
	for(int i=0;i<4;i++)
	{
        if(n==tab[i])
		  return true;
        if(!Miller_Rabbin(n,tab[i]))
		  return false;
	}

	return true;
}
bool RabbinMillerTest( unsigned n )
{
    srand((unsigned)time(NULL));
    if (n<2)
    { // С��2���������Ǻ���Ҳ��������
	  throw 0;
	}
    const unsigned nPrimeListSize=sizeof(g_aPrimeList)/sizeof(unsigned);//��������Ԫ�ظ���
    for(int i=0;i<nPrimeListSize;++i)
	{// �����������е����Ե�ǰ���������ж�
	  if (n/2+1<=g_aPrimeList[i])
      {// ����Ѿ�С�ڵ�ǰ�������������һ��������
		  return true;
	  }
      if (0==n%g_aPrimeList[i])
	  {// ����Ϊ0��˵��һ����������
	    return false;
	  }
    }
    // �ҵ�r��m��ʹ��n = 2^r * m + 1;
	int r = 0, m = n - 1; // ( n - 1 ) һ���Ǻ���
	while ( 0 == ( m & 1 ) )
	{
        m >>= 1; // ����һλ
		r++; // ͳ�����ƵĴ���
	}
    const unsigned nTestCnt = 8; // ��ʾ���в��ԵĴ���
	for ( unsigned i = 0; i < nTestCnt; ++i )
	{ // ������������в��ԣ�
       int a = g_aPrimeList[ rand() % nPrimeListSize ];
	   if ( 1 != Montgomery( a, m, n ) )
	    {
          int j = 0;
		  int e = 1;
	      for ( ; j < r; ++j )
		  {
            if ( n - 1 == Montgomery( a, m * e, n ) )
			{
                break;
			}
            e <<= 1;
		  }
          if (j == r)
		  {
              return false;
		  }
		}
	}

	return true;
}


