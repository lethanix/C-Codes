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

// Given values.
static const double T		= 298.0;		// Temperature in kelvin.
static const double eta	= 1e-3;		// Viscosity.
static const double stks	= 0.5e-6;	// Stokes constant.
static const double Kb 	= 1.38e-23;	// Boltzmann constant.
static const double dt 	= 1e-4;		// Size of step in time.

// Values that change according to the info introduced by the user.
static bool valInitialized = false; // Verifies the initialization.
static int noAvg 	= 1;			// Number to average MSD.
static double **x		= NULL;		// Position of all particles.
static double *msd 	= NULL;		// MSD for each moment.
static double FeEval;				// External force evaluation.
static double cache;				// Temporarily saves values.
static double Fe;					// External force.
static double D;					// Diffusion coefficient.
static double Kr;					// Spring constant.
static double r;					// Radius of particle.
static int POS;					// Number of steps/positions.
static int N;					// Number of particles.

// Log file.
static FILE *logFile;	// Pointer to the log file.
static const char logFileName[20] = "simulation.log";
static char entry[BUFSIZ];

/** Note: static variables are automatically initialized to zero.
 */

/**************************************************************/
/**************************************************************/

/** Declaration of functions:
 *****************************
 */

/** Log file.		*/
static void Log( char [] );

/** Allocates memory.	*/
static void setMemory( void );

/** Free the memory after is used.	*/
static void freeMemory( void );

/** Initializes the external force used.	*/
static void setForceEval( char );

/** Initializes the particles' position uniformly.   */
static void setUniformDist( double , int );

/** Initializes the position of the particles according to a.  */
static void setInitialPosition( double );

/** Initializes the values needed to run the simulation.	*/
extern void setInitialValues(int* , int* , int* ,double* ,char* );

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

static void Log ( char logEntry[] ){
	logFile = fopen(logFileName, "a");
	
	if (logFile == NULL) {
		fprintf(stderr, "Error opening log file: %s\n",
				strerror(errno) );
		exit(errno);
	}
	
	fprintf(logFile, "\n%s", logEntry);
	fclose(logFile);
}
/** End of Log	*/

/**************************************************************/

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
		sprintf(entry, "Memory allocation (positions) error: %s\n",
				strerror(errno) );
		Log(entry);
		
		fprintf(stderr, "Memory allocation error: %s\n",
				strerror(errno) );
		exit(errno);
	}
	Log("\nMemory Allocation:\n\tFor positions: Successful.");
	
	// 2) For the number of particles (columns).
	int row = 0;
	while (row < POS) {
		// Allocate.
		x[row] = (double*)calloc(N, sizeof(double) );
		
		// Check memory validity.
		if ( x[row] == NULL ){
			sprintf(entry, "Memory allocation (particles) error: %s\n",
					strerror(errno) );
			Log(entry);
			
			fprintf(stderr, "Memory allocation error: %s\n",
					strerror(errno) );
			exit(errno);
		}
		
		row++;
	}	// End of while.
	Log("\tFor particles: Successful.");
	
	/** Allocate the memory of msd:
	 *****************************
	 */
	msd = (double*) calloc ( POS, sizeof(double) );
	
	// Check memory validity.
	if ( msd == NULL ) {
		sprintf(entry, "Memory allocation (MSD) error: %s\n",
				strerror(errno) );
		Log(entry);
		
		fprintf(stderr, "Memory allocation error: %s\n",
				strerror(errno) );
		exit(errno);
	}
	Log("\tFor MSD: Successful.");
}
/** End of setMemory   */

/**************************************************************/

static void freeMemory( void ) {
	/** Frees the memory.	*/
	
	Log("\nReleasing memory...");
	int iRow;
	for (iRow =0 ; iRow < POS ; iRow++)
		free(x[iRow]);	// Free allocated memory for positions.
	free(x);				// Free the memory used for positions.
	free(msd);			// Free the memory used for MSD.
	Log("Memory released...");
}
/** End of freeMemory	*/

/**************************************************************/

