/**************************************************************/
/********************     Box-Muller      *********************/
/**************************************************************/

/** Purpose:
 *      To generate values from the standard normal distribution
 *      with mean 0 and standard deviation 1, using the standard
 *      Box-Muller transform.
 *
 *  Record of revisions:
 *      Date        Programmer          Description of change
 *      ====        ==========          =======================
 *      21/06/19    Louis C. Murguía    Original Code.
 *      01/07/19    Louis C. Murguía    No saving data in .txt.
 *                                      Enhancement of function
 *                                      randomBM.
 *      03/07/19    Louis C. Murguía    Transformed to a header.
 *                                      Removal of loops, i.e.
 *                                      recursion used.
 *                                      Name changed to: rndbm.
 */

/** Implements this interface    */
#include "rndbm.h"


/** Import needed interfaces    */
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdarg.h>



// Pi value
#define PI 3.1415926535898

/**************************************************************/
/**************************************************************/

/** Declaration of functions:
 *****************************
 */

/** For n values    */
static int recursiveBM(double *, int n);

/** For one value   */
static double boxMuller(void);

/** For the needed seed; only used one in the program   */
extern void setSeed(void);

/** The function used by the main program to obtain the numbers */
extern void randomBM(int , ...);

/**************************************************************/
/**************************************************************/

/** Definition of functions:
 *****************************
 */

extern void setSeed() {
    /** Set the seed once   */
    srand48( time(NULL) );
}


/**************************************************************/

extern void randomBM(int N, ...) {
    /*
     * Purpose:
     *  To generate random values according to Box & Muller.
     */

    // Create va_list variable
    va_list valist;

    // Initialize valist for N number of arguments
    va_start(valist, N);

    // Evaluate N and perform the corresponding operation
    if (N == 2) {
        // We need more than one value

        // Use the recursive function
        recursiveBM(va_arg(valist, double *), va_arg(valist, int));

    } else {
        // We only need one value
        double *ptr = va_arg(valist, double *);
        *ptr = boxMuller();

    }

    // Clean memory reserved for valist
    va_end(valist);

    // End of function
    return;
}


/**************************************************************/

static int recursiveBM(double *number, int n) {
    /** Recursive Function using Box-Muller Transform
     * Purpose:
     *  To generate random values according to Box & Muller.
     */

    // Data dictionary: declare variable types & definitions
    //      number        Array where the values are saved
    //      n             Number of values, i.e. size of array

    if (n > 0) {

        // Generate the BM-random value and save it
        number[n-1] = boxMuller();

        // Generate the next BM-random value
        recursiveBM(number, n-1);

    } else {

        // Generate the last BM-random value
        number[n] = boxMuller();

    }

    // End of function
    return 0;
}

/**************************************************************/

static double boxMuller() {
    /** Box-Muller Transform
     * Purpose:
     *  To generate a random value according to Box & Muller.
     */

    // Generate two random values uniformly distributed
    // between 0 and 1
    double x1 = drand48();
    double x2 = drand48();

    // Generate the BM-random value and return it
    return ( sqrt(-2*log(x1)) * cos(2*PI*x2) );
}
