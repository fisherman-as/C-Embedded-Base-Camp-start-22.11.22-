/*
Yabanzhi Aleksey

variant #6
*/

#include <stdio.h>
#include <stdlib.h>
#include "math.h"

int main()
{
    const double pi=3.14159265359; //The PI constant

    for (int i=0;i<5;i++) //here we make 5 countings of z1 and z2 with different input data
    {
        double a=(double)((pi/12)*i);   //here we created the angle (a) for each counting with a step of 15 grades
        double z1=cos(a)+cos(2*a)+cos(6*a)+cos(7*a);
        double z2=4*cos(a/2)*cos(5*a/2)*cos(4*a);
        char* end; //this variable keeps the ending, for comfortable reading of results after executing the program
            if ((i+1)==1)
                {
                    end="st";
                }
            else if ((i+1)==2||(i+1)==3)
                {
                    end="d";
                }
            else
                {
                    end="th";
                }
 /*
                        The PRINTF block:
        Here we print the result for each of 5-th countings.
        Besides, here we print the counting result of the each part of the expression for mentor to check it out easy.
 */
        {
        printf("result %d for a=%d(grad) =%.4f(rad):\r\n",i+1,(int)(a*180/pi),a);
        printf("-----\r\n");
        printf("z1=%.4f         =cos(a)+cos(2*a)+cos(6*a)+cos(7*a)\r\n",z1);
        printf("\r\n");
        printf("z2=%.4f         =4*cos(a/2)*cos(5*a/2)*cos(4*a)\r\n",z2);
        printf("--------------------------------------------------------------------------------------------------\r\n");
  /*
                        PRINTF block end
 */
        }
    }
    return 0;
}
