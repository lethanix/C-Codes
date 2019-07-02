
/*  Purpose:
 *      To find the largest and smallest values in a data set
 *      and to print out the data set with the largest and smallest
 *      values labeled.
 *      */


#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10     // Max size of data set

int main() {

//    Data dictionary: declare variable types, definitions, & units
    int input[MAX_SIZE];    // Input values
    int *ilarge;            // Pointer to largest value
    int *ismall;            // Pointer to smallest value
    int j;                  // Loop index
    int nvals;              // Number of vals in data set
    int temp;               // Temporary variable
    char buff[BUFSIZ];      // Input buffer
    char *ptr;              // Buffer pointer

//    Get number of values in data set
    printf("Enter number of values in data set: ");
    fgets(buff, BUFSIZ, stdin);
    nvals = strtol(buff, &ptr, 10);

//    Is the number <= MAX_SIZE?
//    size:
    if ( nvals <= MAX_SIZE ) {

//        Get input values.
        for (j = 0; j < nvals ; ++j) {
            printf("Enter value %3i: ", j+1);
            fgets(buff, BUFSIZ, stdin);
            input[j] = strtol(buff, &ptr, 10);
        }

//        Find the largest value.
        temp = input[0];
        ilarge = &input[0];
//        large:
        for (j = 1; j < nvals ; ++j) {

            if ( input[j] > temp ){
                temp = input[j];
                ilarge = &input[j];
            }   // end if

        }   // end for large

//        Find the smallest value.
        temp = input[0];
        ismall = &input[0];
//        small:
        for (j = 1; j < nvals ; ++j) {

            if ( input[j] < temp ){
                temp = input[j];
                ismall = &input[j];
            }   // end if

        }   // end for small

//        Write out list
        printf("The values are:\n");
//        out:
        for ( j = 0; j < nvals ; ++j) {
            if ( &input[j] == ilarge )
                printf("%6i  LARGEST\n", input[j]);
            else if ( &input[j] == ismall )
                printf("%6i  SMALLEST\n", input[j]);
            else
                printf("%6i \n", input[j]);

        }   // end for loop out

    } else {    // size

//        nvals > MAX_SIZE. Tell user and quit.
        fprintf(stderr, "Too many input values: %6i > %6i\n", nvals, MAX_SIZE);

    }



    return 0;
}