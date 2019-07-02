/***********************************************/
/************     Figure 7-18      *************/
/***********************************************/

/*  Purpose:
 *      To calculate the average value of function "func" over the
 *      range [fist_value, last_value] by taking n evenly-spaced
 *      samples over the range, and averaging the results. Function
 *      "func" is passed to this routine via a dummy argument.
 *      */

double ave_value (double (*func)(double), double first_value, double last_value, int n) {
    /*  Data dictionary: declare argument types & definitions
     *      func            Function to be evaluated
     *      first_value     First value in range
     *      last_value      Last value in range
     *      n               Number of samples to average
     *      */

//    Data ditionary: declare local variable types & definitions
    double delta;       // Step size between samples
    double sum;         // Sum of values to average

//    Get step size.
    delta = ( last_value - first_value ) / (double) (n-1);

//    Accumulate sum.
    sum = 0.;
    for (int i = 0; i < n; ++i) {
        sum += (*func) ( (double) i * delta );
    }

//    Get average and return it.
    return sum / (double) n;

}   // end of function ave_value