static void setForceEval( char force ) {
	switch (force) {
		case 'y':
			FeEval = 1;
			sprintf(entry, "\tFeEval = %.0lf",FeEval);
			Log(entry);
			break;

		default:
			FeEval = 0;
			sprintf(entry, "\tFeEval = %.0lf",FeEval);
			Log(entry);
			break;
	}
}
/** End of setForce	*/

/**************************************************************/

static void setUniformDist( double a, int part) {
    /** Sets the positions of particles uniformly distributed.
     */
    
    // Base Case
    if (part == N)
        return;
    
    // Position the particle (part_num)
    x[0][part] = (2*a/(N-1)) * (double)part - a;
    
    // Position the next particle (part_num + 1)
    setUniformDist( a, part + 1 );
    
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
	
	Log("\nInitial position stablished.");
}
/** End of setInitialPosition   */

/**************************************************************/

extern void setInitialValues(int *noAverage, int *noPosition,
							 int *noParticles, double *aValue,
							 char *force) {
	/** Initializes the values needed to run the simulation:
	 *		noAverage:	number of executions in order to average
	 *					the MSD.
	 *		noPositions:	number of positions for all particles,
	 *					i.e. how many time.
	 *		noParticles: number of particles used in simulation.
	 *		aValue:		the particles' initial position will be
	 *					set uniformly distributed according to
	 *					this value.
	 */
	
	/** Log entries.	*/
	time_t date;
	time(&date);
	Log(ctime(&date));
	
	sprintf(entry, "Initial values:\n\tT = %.0lf\n\teta = %E\n\tstks = %E"
			"\n\tKb = %E\n\tdt = %E",
			T,eta,stks,Kb,dt);
	Log(entry);
	
	/** This MUST be called ONCE in order to set the seed in the
	 * program and use the random values (rndbm.h).	*/
	setSeed();
	
	/** Set initial values and conditions.	*/
	
	// Calculate other values based on the given ones.
	r = stks / (6*M_PI*eta);
	D = Kb*T / stks;
	Kr = Kb*T*eta / D;
	
	if (*noAverage != 0)
		noAvg = abs(*noAverage);
	
	POS	= abs(*noPosition);
	N	= abs(*noParticles);
	
	sprintf(entry, "\nValues calculated/given:\n\tr = %E\n\tD = %E\n\tKr = %E"
			"\n\tnoAvg = %d\n\tPOS = %E\n\tN = %E\n\ta = %E",
			r,D,Kr,noAvg,(double) POS, (double) N, 2*r);
	Log(entry);
	
	setForceEval(*force);
	setMemory();
	//setInitialPosition(*aValue);
	if ( *aValue == 0)
		setInitialPosition(*aValue);
	else
		setInitialPosition(2*r);
	
	valInitialized = true;
}
/** End of setInitialValues.	*/

/**************************************************************/

static void eachPosition( int pos ) {
    /** Runs through all positions for each particle.
     *      - pos_num must start with 1;
     */

    // Base Case: returns to the calling function.
    if ( pos >= POS )
        return;
    
    /** Calculate the position and the MSD given by pos_num and
	 * go to the next one.
     */

    // Get the actual position of all particles & numerator of MSD.
    eachParticle( 0, pos );
	
	// Calculation of MSD.
	msd[pos] = msd[pos] + cache / (N * noAvg);
	cache = 0;	// Clear the cache.
    
    // Go to the next position.
    eachPosition( pos+1 );
    
}
/** End of eachPosition.    */

/**************************************************************/

