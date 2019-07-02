//
// Created by Louis Murguia on 2019-03-24.
//

#include <stdio.h>
#include <stdlib.h>

#define BASE 10 // Denotes the base of the input string,
                // which makes this function useful for
                // inputting numbers in say base 16, hexadecimal.

int main() {
    // Declare the variables used in this program.
    long int i;
    long int j;
    long int k;
    char buf[BUFSIZ];   // Buffer input
    char *ptr;          // Pointer: point to the character
                        //  that caused the parsing to stop.

    // Get two values to store in variables i and j
    printf("Enter the numbers to multiply: \n");

    printf("\tFirst: ");
    fgets(buf, BUFSIZ, stdin);
    i = strtol(buf, &ptr, BASE);

    printf("\tLast: ");
    fgets(buf, BUFSIZ, stdin);
    j = strtol(buf, &ptr, BASE);

    // Multiply the numbers together
    k = i*j;

    // Write out the result.
    printf("Result = %li", k);

    return 0;
}