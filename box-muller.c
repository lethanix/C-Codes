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
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

/*  Declaration of functions:
 *      randomBM
 *      */
double * randomBM();
double getNumber();

#define PI 3.1415926535898
#define n 10000    // Number of values to generate

// Error number
extern int errno;

int main ()
{
    // Data dictionary: declare variable types & definitions
    double *pBM;            // Pointer to array of random values
                            // obtain by randomBM
    FILE *fp;               // Pointer to file (uniform dist)
    FILE *fpBM;             // Pointer to file (normal dist)
    bool opened = false;    // Boolean value to verify if the
                            // file opened (uniform dist)
    bool openedBM = false;  // Boolean value to verify if the
                            // file opened (normal dist)
    int status = 0;         // I/O status
    char msg[80];           // Error message

    /**************************************************************/

    // Open/create the files, and check for errors on open.
    opened = ( fp = fopen("rndUniform.txt", "w") );
    openedBM = ( fpBM = fopen("rndNormal.txt", "w") );

    if (opened == true && openedBM == true) {
        // Files opened successfully.

        // Set the seed
        srand48(time(NULL));

        // Get the random values using Box-Muller Transform
        pBM = randomBM();

        // Save the values in files
        for (int i = 0; i < n; ++i) {
            fprintf(fpBM, "%lf\n", pBM[i]);
            fprintf(fp, "%lf\n", drand48());
        }

    } else {  // File did not opened. An error occurred.
         status = errno;
         strcpy(msg, strerror(status));
         fprintf(stderr,
                 "Can't open the file: %s\n", msg);
         exit(status);
    }

     // Close files
    fclose(fp);
    fclose(fpBM);

    return 0;
}

/**************************************************************/

double * randomBM() {
    /*
     * Purpose:
     *  To generate n-random values according to Box & Muller.
     */

    // Data dictionary: declare variable types & definitions
    static double numbers[n];   // Array of random numbers
                                // using BM Transform
    double x1, x2;              // Uniformly random values

    // Box-Muller Transform
    for (int i = 0; i < n; ++i) {
        // Generate two random values uniformly distributed
        // between 0 and 1
        x1 = drand48();
        x2 = drand48();

        // Generate the BM-random value
        numbers[i] = ( sqrt(-2*log(x1)) * cos(2*PI*x2) );
    }

    return numbers;

}
