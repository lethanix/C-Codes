//
// Created by Louis Murguia on 2019-04-09.
//

/*  Purpose:
 *      To perform a least-squares fit of an input data set
 *      to a straight line, and print out the resulting slope
 *      and intercept values. The input data for this fit
 *      comes from a user-specified input data file.
 *      */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

int main(){

//    Data dictionary: declare variable types, definitions, & units
//    Note that cumulative variables are all initialized to zero.
    char filename[24];      // Input file name (<= 24 chars)
    int ierror = 0;         // Error number from I/O statements
    char msg[80];           // Error message
    int n = 0;              // Number of input data pairs (x,y)
    double_t slope;         // Slope of the line
    double_t sum_x = 0;     // Sum of all input X values
    double_t sum_x2 = 0;    // Sum of all input X values squares
    double_t sum_xy = 0;    // Sum of all input X*Y values
    double_t sum_y = 0;     // Sun of all input Y values
    double_t x;             //  An input X value
    double_t x_bar;         // Average X value
    double_t y;             // An input Y value
    double_t y_bar;         // Average Y value
    double_t y_int;         // Y-axis intercept of the line
    FILE *LU;               // File pointer
    char buff[BUFSIZ];      // Input buffer
    char *ptr;              // Pointer for conversion
    char *space;            // Pointer of space between numbers

//    Prompt user and get the name of the input file.
    printf("This program performs a least-squares fit of an\n"
           "input data set to a straight line. Enter the name\n"
           "of the file containing the input (x,y) pairs: ");
    fgets(buff, BUFSIZ, stdin);

//    Copy the name of the file without '\n' at the end
    strncpy(filename, buff, strcspn(buff,"\n"));


//    Open the input file
    LU = fopen(filename, "r");
    ierror = errno;

//    Check to see if the open failed
//  Errorif:
    if ( ierror > 0 ){
        strcpy(msg, strerror(ierror));
        fprintf(stderr, "Error opening file: %s\n", msg);
        exit(ierror);
    } else {

//        File opened successfully. Read the (x,y) pairs from
//        the input file
        while ( !feof(LU) ) {
            fgets(buff, BUFSIZ, LU);    // Read line
            ierror = errno;
            if ( ierror != 0 )
                exit(ierror);

            space = strtok(buff,", ");
            x = strtod(space, &ptr);
            space = strtok(NULL,", ");
            y = strtod(space, &ptr);

            n++;                //
            sum_x += x;         // Calculate
            sum_y += y;         //      statistics
            sum_x2 += pow(x,2); //
            sum_xy += x*y;      //
        }

//        Now calculate the slope and intercept
        x_bar = sum_x / (double_t) n;
        y_bar = sum_y / (double_t) n;
        slope = ( sum_xy - sum_x * y_bar ) / ( sum_x2 - sum_x * x_bar );
        y_int = y_bar - slope * x_bar;

//        Tell user.
        printf("Regression coefficients for the least-square line:"
               "\n\tslope (m)       = %12.3lf"
               "\n\tIntercept (b)   = %12.3lf"
               "\n\tNo of points    = %12i\n",
               slope, y_int, n);

//        Close input file, and quit
        fclose(LU);
    }


    return 0;
}