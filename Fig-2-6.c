//
// Created by Louis Murguia on 2019-03-24.
//

/*  Purpose:
 *      To convert an input temperature from degrees Fahrenheit to
 *      an output temperature in kelvins.
 *      */

#include <stdio.h>
#include <stdlib.h>

int main() {

    // Data dictionary: declare variable types, definitions, & units
    double temp_f;      // Temperature in degrees Fahrenheit
    double temp_k;      // Temperature in kelvins
    char buf[BUFSIZ];   // Buffer input
    char *ptr;

    // Prompt the user for the input temperature
    printf("Enter the temperature in degrees Fahrenheit: ");
    fgets(buf, BUFSIZ, stdin);
    temp_f = strtod(buf, &ptr);


    // Convert to kelvins.
    temp_k = (5./9.) * (temp_f - 32.) + 273.15;

    // Write out the result.
    printf("%.2lf degrees Fahrenheit = %.2lf kelvins\n", temp_f, temp_k);

    return 0;
}
