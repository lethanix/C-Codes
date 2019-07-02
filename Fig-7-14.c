/***********************************************/
/************     Figure 7-14      *************/
/***********************************************/

/*  Purpose:
 *      Program to test function quadf.
 *      */

#include <stdio.h>
#include <stdlib.h>

/*  Declaration of function defined in Fig-7-13.c:
 *      quadf
 *      */
extern double quadf ( double , double , double , double );

int main() {

//    Data dictionary: declare variable types & definitions
    double a, b, c, x;      // Declare local variables
    char buff[BUFSIZ];      // Input buffer
    char *ptr;              // Buffer pointer

//    Get input data.
    printf("Enter quadratic coefficients:\n\ta: ");
    fgets(buff, BUFSIZ, stdin);
    a = strtod(buff, &ptr);

    printf("\tb: ");
    fgets(buff, BUFSIZ, stdin);
    b = strtod(buff, &ptr);

    printf("\tc: ");
    fgets(buff, BUFSIZ, stdin);
    c = strtod(buff, &ptr);

    printf("Enter location at which to evaluate equation: ");
    fgets(buff, BUFSIZ, stdin);
    x = strtod(buff, &ptr);

//    Write out result.
    printf("quadf(%10.4lf) = %12.4lf\n", x, quadf(x,a,b,c) );

    return 0;

}