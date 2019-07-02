/***********************************************/
/************     Figure 7-10      *************/
/***********************************************/

/*
 *  Purpose:
 *      To declare data shared between subs random0 and seed.
 *      */

#include <stdlib.h>

int n = 9876;   // Shared seed

/***********************************************/
/***********************************************/

// Data dictionary:
//             Random number
void random0 ( double *ran ) {
    /*
     *  Purpose:
     *      Function to generate a pseudorandom number with a uniform
     *      distribution in the range 0. <= ran < 1.0
     *      */

//    Calculate next number
    n = (8121 * n + 28411) % 134456;

//    Generate random value from this number
    *ran = (double) n / 134456.0;

}   // end function random0

/***********************************************/
/***********************************************/

// Data dictionary:
//              Value to initialize sequence
void seed ( int iseed ) {
    /*
     *  Purpose:
     *      To set the seed for random number generator random0.
     *      */

//    Set seed
    n = abs( iseed );

}   // end function seed