//
// Created by Louis Murguia on 2019-03-26.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*  Purpose:
 *      This program solves for the roots of a quadratic equation of the
 *      form a*x^2 + b*x + c = 0. It calculates the answers regardless
 *      of the type of roots that the equation possesses.
 *      */

int main() {

//    Data dictionary: declare variable types, definitions, & units
    double a;                       // Coefficient of x^2 term of equation
    double b;                       // Coefficient of x term of equation
    double c;                       // Constant term of equation
    double discriminant;            // Discriminant of the equation
    double imag_part, real_part;    // Imaginary/Real part of equation
    // (for complex roots)
    double x1, x2;                  // First/Second solution of equation
    // (for real roots)
    char buf[BUFSIZ];               // Input buffer
    char *ptr;

//    Prompt the user for the coefficients of the equation
    printf("This program solves for the roots of a quadratic\n");
    printf("equation of the form A * X^2 + B * X + C = 0.\n");
    printf("Enter the coefficients:\n");

    printf("\tA: ");
    fgets(buf, BUFSIZ, stdin);
    a = strtod(buf, &ptr);

    printf("\tB: ");
    fgets(buf, BUFSIZ, stdin);
    b = strtod(buf, &ptr);

    printf("\tC: ");
    fgets(buf, BUFSIZ, stdin);
    c = strtod(buf, &ptr);

//    Echo back coefficients
    printf("The coefficients A, B, and C are:\t%.2lf\t%.2lf\t%.2lf\n", a, b, c);

//    Calculate discriminant
    discriminant = pow(b, 2) - 4. * a * c;

//    Solve for the roots, depending upon the value of the discriminant
    if ( discriminant > 0. ) {  // there are two real roots, so...

        x1 = ( -b + sqrt(discriminant) ) / ( 2. * a );
        x2 = ( -b - sqrt(discriminant) ) / ( 2. * a );
        printf("This equation has two real roots:\n");
        printf("\tX1 = %.2lf\n",x1);
        printf("\tX2 = %.2lf\n",x2);
    }

    else if ( discriminant < 0. ) { // there are complex roots, so...

        real_part = ( -b ) / ( 2. * a );
        imag_part = sqrt( fabs(discriminant) ) / ( 2. * a );
        printf("This equation has complex roots:\n");
        printf("\tX1 = %5.2lf + i %5.2lf\n", real_part, imag_part);
        printf("\tX2 = %5.2lf - i %5.2lf\n", real_part, imag_part);

    }

    else if ( discriminant == 0. ) {  // there is one repeated root, so...

        x1 = ( -b ) / ( 2. * a );
        printf("This equation has two identical real roots:\n");
        printf("\tX1 = X2 = %5.2lf\n", x1);

    }

    return 0;
}
