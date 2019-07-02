/***********************************************/
/************     Figure 7-11      *************/
/***********************************************/

/*
 *  Purpose:
 *      Program test the random number generator random0
 *      */

#include <stdio.h>
#include <stdlib.h>

/*  Declaration of functions defined in Fig-7-10.c:
 *      random0
 *      seed */
extern void random0 (double *);
extern void seed (int);

int main() {

//    Data dictionary: declare variable types & definitions
    double ave;         // Average of random numbers
    int iseed;          // Seed for random number sequence
    double ran;         // A random number
    double sum;         // Sum of random numbers

    char buff[BUFSIZ];  // Input buffer
    char *ptr;          // Buffer pointer

//    Get seed
    printf("Enter seed: ");
    fgets(buff, BUFSIZ, stdin);
    iseed = strtol(buff, &ptr, 10);

//    Set seed
    seed( iseed );

//    Print out 10 random numbers:
    printf("10 random numbers:\n");
    for (int i = 0; i < 10; ++i) {
        random0( &ran );
        printf("%3s%16.6lf\n", "", ran);
    }

//    Average 5 consecutive 1000-value sequences.
    printf("Averages of 5 consecutive 1000-sample sequences:\n");
    for (int iseq = 0; iseq < 5; ++iseq) {
        sum = 0.;
        for (int i = 0; i < 1000; ++i) {
            random0( &ran );
            sum += ran;
        }
        ave = sum / 1000.;
        printf("%3s%16.6lf\n", "", ave);
    }

    return 0;
}
