/**************************************************************/
/*****************     Brownian Dynamics      *****************/
/**************************************************************/

/** Purpose:
 *      To generate brownian dynamics with a given number of
 *      particles and calculate the Mean Squared Displacement
 *      (MSD)——using the Box-Muller transform to obtain random
 *      values.
 *
 *      Record of revisions:
 *      Date        Programmer          Description of change
 *      ====        ==========          =======================
 *      17/07/19    Louis C. Murguía    Original Code.
 *
 */


/** Implements this interface    */
#include "BrownianDynamics.h"

/** Import needed interfaces    */
#include "rndbm.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>


/** Data dictionary: declare global variable types & definitions.
 *****************************
 */
static const double dt = 0.0001;	// Size of step in time.
static const double D = 1.0;		// Diffusion coefficient.
static int POS;					// Number of steps/positions.
static int N;					// Number of particles.
static double **x = NULL;			// Position of all particles.
static double *msd = NULL;		// MSD for each moment.
static double cache;				// Temporarily saves values.
static int noAvg = 1;			// Number to average MSD.
bool valInitialized = false;		// Verifies the initialization.

/** Note: static variables are automatically initialized to
 * zero, thus, the position and number of particles are zero.
 */

/**************************************************************/
/**************************************************************/

/** Declaration of functions:
 *****************************
 */

/** Allocates memory.	*/
static void setMemory( void );

/** Free the memory after is used.	*/
static void freeMemory( void );

/** Initializes the particles' position uniformly.   */
static void setUniformDist( double , int );

/** Initializes the position of the particles according to a.  */
static void setInitialPosition( double );

/** Initializes the values needed to run the simulation.	*/
extern void setInitialValues(int* , int* , int* ,double* );

/** Scroll through each position.   */
static void eachPosition( int );

/** Scroll trough each particle and updating its position.  */
static void eachParticle( int , const int );

/** Save the MSD and positions. */
static void saveIt( int );

/**************************************************************/
/**************************************************************/

/** Definition of functions:
 *****************************
 */

extern void seed( void ) {
	/** The function is a wrapper for setSeed in rndbm.h.
	 */
	setSeed();
}
/** End of seed	*/

/**************************************************************/

static void setMemory(void) {
	/** Allocates the memory needed to save the position of
	 * particles and calculate the MSD.
	 */
	
	/** Allocate the memory of x:
	 *****************************
	 */
	// 1) For the number of positions (rows).
	x = (double **) calloc( POS, sizeof(double*) );
	
	// Check memory validity.
	if ( x == NULL ) {
		fprintf(stderr, "Memory allocation error: %s\n",
				strerror(errno) );
		exit(errno);
	}
	
	// 2) For the number of particles (columns).
	int row = 0;
	while (row < POS) {
		// Allocate.
		x[row] = (double*)calloc(N, sizeof(double) );
		
		// Check memory validity.
		if ( x[row] == NULL ){
			fprintf(stderr, "Memory allocation error: %s\n",
					strerror(errno) );
			exit(errno);
		}
		
		row++;
	}	// End of while.
	
	/** Allocate the memory of msd:
	 *****************************
	 */
	msd = (double*) calloc ( POS, sizeof(double) );
}
/** End of setMemory   */

/**************************************************************/

static void freeMemory( void ) {
	/** Frees the memory.	*/
	
	printf("\n\tReleasing memory...");
	int iRow;
	for (iRow =0 ; iRow < POS ; iRow++)
		free(x[iRow]);	// Free allocated memory for positions.
	free(x);				// Free the memory used for positions.
	free(msd);			// Free the memory used for MSD.
}
/** End of freeMemory	*/

/**************************************************************/

static void setUniformDist( double a, int part_num) {
    /** Sets the positions of particles uniformly distributed.
     */
    
    // Base Case
    if (part_num == N)
        return;
    
    // Position the particle (part_num)
    x[0][part_num] = (2*a/(N-1)) * (double)part_num - a;
    
    // Position the next particle (part_num + 1)
    setUniformDist( a, part_num + 1 );
    
}
/** End of setUniformDist   */

/**************************************************************/

static void setInitialPosition(double a) {
    /** Initializes the position of the particles according to a.
     * All positions are 0, or particles are evenly distributed in
     * the range [-a,a].
     */
    if (a == 0)
        return;
    else
        setUniformDist(a,0);
}
/** End of setInitialPosition   */

/**************************************************************/

