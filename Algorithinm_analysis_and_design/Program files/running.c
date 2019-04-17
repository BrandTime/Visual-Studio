#include<stdio.h>
const int S_PER_M=60;
const int S_PER_H=3600;
const double M_PER_K=0.62137;
int main(void)
{
    double distm,distk;
    int min,sec;
    int time;
    double rate,mtime;
    int msec,mmin;

    printf("This program is designed for converting your time for a metric race\n"
           "to a time for running a mile and to your average\n"
           "speed in miles per hour.\n"
           "Please enter in kilometer,the distance you have ran:\n");
    scanf("%lf",&distk);
    printf("Now, please enter the time you spent:\n");
    printf("Begin by entering the minutes:\n");
    scanf("%d",&min);
    printf("Next enter the seconds:\n");
    scanf("%d",&sec);

    distm=distk*M_PER_K;
    time=min*S_PER_M+sec;
    rate=distm/(double)time*S_PER_H;
    mtime=(double)time/distm;
    mmin=(int)mtime/S_PER_M;
    msec=(int)mtime%S_PER_M;

    printf("You ran %1.2f(%1.2f miles)km in %.2d min, %d sec.\n",
           distk,distm,min,sec);
    printf("That pace corresponds to running a mile in %d min, %d sec.\n",
           mmin,msec);
    printf("Your average speed was %1.2f mph.\n",rate);


    return 0;
}
