/***********************************************/
/*************     Figure 7-3      *************/
/***********************************************/

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
#include <stdbool.h>

extern int errno;

#define MAX_SIZE 10     // Maximum input data set size

void sort (double *, int);

int main() {
//    Data dictionary: declare variable types & definitions
    double a[MAX_SIZE];     // Data array to sort
    bool exceed = false;    /* Logical indicating that
 *                             array limits are exceeded. */
    char filename[20];      // Input data file name
    char msg[80];           // Error message
    int nvals = 0;          // Number of data values to sort
    int status;             // I/O status: 0 for success

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
        } else {    // else toobig
//
//        Limit not exceeded: sort the data.
            sort(a, nvals);

//        Now write out the sorted data.
            printf("The sorted output data values are:\n");
            for (int k = 0; k < nvals; ++k) {
                printf("%3s%10.4lf\n","",a[k]);
            }
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

/***********************************************/
/***********************************************/

void sort (double *arr, int n) {
    /*
     *  Purpose:
     *      To sort real array "arr" into ascending order using a selection
     *      sort.
     *      */

//    Data dictionary: declare variable types & definitions
    double temp;            // Temporary variable for swapping
    double *iptr;           // Pointer to smallest value

//    Sort the array

    // outer:
    for (int i = 0; i < n-1; ++i) {

//            Find the minimum value in arr[i] through arr[n]
        iptr = &arr[i];
//            inner:
        for (int j = i+1; j < n ; ++j) {
            // minval:
            if  ( arr[j] < *iptr )
                iptr = &arr[j];
            // end if minval
        } // end for inner

        /* iptr now points to the minimum value, so swap *iptr with
         * arr[i] if &arr[i] /= iptr.   */
        // swap:
        if ( &arr[i] != iptr ) {
            temp = arr[i];
            arr[i] = *iptr;
            *iptr = temp;
        } // end if swap

    } // end for outer
}