extern void setInitialValues(int * noAverage, int * noPosition,
							 int * noParticles,
							 double * diameter) {
	/** Initializes the values needed to run the simulation:
	 *		noAverage:	number of executions in order to average
	 *					the MSD.
	 *		noPositions:	number of positions for all particles,
	 *					i.e. how many time.
	 *		noParticles: number of particles used in simulation.
	 *		diameter:	the particles' initial position will be
	 *					set uniformly distributed according to
	 *					this value.
	 */
	
	/** This MUST be called ONCE in order to set the seed in the
	 * program and use the random values (rndbm.h).	*/
	setSeed();
	
	// Set initial values.
	noAvg = *noAverage;
	POS = *noPosition;
	N = *noParticles;
	setMemory();
	setInitialPosition(*diameter);
	
	valInitialized = true;
}
/** End of setInitialValues.	*/

/**************************************************************/

static void eachPosition( int pos_num ) {
    /** Runs through all positions for each particle.
     *      - pos_num must start with 1;
     */

    // Base Case: returns to the calling function.
    if ( pos_num >= POS )
        return;
    
    /** Calculate the position and the MSD given by pos_num and
	 * go to the next one.
     */

    // Get the actual position of all particles & numerator of MSD.
    eachParticle( 0, pos_num );
	
	// Calculation of MSD.
	msd[pos_num] = msd[pos_num] + cache / (N * noAvg);
	cache = 0;	// Clear the cache.
    
    // Go to the next position.
    eachPosition( pos_num+1 );
    
}
/** End of eachPosition.    */

/**************************************************************/

static void eachParticle( int part_num, const int pos_num ) {
    /** Modify the position of each particle.
     *      - part_num must start with 0;
     *      - pos_num must start with 1;  */
    
    // Base Case: returns to the calling function.
	if ( part_num >= N ){
		return;}
    
    /** Modify the position of the actual particle, calculate the
	 * numerator of MSD and move to the next one.
	 */
    
    /** Data dictionary: declare variable types & definitions */
    double G;           // Random value (BM).
    
    // Get the random value using the Box-Muller Transform.
    randomBM(1, &G);
    
    // Modify the position.
    x[pos_num][part_num] = x[pos_num-1][part_num] + sqrt(2 * D * dt) * G;
	
	// Numerator of MSD
	cache = cache + pow( x[pos_num][part_num] - x[0][part_num], 2 );
    
    // Go to the next particle.
    eachParticle( part_num+1, pos_num );
    
}
/** End of eachParticle.    */

/**************************************************************/

static void saveIt(int num_file){
    
    /** Data dictionary: declare variable types & definitions */
    FILE *fpos;     		// Pointer to the file (for positions).
    FILE *fmsd;    		// Pointer to the file (for the MSD).
    int pos;        		// Index of position
    int part;       		// Index of particle
	char namefile[50];	// Name of the file to open.
	
	printf("\n\tSaving information...");
	// Concatenate the name of the file and the num_file and open
	// the files to write.
	sprintf(namefile, "position%d%s", num_file,".txt");
    fpos = fopen(namefile, "w");
	
	sprintf(namefile, "msd%d%s", num_file,".txt");
    fmsd = fopen(namefile, "w");
    
    // Verify if there was a problem opening the files
    if ( fpos == NULL || fmsd == NULL ) {
        fprintf(stderr, "Error opening a file: %s\n",
                strerror(errno) );
        exit(errno);
    }
    
    // Save the info.
    for ( pos = 0; pos < POS; ++pos) {
        // Write the MSD
        fprintf(fmsd, "%lf\t%lf\n", pos*dt , msd[pos] );
        
        // Write the time
        fprintf(fpos, "%lf\t", pos*dt);
        
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

/**************************************************************/

extern void startDynamic(void){
	/** Initiates the dynamic and verifies the needed information
	 * to calculate the positions of the particles and compute
	 * the Mean Squared Displacement.
	 */
	
	/** Data dictionary: declare variable types & definitions.*/
	int loop = 0;		// Looping variable.
	clock_t start, end;	// Time variables.
	double elapsedTime;		// Time of compute.
	
	/** Verify if the values are initialized.	*/
	if (valInitialized == false) {
		fprintf(stdout, "\tValues have not been initialized.");
		exit(1);
	}
	
	/** Start the simulation.	*/
	start = clock();
	printf("\n\t Brownian Dynamics Started\n"
		   "\t==========================\n");
	
	while ( loop < noAvg ) {
		
		/** Compute all positions & Mean Square Displacement. */
		eachPosition(1);
		
		/** Save the information.	*/
		//saveIt(loop+1);	// Saves positions & MSD at every loop.
		
		// Print the status.
		printf("\r%d of %d is done.", loop+1, noAvg );
		fflush(stdout);
		
		loop++;
	}	// Enf of while loop.
	
	saveIt(noAvg); // Saves the last positions & the averaged MSD.
	
	/** Frees the memory used.	*/
	freeMemory();
	
	/** Calculate the time of compute.	*/
	end = clock();
	elapsedTime = ( (double) (end - start) ) / CLOCKS_PER_SEC;
	printf("\n\tTime elapsed: %.2lf seconds.\n", elapsedTime);
}
/** End of startDynamic.     */
