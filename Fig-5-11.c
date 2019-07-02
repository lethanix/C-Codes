//
// Created by Louis Murguia on 2019-04-09.
//

/*  Purpose:
 *      To illustrate the use of a temporary file and positioning
 *      commands as follows:
 *      1.  Read in an arbitrary number of positive or zero
 *          values, saving them in a temporary file. Stop
 *          reading when a negative value is encountered.
 *      2.  Ask the user for a record number to display.
 *      3.  Rewind the file, get that value, and display it.
 *      */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

//    Data dictionary: declare variable types, definitions, & units
    FILE *LU;           // File pointer
    double data;        // Data value stored in a disk file
    int icount = 0;     // The number of input data records
    int irec;           // Record number to recover and display
    int j;              // Loop index
    char buff[BUFSIZ];  // Input buffer
    char *ptr;          // Buffer pointer

//    Open a temporary file
    LU = tmpfile();

//    Prompt user and get input data
    printf("Enter positive or zero input values.\n"
            "A negative value terminates input.\n");

//    Get the input values, and write them to the temporary file
    while (1) {
        printf("Enter sample %4i: ", icount+1);   // Prompt for next value
        fgets(buff, BUFSIZ, stdin);             // Read value
        data = strtod(buff, &ptr);
        if ( data < 0 )                         // Exit on negative numbers
            break;
        icount++;                               // Valid value: bump count
        fprintf(LU, "%16.6E\n", data);          // Write data to temporary file
    }

//    Now we have all of the records. Ask which record to see.
//    icount records are in the file.
    printf("\nWhich record do you want to see (1 to %4i)? ", icount);
    fgets(buff, BUFSIZ, stdin);
    irec = strtol(buff, &ptr, 10);

//    Do we have a legal record number? If so, get the record.
//    If not, tell the user and stop.
    if ( (irec >= 1) && (irec <= icount) ){

//        This is a legal record. Rewind the temporary file.
        rewind(LU);
//        Read forward to the desired record.
        for (j = 1; j <= irec ; ++j) {
            fgets(buff, BUFSIZ, LU);
        }
        data = strtod(buff, &ptr);

//        Tell user.
        printf("The value of record %4i is %14.5E\n",
                irec, data);

    } else      // We have an illegal record number. Tell user.
        fprintf(stderr, "Illegal record number entered: %8i\n",
                irec);
//    Close file
    fclose(LU);

    return 0;
}
