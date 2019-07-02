/***********************************************/
/************     Figure 7-16      *************/
/***********************************************/

#include <math.h>

/*  The smallest value for which
 *  to calculate sin(x)/x
 *  */
#define EPSILON 1.0E-30

double sinc (double x) {
    /*  Purpose:
     *      To calculate the sinc function
     *          sinc(x) = sin(x) / x
     *          */

//    Data dictionary: declare argument types & definitions
    // double x     Value for which to evaluate sinc
    double sinc;    // Output value sinc(x)

//    Check to see if ABS(x) > EPSILON.
    if ( fabs(x) > EPSILON )
        sinc = sin(x) / x;
    else
        sinc = 1.;

    return sinc;

}   // end of function sinc