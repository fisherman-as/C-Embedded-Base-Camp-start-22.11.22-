/*
Yabanzhi Aleksey

variant #6
*/

#include <stdio.h>
#include <stdlib.h>
#include "math.h"

int main()
{
    const double pi=3.14159265359;

for (int i=0;i<5;i++)
{
double a=(double)((pi/12)*i);
double z1=cos(a)+cos(2*a)+cos(6*a)+cos(7*a);
double z2=4*cos(a/2)*cos(5*a/2)*cos(4*a);
char* end;
if ((i+1)==1)
    end="st";
else if ((i+1)==2|(i+1)==3)
    end="d";
else
    end="th";


printf("The %d-%s time:\r\n",i+1,end);
printf("a=%d(grad) =%.3f(rad)\r\n",(int)(a*180/pi),a);
printf("-----\r\n");
printf("z1=%.3f       =cos(a)+cos(2*a)+cos(6*a)+cos(7*a)\r\n",z1);
double x2=cos(a);
printf("            cos(a)=%.3f;    ",x2);
double x3=cos(2*a);
printf("cos(2*a)=%.3f;  ",x3);
double x4=cos(6*a);
printf("cos(6*a)=%.3f;  ",x4);
double x5=cos(7*a);
printf("cos(7*a)=%.3f;\r\n",x5);

printf("\r\n");
printf("z2=%.3f       =4*cos(a/2)*cos(5*a/2)*cos(4*a)\r\n",z2);
double y2=cos(a/2);
printf("            cos(a/2)=%.3f;  ",y2);
double y3=cos(5*a/2);
printf("cos(5*a/2)=%.3f;    ",y3);
double y4=cos(4*a);
printf("cos(4*a)=%.3f;\r\n",y4);

printf("--------------------------------------------------------------------------------------------------\r\n");


}
    return 0;
}
