//
// Created by Louis Murguia on 2019-03-28.
//

/*  Purpose:
 *      To calculate mean and the standard deviation of an input
 *      data set, where each input value can be positive, negative,
 *      or zero.
 *      */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {

    //    Data dictionary: declare variable types, definitions, & units
    int i;                  // Loop index
    int n = 0;              // The number of input samples.
    double std_dev = 0;     // The standard deviation of the input samples.
    double sum_x = 0;       // The sum of the input values.
    double sum_x2 = 0;      // The sum of the squares of the input values.
    double x = 0;           // An input data value.
    double x_bar;           // The average of the input samples.
    char buff[BUFSIZ];      // Input buffer
    char *ptr;

//    Get the number of points to input.
    printf("Enter number of points: ");
    fgets(buff, BUFSIZ, stdin);
    n = strtol(buff, &ptr, 10);

//    Check to see if we have enough input data
    if ( n < 2 )
        fprintf(stderr, "At least 2 values must be entered.\n");

    else {  // we will have enough data, so let's get it.

//        Loop to read input values.
        for (i = 0; i < n ; ++i) {
//            Read values
            printf("Enter number: ");
            fgets(buff, BUFSIZ, stdin);
            printf("The number is %s", buff);
            x = strtol(buff, &ptr, 10);

//            Accumulate sums.
            sum_x += x;
            sum_x2 += pow(x,2);

        }   // End for

//        Now calculate statistics.
        x_bar = sum_x / (double) n;
        std_dev = sqrt( ( (double) n * sum_x2 - pow(sum_x,2) ) / ( (double) n * (double) (n-1) ) );

//    Tell the user
        printf("\tThe mean of this data set is:\t%.2lf\n", x_bar);
        printf("\tThe standard deviation is:\t%.2lf\n", std_dev);
        printf("\tThe number of data points is:\t%i\n", n);

    }   // End if

    return 0;
}