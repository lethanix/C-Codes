//
//  main.c
//  try
//
//  Created by Louis Murguia on 7/15/19.
//  Copyright © 2019 Louis Murguia. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define POS 2
#define N 4

//static double x[POS][N];
double **x = NULL;

void setVariables(const int mypos, const int myn){
	
	x = (double **)calloc( mypos, sizeof(double*) );
	if ( x == NULL)
		exit(1);
	
	int i;
	for (i = 0; i<mypos; i++) {
		x[i] = (double*)calloc( myn, sizeof(double));
		if ( x[i] == NULL )
			exit(1);
	}
}

void getPosition( double x[][N], int position,
                 int particle) {
    // Base Case
    if ( position > POS )
        return;
    x[position][0] = position;
    printf("x[%d] = %lf\n", position, x[position][0]);
    getPosition(x, position + 1, 0);
}

void setUniformDist( double a, int part_num) {
    
    // Base Case
    if (part_num == N)
        return;
    
    // Position the particle (part_num)
    x[0][part_num] = (2*a/(N-1)) * (double)part_num - a;

    // Position the next particle (part_num + 1)
    setUniformDist(a, part_num + 1);
    
}

void setInitialPosition( double a) {
    if (a == 0)
		return;
    else
        setUniformDist(a,0);
}

void print() {
    int i,j;
    for (i=0; i<POS; i++) {
        for (j=0; j<N ; j++) {
			printf("%lf\t", x[i][j]);
        }
        printf("\n");
    }
}

void tryPtr(int * value) {
	printf("a: %d\n", abs(*value) );
}

void passStr(char m[]) {
	printf("String: %s\n",m);
}

int main(int argc, const char * argv[]) {
    /**
    double a = 0;
    char buff[BUFSIZ];  // Input buffer
    char * p;          // Buffer pointer
    // getPosition(x, 0, 0);
	setVariables(POS, N);
    printf("What is the initial position of particles?\n"
           "\t1)Enter 0 to position all particles in 0.\n"
           "\n\t2)Enter a value to position them uniformly\n"
           "\tdistributed in the interval [-value, value].\n"
           "Value: ");
    fgets(buff, BUFSIZ, stdin);
    a = strtod(buff, &p);
	
    printf("\nBEFORE:\n");
    print();
    
    setInitialPosition(a);
    
    printf("\nAFTER:\n");
    print();
    
	int iRow;
	for (iRow =0 ; iRow < POS ; iRow++)
	{
		free(x[iRow]); // free allocated memory
	}

	free(x);
    
    // double example[2][2] = {0.0};
	 */
	int a = -500;
	double value = 1.3e3;
	char mssg[10] = "hola";
	char buff[BUFSIZ];	// Input buffer.
	char force = 'c';
	tryPtr(&a);
	value 			= value + 2000;
	printf("Value: %lf\n",value);
	
	printf("- Is there an external force? (y/n): ");
	fgets(buff, BUFSIZ, stdin);
	force 						= buff[0];
	printf("your input: %c\n", force);
	time_t now;
	time(&now);
	printf("\n\tTime: %s\n", ctime(&now) );
	passStr(mssg);
    return 0;
}

