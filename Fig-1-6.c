/*

 Created by Louis Murguia on 2019-03-20.

 Traduction of Fortran code:

      QUAD4

    This program reads the coefficients of a quadratic equation of
    the form
        A * X**2 + B * X + C = 0,
    and solves for the roots of the equation (Fortran 77 style).


   Source: Fortran for Scientists and Engineers, Chapman
           Figure 1-6
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {

    double a, b, c; // Valores de entrada
    double discr, x1, x2;
    int enter;

    printf("*****************************\n");
    printf("*   PROGRAM OF FIGURE 1-6   *\n");
    printf("*****************************\n");

    //  Get the coefficients of the quadratic equation.
    printf("\nEnter the coefficients A, B and C:\n");
    scanf("%lf %lf %lf", &a, &b, &c);

    //  Echo the coefficients to make sure they are entered correctly.
    printf("The coefficients are:\t%.2lf\t%.2lf\t%.2lf\n",a,b,c);

    //  Check the discriminant and calculate its roots.

    discr = pow(b,2) - 4*a*c;

    if (discr < 0) {
        printf("This equation has complex roots:\n");
        printf("\tX = %lf + i %lf\n", -b/(2*a), sqrt(fabs(discr))/(2*a) );
        printf("\tX = %lf - i %lf\n", -b/(2*a), sqrt(fabs(discr))/(2*a) );
    }
    else if (discr == 0) {
        printf("This equation has a single repeated real root:\n");
        printf("\tX = %lf\n", -b/(2*a));
    }

    else {
        printf("This equation has two distinct real roots:\n");
        printf("\tX = %lf\n", (-b + sqrt(fabs(discr)))/(2*a) );
        printf("\tX = %lf\n", (-b - sqrt(fabs(discr)))/(2*a) );
    }

    printf("\nPress [Enter] key to continue.");
    getchar();
    getchar();


    return 0;


}


