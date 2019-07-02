//
// Created by Louis Murguia on 2019-03-28.
//

/*  Purpose:
 *      To calculate mean and the standard deviation of an input
 *      data set containing an arbitrary number of input values.
 *      */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {

//    Data dictionary: declare variable types, definitions, & units
    int n = 0;              // The number of input samples.
    double std_dev = 0;     // The standard deviation of the input samples.
    double sum_x = 0;       // The sum of the input values.
    double sum_x2 = 0;      // The sum of the squares of the input values.
    double x = 0;           // An input data value.
    double x_bar;           // The average of the input samples.
    char buff[BUFSIZ];      // Input buffer
    char *ptr;

//    While Loop to read input values
    while (x >= 0) {
//        Read in next value
        printf("Enter number: ");
        fgets(buff, BUFSIZ, stdin);
        printf("The number is %s\n", buff);
        x = strtod(buff, &ptr);

//        Test for the loop exit
        if ( x < 0 )
            continue;

//        Accumulate sums.
        n = n + 1;
        sum_x = sum_x + x;
        sum_x2 = sum_x2 + pow(x, 2);

    }   // End while loop

//    Check to see if we have enough input data.
    if ( n < 2 ) {  // Insufficient information

        fprintf(stderr, "At least 2 values must be entered!");
        exit(-1);
    }
    else {  // There is enough information, so
            // calculate the mean and standard deviation

        x_bar = sum_x / (double) n;
        std_dev = sqrt( ( (double) n * sum_x2 - pow(sum_x,2) ) / ( (double) n * (double) (n-1) ) );

//        Tell the user
        printf("\tThe mean of this data set is:\t%.2lf\n", x_bar);
        printf("\tThe standard deviation is:\t\t%.2lf\n", std_dev);
        printf("\tThe number of data points is:\t%i\n", n);
    }   // End if

    return 0;
}