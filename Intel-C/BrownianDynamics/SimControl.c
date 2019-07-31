#include <stdio.h>
#include <stdlib.h>
#include "BrownianDynamics.h"

int main()
{
	/** Data dictionary: declare variable types & definitions.*/
	char buff[BUFSIZ];	// Input buffer.
	char * ptr;			// Buffer pointer.
	int noAvg = 1;		// Number of execution to average MSD.
	int noPart = 0;		// Number of particles.
	int noPos = 0;		// Number of positions.
	double a = 0;		// Diameter of the particle.
	
	/** Ask the user for information.	*/
	printf("\t Brownian Dynamics - Initial Values\n"
		   "\t====================================\n");
	
	// Request the number of runs.
	printf("- How many times will MSD be averaged?: ");
	fgets(buff, BUFSIZ, stdin);
	noAvg = (int) strtol(buff, &ptr, 10);
	
	// Request the number of particles.
	printf("- Number of particles: ");
	fgets(buff, BUFSIZ, stdin);
	noPart = (int) strtol(buff, &ptr, 10);
	
	// Request the number of positions.
	printf("- Number of positions: ");
	fgets(buff, BUFSIZ, stdin);
	noPos = (int) strtol(buff, &ptr, 10);
	
	// Request the initial position of particles.
	printf("- What is the initial position of particles?\n"
		   "\t1)Enter 0 to position all particles in 0.\n"
		   "\n\t2)Enter a value to position them uniformly\n"
		   "\tdistributed in the interval [-value, value].\n"
		   "Value: ");
	fgets(buff, BUFSIZ, stdin);
	a = strtod(buff, &ptr);
	
	/** Initialize the needed values.	*/
	setInitialValues(&noAvg, &noPos, &noPart, &a);
	
	/** Start the simulation.	*/
	startDynamic();
	
	return 0;
}
