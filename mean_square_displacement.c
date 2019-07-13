/**************************************************************/
/********************     MSD Serial      *********************/
/**************************************************************/

/** Purpose:
 *      To obtain the Mean Square Distance (MSD) of n particles,
 *      with brownian motion, without parallelization.
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

#include "rndbm.h"


/**************************************************************/
/**************************************************************/


/** Declaration of macros:
 *****************************
 */
 #define POS 10000      // Number of steps/positions.
 #define N 1000         // Number of particles.


/** Declaration of functions:
 *****************************
 */
 int eachPosition( double [POS][N], int );
 int eachParticle( double [POS][N], int , const int * );
 void MSD( double [POS][N], double * );
 void saveIt(double [POS][N], double *);


/** Data dictionary: declare global variable types & definitions.
 *****************************
 * */
 static const double dt = 0.0001;       // Size of step in time.
 static const double D = 1.0;           // Diffusion coefficient.



/**************************************************************/
/**************************************************************/


int main () {

    /** Data dictionary: declare variable types & definitions.*/
//    static const int t=(int)(steps*dt); // Resultant time.
    static double x[POS][N];        // Position of all particles.
    static double msd[POS];         // MSD for each moment.
    /** Note: static variables are automatically initialized to
     * zero, thus, the position of all particles are and the MSD
     * are zero.  */

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

int eachPosition( double x[POS][N], int pos_num ) {
    /** Runs through all positions for each particle.
     *      - pos_num must start with 1;    */

    /** Data dictionary: declare variable types & definitions.*/
    int act_pos;        // The actual position.

    // Verify the actual position (number of steps) and
    // implement the adequate code.
    act_pos = POS - pos_num;

    if ( act_pos >= 0 ) {
        /** Calculate the position given by post_num and move
         * to the next one.     */

        // Get the position of the actual step for all particles.
        eachParticle(x, 0, &pos_num);

        // Go to the next position.
        eachPosition(x, pos_num+1);
    }

    // Return to main
    return 0;

}   /** End of eachPosition.    */


/**************************************************************/


int eachParticle( double x[POS][N], int part_num,
        const int *which_pos ) {
    /** Modify the next position of each particle.
     *      - part_num must start with 0;
     *      - which_pos must start with 1;  */

    /** Data dictionary: declare variable types & definitions */
    double G;           // Random value (BM).
    int which_part;     // The actual particle.

    // Verify which particle will be modified and implement the
    // corresponding code.
    which_part = N - part_num;

    if ( which_part > 0 ) {
        /** Modify the position of the actual particle and move
         * to the next one. */

        // Get the random value using the Box-Muller Transform.
        randomBM(1, &G);

        // Modify the position.
        x[*which_pos][which_part] = x[*which_pos-1][which_part]
                + sqrt(2.* D * dt) * G;

        // Go to the next particle.
        eachParticle(x, part_num+1, which_pos);

    } else {
        /** Modify the position of the last particle.   */

        // Get the random value using the Box-Muller Transform.
        randomBM(1, &G);

        // Modify the position.
        x[*which_pos][which_part] = x[*which_pos-1][which_part]
                                    + sqrt(2.* D * dt) * G;

    }

    // Return to eachPosition.
    return 0;

}   /** End of eachParticle.    */


/**************************************************************/


void MSD( double x[POS][N], double *result ) {
    /** Calculate the Mean Square Root for each time.   */

    /** Data dictionary: declare variable types & definitions */
    double cache = 0;       // Used to temporary save values.

    // Reset back to zero for precaution.
    memset(result, 0, POS);

    for (int pos = 1; pos < POS ; ++pos) {
        for (int part = 0; part < N; ++part) {
            cache = cache + pow( x[pos][part] - x[0][part], 2 );
        }
        result[pos] = cache / N;
        cache = 0;
    }

}   /** End of MSD.     */


/**************************************************************/


void saveIt(double x[POS][N], double *m){

    /** Data dictionary: declare variable types & definitions */
    FILE *fpos;      // Pointer to the file for the positions.
    FILE *fmsd;      // Pointer to the file for the MSD.

    // Open the files to write.
    fpos = fopen("positions.txt", "w");
    fmsd = fopen("msd.txt", "w");

    // Save the info.
    for (int pos = 0; pos < POS; ++pos) {
        // Write the MSD
        fprintf(fmsd, "%5d\t%lf\n", pos, m[pos] );
        for (int part = 0; part < N; ++part) {
            // Write the positions of all particles
            fprintf(fpos, "%lf\t", x[pos][part]);
        }
        fprintf(fpos, "\n");
    }

    fclose(fpos);
    fclose(fmsd);

}   /** End of saveIt.     */