static void eachParticle( int part, const int pos ) {
    /** Modify the position of each particle.
     *      - part_num must start with 0;
     *      - pos_num must start with 1;  */
    
    // Base Case: returns to the calling function.
	if ( part >= N ){
		return;}
    
    /** Modify the position of the actual particle, calculate the
	 * numerator of MSD and move to the next one.
	 */
    
    /** Data dictionary: declare variable types & definitions */
    double G = 0;	// Random value (BM).
    
    // Get the random value using the Box-Muller Transform.
    randomBM(1, &G);
	
	// Get the external force.
	Fe = -Kr * ( x[pos-1][part] - x[0][part] ) * FeEval;
	
    // Modify the position.
    x[pos][part] = x[pos-1][part] + D*Fe*dt/(Kb*T) + sqrt(2*D*dt)*G;
	
	// Numerator of MSD
	cache = cache + pow( x[pos][part] - x[0][part], 2 );
    
    // Go to the next particle.
    eachParticle( part+1, pos );
    
}
/** End of eachParticle.    */

/**************************************************************/

static void saveIt(int noFile){
    
    /** Data dictionary: declare variable types & definitions */
    FILE *fPos;     		// Pointer to the file (for positions).
    FILE *fMSD;    		// Pointer to the file (for the MSD).
    int pos;        		// Index of position
    int part;       		// Index of particle
	char fileName[50];	// Name of the file to open.
	char extension[20];	// Last part of file's name.
	
	printf("\n\tSaving information...");
	Log("\nSaving information:");
	
	// Add information of the dynamic to the name of the file.
	if ( FeEval == 1 )
		strcpy(extension, "-Fe.dat");
	else
		strcpy(extension, ".dat");
	
	// Concatenate the name of the file and the noFile and open
	// the files to write.
	sprintf(fileName, "position-%d%s", noFile, extension);
    fPos = fopen(fileName, "w");
	
	sprintf(entry, "\tPositions' file name: %s",fileName);
	Log(entry);
	
	sprintf(fileName, "msd-%d%s", noFile, extension);
    fMSD = fopen(fileName, "w");
	
	sprintf(entry, "\tMSD file name: %s",fileName);
	Log(entry);
    
    // Verify if there was a problem opening the files
    if ( fPos == NULL || fMSD == NULL ) {
		sprintf(entry, "Error opening a file: %s\n",
				strerror(errno) );
		Log(entry);
		
        fprintf(stderr, "Error opening a file: %s\n",
                strerror(errno) );
        exit(errno);
    }
    
    // Save the info.
    for ( pos = 0; pos < POS; ++pos) {
        // Write the MSD
        fprintf(fMSD, "%E\t%E\n", pos*dt , msd[pos] );
        
        // Write the time
        fprintf(fPos, "%E\t", pos*dt);
        
        for ( part = 0; part < N; ++part) {
            // Write the positions of all particles
            fprintf(fPos, "%E\t", x[pos][part]);
        }
        fprintf(fPos, "\n");
    }
	
	Log("\tSuccessfully saved.");
	
    fclose(fPos);
    fclose(fMSD);
    
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
		Log("\nValues have not been initialized.");
		fprintf(stdout, "\tValues have not been initialized.");
		exit(1);
	}
	
	/** Start the simulation.	*/
	Log("\n\t Brownian Dynamics Started\n"
		  "\t==========================");
	start = clock();
	printf("\n\t Brownian Dynamics Started\n"
		   "\t==========================\n");
	
	while ( loop < noAvg ) {
		
		/** Compute all positions & Mean Square Displacement. */
		eachPosition(1);
		
		/** Save the information.	*/
		//saveIt(loop+1);	// Saves positions & MSD at every loop.
		
		// Print the status.
		printf("\r\t\t%d of %d is done.", loop+1, noAvg );
		fflush(stdout);
		
		sprintf(entry,"\t\t%d of %d is done.", loop+1, noAvg );
		Log(entry);
		
		loop++;
	}	// Enf of while loop.
	
	saveIt(noAvg); // Saves the last positions & the averaged MSD.
	
	/** Frees the memory used.	*/
	freeMemory();
	
	/** Calculate the time of compute.	*/
	end = clock();
	elapsedTime = ( (double) (end - start) ) / CLOCKS_PER_SEC;
	printf("\n\tTime elapsed: %.2lf seconds.\n", elapsedTime);
	sprintf(entry, "\nTime elapsed: %.2lf seconds.\n", elapsedTime);
	Log(entry);
}
/** End of startDynamic.     */
