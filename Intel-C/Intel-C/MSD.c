/**************************************************************/
/********************     MSD Serial      *********************/
/**************************************************************/

/** Purpose:
 *      To obtain the Mean Square Displacement (MSD) of N parti-
 *      cles, with brownian motion, without parallelization.
 *
 *  Record of revisions:
 *      Date        Programmer          Description of change
 *      ====        ==========          =======================
 *      04/07/19    Louis C. Murguía    Original code.
 */

#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "rndbm.h"


/** Declaration of macros:
 *****************************
 */
 #define POS 10000      // Number of steps/positions.
 #define N 1000         // Number of particles.


/** Declaration of functions:
 *****************************
 */
 void eachPosition( double [POS][N], int );
 void eachParticle( double [POS][N], int , const int );
 void MSD( double [POS][N], double * );
 void saveIt(double [POS][N], double *);


/** Data dictionary: declare global variable types & definitions.
 *****************************
 */
 static const double dt = 0.0001;       // Size of step in time.
 static const double D = 1.0;           // Diffusion coefficient.


/**************************************************************/
/**************************************************************/


int main () {

    /** Data dictionary: declare variable types & definitions.*/
    static double x[POS][N];        // Position of all particles.
    static double msd[POS];         // MSD for each moment.
    
    /** Note: static variables are automatically initialized to
     * zero, thus, the position of all the particles and the MSD
     * are zero.
     */

    /** Set the seed for randomBM (only used once)  */
    setSeed();

    /** Compute all positions. */
    eachPosition(x, 1);

    /** Get the Mean Square Displacement for each time. */
    MSD(x, msd);

    /** Save the info.  */
    saveIt(x, msd);

    return 0;
}


/**************************************************************/
/**************************************************************/


/** Definition of functions:
 *****************************
 */

void eachPosition( double x[POS][N], int pos_num ) {
    /** Runs through all positions for each particle.
     *      - pos_num must start with 1;
     */
    
    // Base Case: returns to the calling function.
    if ( pos_num > POS )
        return;
    
    /** Calculate the position given by pos_num and go to the
     * next one.
     */

    // Get the actual position for all particles.
    eachParticle(x, 0, pos_num);

    // Go to the next position.
    eachPosition(x, pos_num+1);

}
    /** End of eachPosition.    */


/**************************************************************/


void eachParticle( double x[POS][N], int part_num,
        const int pos_num ) {
    /** Modify the position of each particle.
     *      - part_num must start with 0;
     *      - pos_num must start with 1;  */
    
    // Base Case: returns to the calling function.
    if ( part_num > N )
        return;

    /** Modify the position of the actual particle and move
    * to the next one. */
    
    /** Data dictionary: declare variable types & definitions */
    double G;           // Random value (BM).

    // Get the random value using the Box-Muller Transform.
    randomBM(1, &G);

    // Modify the position.
    x[pos_num][part_num] = x[pos_num-1][part_num] +
                            sqrt(2 * D * dt) * G;

    // Go to the next particle.
    eachParticle(x, part_num+1, pos_num);

}
    /** End of eachParticle.    */


/**************************************************************/


void MSD( double x[POS][N], double *result ) {
    /** Calculate the Mean Square Root for each time.   */

    /** Data dictionary: declare variable types & definitions */
    double cache = 0;       // Used to temporary save values.
    int pos;                // Index of position
    int part;               // Index of particle

    // Reset back to zero for precaution.
    memset(result, 0, POS);
    
    for ( pos = 1; pos < POS ; ++pos) {
        for ( part = 0; part < N; ++part) {
            cache = cache + pow( x[pos][part] - x[0][part], 2 );
        }
        result[pos] = cache / N;
        cache = 0;
    }

}
    /** End of MSD.     */


/**************************************************************/


void saveIt(double x[POS][N], double *m){

    /** Data dictionary: declare variable types & definitions */
    FILE *fpos;     // Pointer to the file for the positions.
    FILE *fmsd;     // Pointer to the file for the MSD.
    int pos;        // Index of position
    int part;       // Index of particle

    // Open the files to write.
    fpos = fopen("positions2.txt", "w");
    fmsd = fopen("msd2.txt", "w");
    
    // Verify if there was a problem opening the files
    if ( fpos == NULL || fmsd == NULL ) {
        fprintf(stderr, "Error opening a file: %s\n",
                strerror(errno) );
        exit(errno);
    }

    // Save the info.
    for ( pos = 0; pos < POS; ++pos) {
        // Write the MSD
        fprintf(fmsd, "%lf\t%lf\n", pos*dt , m[pos] );
        
        for ( part = 0; part < N; ++part) {
            // Write the positions of all particles
            fprintf(fpos, "%lf\t", x[pos][part]);
        }
        fprintf(fpos, "\n");
    }

    fclose(fpos);
    fclose(fmsd);

}
    /** End of saveIt.     */
