/***********************************************/
/*************     Figure 7-2      *************/
/***********************************************/

/*
 *
 *  Purpose:
 *      Program to test the operation of void function calc_hypotenuse.
 *      */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function prototype
extern void calc_hypotenuse (double_t , double_t, double_t *);

int main () {

//    Data dictionary: declare variable types & definitions
    double_t s1;        // Length of side 1
    double_t s2;        // Length of side 2
    double_t hypot;     // Hypotenuse

    char buff[BUFSIZ];  // Input buffer
    char *ptr;          // Buffer pointer

//    Get the lengths of the two sides.
    printf("Program to test subroutine (function) calc_hypotenuse:\n"
           "\tEnter the length of side 1: ");
    fgets(buff, BUFSIZ, stdin);
    s1 = strtod(buff, &ptr);
    printf("\tEnter the length of side 2: ");
    fgets(buff, BUFSIZ, stdin);
    s2 = strtod(buff, &ptr);

//    Call calc_hypotenuse
    calc_hypotenuse(s1, s2, &hypot);

//    Write out hypotenuse.
    printf("The length of the hypotenuse is: %10.4lf\n", hypot);

    return 0;

}