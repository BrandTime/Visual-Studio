#include<stdio.h>
#include<string.h>
#include<math.h>
int temperature(double a)
{
    const double KAIR=273.16;
    double she;
    she=5.0/9.0*(a-32.0);
    printf("���¶ȱ�ʾΪ�����¶�Ϊ:\n%.2f\n",she);
    printf("���¶ȱ�ʾΪ�����¶�Ϊ:\n%.2f\n",she+KAIR);

    return 0;
}
int main(void)
{
    double a;
    int status;
    while(1)
    {
        printf("������һ���Ի����±��ʾ���¶ȣ�\n");
        status=scanf("%lf",&a);
        if(status==0)
            break;
        temperature(a);

    }

    return 0;;
}
