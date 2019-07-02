/*
 * Purpose:
 *      To calculate mean, median, and standard deviation of an input
 *      data set read from a file.
 *      */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

#define MAX_SIZE 100    // Max data size

int main() {
//    Data dictionary: declare variable types & definitions
    double_t a[MAX_SIZE];       // Data array to sort
    bool exceed = false;        /* Logical indicating that array
                                *  limits are exceeded. */
    char filename[20];          // Input data file name
    double *iptr;               // Pointer to smallest value
    char msg[80];               // Error message
    int nvals = 0;              // Number of data values to sort
    int status;                 // I/O status: 0 for success
    double_t median;            // The median of the input samples
    double_t std_dev;           // Standard deviation of input samples
    double_t sum_x = 0;         // Sum of input values
    double_t sum_x2 = 0;        // Sum of input values squared
    double_t temp;              // Temporary variable for swapping
    double_t x_bar;             // Average of input values

    FILE *fp;               // Pointer to file
    char buff[BUFSIZ];      // Input buffer
    char *ptr;              // Buffer pointer

//    Get the name of the file containing the input data.
    printf("Enter the file name with the data to be sorted: ");
    scanf("%s",filename);

//    Open input data file.
    fp = fopen(filename, "r");

//    Was the open successful?
//    fileopen:
    if ( fp != NULL ) {     // Open successful

        /*  The file was opened successfully, so read the data to sort
         * from it, sort the data, and write out the results.
         * First read in data.  */
        while ( !feof(fp) ) {  // While the end of file is not reached
            fgets(buff, BUFSIZ, fp);        // Get value
            // size:
            if  ( nvals < MAX_SIZE )            // Too many values?
                a[nvals] = strtod(buff, &ptr);  // No: Save value in array
            else
                exceed = true;                  // Yes: Array overflow
            // end if size
            nvals++;                        // Bump count
        }

//        Was the array size exceeded? If so, tell user and quit.
        // toobig:
        if ( exceed ){
            fprintf(stderr, "Maximum array size exceeded: %6i > %6i", nvals, MAX_SIZE);
            exit(2);
        } else {
//
//        Limit not exceeded: sort the data.
            // outer:
            for (int i = 0; i < nvals-1; ++i) {

//            Find the minimum value in a[i] through a[nvals]
                iptr = &a[i];
//            inner:
                for (int j = i+1; j < nvals ; ++j) {
                    // minval:
                    if  ( a[j] < *iptr )
                        iptr = &a[j];
                    // end if minval
                } // end for inner

                /* iptr now points to the minimum value, so swap *iptr with
                 * a[i] if &a[i] /= iptr.   */
                // swap:
                if ( &a[i] != iptr ) {
                    temp = a[i];
                    a[i] = *iptr;
                    *iptr = temp;
                } // end if swap

            } // end for outer

//          The data is now sorted. Accumulate sums to calculate
//          statistics.
            // sums:
            for (int i = 0; i < nvals; ++i) {
                sum_x += a[i];
                sum_x2 += pow(a[i],2);
            }   // end for sums

//            Check to see if we have enough input data.
            // enough:
            if ( nvals < 2 ) {
//                Insufficient data.
                fprintf(stderr, "At least 2 values must be entered.");
            } else {
//                Calculate the mean, median and standard deviation
                x_bar = sum_x / (double_t) nvals;
                std_dev = sqrt( ((double_t) nvals * sum_x2 - pow(sum_x,2)) \
                            / ( (double_t)nvals * (double_t)(nvals-1) ));
                // even:
                if ( nvals % 2 == 0 ) {
                    median = ( a[nvals/2] + a[nvals/2+1] ) / 2.0;
                } else {
                    median = a[nvals/2+1];
                }   // end if even

//                Tell user.
                printf("\nThe mean of this data set is:  \t%lf\n", x_bar);
                printf("The median of this data set is:\t%lf\n", median);
                printf("The standard deviation is:     \t%lf\n", std_dev);
                printf("The number of data points is:  \t%i\n", nvals);

            }   // end if enough

        }   // end if toobig

    } else {    // else fileopen
//        Else file open failed. Tell user.
        status = errno;
        strcpy(msg, strerror(status));
        fprintf(stderr, "File open failed--error = %s\n", msg);
        exit(status);

    }

//     Close file
    fclose(fp);

    return 0;
}

