/***********************************************/
/************     Figure 7-21      *************/
/***********************************************/

/*  Purpose:
 *      To test passing functions names as arguments.
 *      */

#include <stdio.h>
#include <stdlib.h>

/*  Declaration of function defined in Fig-7-20.c:
 *      funcs_as_arguments
 *      */
extern void funcs_as_arguments (double , double , void (*func) (double, double, double *), double *);

//  Declaration of functions to call
void prod (double, double, double *);
void sum (double, double, double *);

int main () {

//    Data dictionary: declare variable types & definitions
    double x;           // First value
    double y;           // Last value
    double result;      // Result
    char buff[BUFSIZ];  // Input buffer
    char *ptr;          // Buffer pointer

//    Get the x and y values
    printf("\tEnter x: ");
    fgets(buff, BUFSIZ, stdin);
    x = strtod(buff, &ptr);

    printf("\tEnter y: ");
    fgets(buff, BUFSIZ, stdin);
    y = strtod(buff, &ptr);

//    Calculate product
    funcs_as_arguments(x, y, prod, &result);
    printf("The product is %lf\n", result);

//    Calculate product and sum
    funcs_as_arguments(x, y, sum, &result);
    printf("The sum is %lf\n", result);

    return 0;
}

/***********************************************/
/***********************************************/

void prod (double x, double y, double *result) {
    /*
     *  Purpose:
     *      To calculate product of two real numbers.
     *      */

    /*  Data dictionary: declare argument types & definitions
     *      x           First value
     *      y           Last value
     *      result      Result (out)
     *      */

//    Calculate value.
    *result = x * y;

}   // end of function prod

/***********************************************/
/***********************************************/

void sum (double x, double y, double *result) {
    /*
     *  Purpose:
     *      To calculate sum of two real numbers.
     *      */

    /*  Data dictionary: declare argument types & definitions
     *      x           First value
     *      y           Last value
     *      result      Result (out)
     *      */

//    Calculate value.
    *result = x + y;

}   // end of function sum
