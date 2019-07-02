/*
 * Purpose:
 *      To calculate a table of numbers, square roots, and cube roots
 *      using a DO loop to output the table.
 *      */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define  MAX_SIZE 10    // Max values in array

int main() {

//    Data dictionary: declare variable types, definitions, & units
    int j = 0;                        // Loop index
    double value[MAX_SIZE];           // Array of numbers
    double square_root[MAX_SIZE];     // Array of square roots
    double cube_root[MAX_SIZE];       // Array of cube roots

//    Calculate the square roots & cube roots of the numbers.
    do {
        value[j] = (double) j+1.0;
        square_root[j] = sqrt(value[j]);
        cube_root[j] = pow(value[j], 1.0/3.0);
        j++;

    }   while ( j < MAX_SIZE );

//    Write out each number, its square root, and its cube root.
    printf("%20sTable of Square and Cube Roots\n"
           "%4s Number  Square Root  Cube Root"
           "%3s Number  Square Root  Cube Root\n"
           "%4s ======  ===========  =========="
           "%3s======  ===========  =========\n"
           ,"","","","","");
    j = 0;
    do {
        printf("%4s%6.0lf%6s%6.4lf%6s%6.4lf"
                ,"", value[j],"", square_root[j],"", cube_root[j]);
        j++;
        printf("%4s%6.0lf%6s%6.4lf%6s%6.4lf\n"
                ,"", value[j],"", square_root[j],"", cube_root[j]);
        j++;

    } while ( j < MAX_SIZE );

    return 0;
}