/*
 * Purpose:
 *      To read in a real input data set, sort it into ascending order
 *      using the selection sort algorithm, and to write the sorted
 *      data to the standard output device.
 *      */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

extern int errno;

#define MAX_SIZE 10     // Maximum input data set size

int main() {
//    Data dictionary: declare variable types & definitions
    double a[MAX_SIZE];     // Data array to sort
    char filename[20];      // Input data file name
    double *iptr;              // Pointer to smallest value
    char msg[80];           // Error message
    int nvals = 0;          // Number of data values to sort
    int status;             // I/O status: 0 for success
    double temp;            // Temporary variable for swapping

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
            a[nvals] = strtod(buff, &ptr);  // Save value in array
            nvals++;                        // Bump count
        }

//        Now, sort the data.
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

//        Now write out the sorted data.
        printf("The sorted output data values are:\n");
        for (int k = 0; k < nvals; ++k) {
            printf("%3s%10.4lf\n","",a[k]);
        }

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