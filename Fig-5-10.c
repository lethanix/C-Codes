//
// Created by Louis Murguia on 2019-04-09.
//

/*  Purpose:
 *      To illustrate how to read an unknown number of values from
 *      an input data file, detecting both any formatting errors and
 *      the end of file.
 *      */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

extern int errno;

int main() {

//    Data dictionary: declare variable types, definitions, & units
    char filename[20];  // Name of file to open
    char msg[80];       // Error message
    int nvals = 0;      // Number of values read in
    int status = 0;     // I/O status
    double value;       // The real value read in
    char buff[BUFSIZ];  // Input buffer
    char *ptr;          // Buffer pointer
    FILE *fp;           // Pointer to file

//    Get the file name, and echo it back to the user.
    printf("Please enter input file name: ");
    fgets(buff, BUFSIZ, stdin);
    printf("The input file name is: %s\n", buff);

//    Copy the filename without the \n at the end
    strncpy(filename, buff, strcspn(buff, "\n"));

//    Open the file, and check for errors on open.
//  openif:
    if ( (fp = fopen(filename, "r")) != NULL ) {

//        Open was ok. Read values.
        // readloop:
        while ( !feof(fp) ){    // Get next value
            fgets(buff, BUFSIZ, (FILE *) fp);

            value = strtod(buff, &ptr);
            if ( buff == ptr || ptr == NULL || *ptr == ' ') {
                fprintf(stderr,
                        "An error occurred reading line %3i\n",
                        nvals + 1);
                exit(1);
            }
            status = errno;
            nvals++;                                                // Valid: increase count
            printf("Line %3i: Value = %10.3lf\n", nvals, value);   // Echo to screen

        } // End while readloop

//        The WHILE loop has terminated. Was it because of a READ
//        error or because of the end of the input file?
        // readif:
        if ( status > 0 ) {     // A fgets error occurred. Tell user.
            strcpy(msg, strerror(status));
            fprintf(stderr,
                    "An error occurred reading line %3i\n %s\n",
                    nvals + 1, msg);
        } else {    // the end of the data was reached. Tell user.
            printf("End of file reached. There were %3i values in the file.\n",
                    nvals);
        }   // End of readif

    } else {    // else openif
        status = errno;
        strcpy(msg, strerror(status));
        fprintf(stderr,
                "Can't open the file: %s\n", msg);
        exit(status);

    } // End of openif

//    Close file
    fclose(fp);

    return 0;
}
