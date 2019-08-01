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

#ifndef BrownianDynamics_h
#define BrownianDynamics_h

#define BrownianDynamics_Function_startDynamic
#define BrownianDynamics_Function_setInitialValues

/** Declaration of functions:
 *****************************
 */

/** How to use setInitialValues:
 *	Initializes the values needed to run the simulation:
 *		noAverage:	number of executions in order to average
 *					the MSD.
 *		noPositions:	number of positions for all particles,
 *					i.e. how many time.
 *		noParticles: number of particles used in simulation.
 *		aValue:		the particles' initial position will be
 *					set uniformly distributed according to
 *					this value.
 *		force:		character specifying if an external force
 *					exists ('y' -> yes,'n' -> no).
 */
extern void setInitialValues(int * noAverage, int * noPosition,
							 int * noParticles,
							 double * aValue, char * force);


/* How to use startDynamic():
 *		Call this function to begin the compute of the brownian
 *		dynamics according to the initial conditions.
 */
extern void startDynamic(void);


#endif /* BrownianDynamics_h */
