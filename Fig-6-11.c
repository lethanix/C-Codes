/*
 * Purpose:
 *      To illustrate array I/O.
 *      */


#include <stdio.h>
#include <stdlib.h>

int main() {

//    Data dictionary: declare variable types & definitions
    double a[5] = {1., 2., 3., 20., 10.};   // 5-element test array
    int vec[4] = {4, 3, 4, 5};              // Vector subscript

//    Output entire array.
    for (int i = 0; i < 5; ++i) {
        printf("%8.3lf",a[i]);
    }

    printf("\n");

//    Output array section.
    for (int i = 1; i < 5 ; i +=2) {
        printf("%8.3lf",a[i]);
    }

    printf("\n");

//    Output array section selected by a vector subscript.
    for (int i = 0; i < 4; ++i) {
        printf("%8.3lf",a[vec[i]-1]);
    }

    return 0;
}