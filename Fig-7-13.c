/***********************************************/
/************     Figure 7-13      *************/
/***********************************************/

#include <math.h>

double quadf ( double x, double a, double b, double c) {
    /*
     *  Purpose:
     *      To evaluate a quadratic polynomial of the form
     *          quadf = a * x^2 + b * x + c
     *          */

    /*  Data dictionary: declare argument definitions
     *      x   Value to evaluate expression for
     *      a   Coefficient of x^2 term
     *      b   Coefficient of x term
     *      c   Coefficient of constant term
     *      */

//    Evaluate expression and return it
    return a * pow(x,2) + b * x + c;

}   // end of function quadf