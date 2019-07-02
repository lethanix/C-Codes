/***********************************************/
/************     Figure 7-19      *************/
/***********************************************/

/*  Purpose:
 *      To test function ave_value by calling it with a user-defined
 *      function my_function.
 *      */

#include <stdio.h>

/*  Declaration of function defined in Fig-7-18.c:
 *      ave_value   Average value of function
 *      */
extern double ave_value (double (*func)(double), double , double , int );

//  Declaration of user-defined function my_function
double my_function(double);

int main() {

//    Data dictionary: declare local variable types & definitions
    double ave;     // Average of my_function

//    Call function with func = my_function.
    ave = ave_value( my_function, 0., 1., 101);
    printf("The average value of my_function between 0. and 1. is %16.6lf.\n",
            ave);

    return 0;
}

/***********************************************/
/***********************************************/

double my_function (double x) {
    return 3. * x;
}