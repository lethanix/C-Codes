/*
 Created by Louis Murguia on 2019-03-19.

 Traduction of Fortran code:

   Solve quadratic equation in Fortran I

   Source: Fortran for Scientists and Engineers, Chapman
           Figure 1-5
*/


#include <stdio.h>
#include <math.h>

int main() {

    double a, b, c; // Valores de entrada
    double discr, x1, x2;

    printf("*****************************\n");
    printf("*   PROGRAM OF FIGURE 1-5   *\n");
    printf("*****************************\n");

    scanf("%lf %lf %lf", &a, &b, &c);

    discr = pow(b,2) - 4*a*c;
    
    if (discr < 0){
        x1 = -b/(2*a);
        x2 = sqrt( fabs(discr) )/(2*a);
        printf("\tX = %lf + i %lf \n",x1,x2);
        printf("\tX = %lf - i %lf \n",x1,x2);
    }
    else if (discr == 0){
        x1 = -b/(2*a);
        printf("\tX = %lf \n", x1);
    }
    else {
        x1 = -b + sqrt( fabs(discr) )/(2*a);
        x2 = -b - sqrt( fabs(discr) )/(2*a);
        printf("\tX1 = %lf \n",x1);
        printf("\tX2 = %lf \n",x2);
    }

    return 0;

}
