#include<stdio.h>
#include<string.h>
#include<math.h>
int temperature(double a)
{
    const double KAIR=273.16;
    double she;
    she=5.0/9.0*(a-32.0);
    printf("该温度表示为摄氏温度为:\n%.2f\n",she);
    printf("该温度表示为开氏温度为:\n%.2f\n",she+KAIR);

    return 0;
}
int main(void)
{
    double a;
    int status;
    while(1)
    {
        printf("请输入一个以华氏温标表示的温度：\n");
        status=scanf("%lf",&a);
        if(status==0)
            break;
        temperature(a);

    }

    return 0;;
}
