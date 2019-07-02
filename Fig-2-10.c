//
// Created by Louis Murguia on 2019-03-24.
//
/*  Purpose:
 *      To calculate the age of an organic sample from the percentage
 *      of the original carbon 14 remaining in the sample.
 *      */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Data dictionary: declare constants
#define LAMBDA 0.00012097   // The radioactive decay
                            // constant of carbon 14
                            // in units of 1/years.

int main() {
    // Data dictionary: declare variable types, definitions, & units
    double age;         // The age of the sample (years)
    double percent;     // The percentage of carbon 14 remaining at
                        // the time of the measurement (%)
    double ratio;       // The ratio of the carbon 14 remaining at
                        // the time of the measurement to the original
                        // amount of carbon 14 (no units)
    char buf[BUFSIZ];   // Buffer input
    char *ptr;

    // Prompt the user for the percentage of C-14 remaining.
    printf("Enter the percentage of carbon 14 remaining: ");
    fgets(buf, BUFSIZ, stdin);
    percent = strtod(buf, &ptr);

    // Echo the user's input value.
    printf("The remaining carbon 14 = %.2lf %%.\n", percent);

    // Perform calculations
    ratio = percent / 100.;             // Convert to fractional ratio
    age = (-1.0 / LAMBDA) * log(ratio); // Get age in years

    // Tell the user about the age of the sample.
    printf("The age of the sample is %.2lf years.\n", age);

    // Finish up.
    return 0;
}
