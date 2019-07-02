/**************************************************************/
/********************     Box-Muller      *********************/
/**************************************************************/

/*  Purpose:
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
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*  Declaration of functions:
 *      randomBM
 *      */
void randomBM(double numbers[], int size);

#define PI 3.1415926535898
#define n 10000    // Number of values to generate

int main ()
{
    // Data dictionary: declare variable types & definitions
    double valuesBM[n];     // Array of random values obtained
                            // by randomBM

    /**********************************************************/

    // Set the seed
    srand48(time(NULL));

    // Get the random values using Box-Muller Transform
    randomBM(valuesBM, n);

    return 0;
}

/**************************************************************/

void randomBM(double numbers[], int size) {
    /*
     * Purpose:
     *  To generate random values according to Box & Muller.
     */

    // Data dictionary: declare variable types & definitions
    // double numbers[size] -->    Array of random numbers
    //                             using BM Transform
    double x1, x2;              // Random numbers (uniform dist)

    // Box-Muller Transform
    for (int i = 0; i < size; ++i) {
        // Generate two random values uniformly distributed
        // between 0 and 1
        x1 = drand48();
        x2 = drand48();

        // Generate the BM-random value
        numbers[i] = ( sqrt(-2*log(x1)) * cos(2*PI*x2) );
    }

}
