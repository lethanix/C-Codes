//
// Created by Louis Murguia on 2019-04-09.
//

/*  Purpose:
 *      To illustrate the use of formatted output. This
 *      program generates a table containing the square
 *      roots, squares, and cubes of all integers between
 *      1 and 10. The table includes a title and a column
 *      headings.
 *      */

#include <stdio.h>
#include <math.h>

int main() {

//    Data dictionary: declare variable types, definitions, & units
    int cube;           // The cube of i
    int i;              // Index variable
    int square;         // The square of i
    double square_root; // The square root of i

//    Print the title of the table on a new page.
    printf("\f%3sTable of Square Roots, Squares, and Cubes\n", "");

//    Print the column headings after skipping one line.
    printf("\n%-4s%-9s%-16s%-10s%4s","", "Number","Square Root", "Square", "Cube");
    printf("\n%-4s%-9s%-16s%-10s%4s\n\v","","======","===========","======","====");

//    Generate the required values, and print them out.
    i = 1;
    do {
        square_root = sqrt(i);
        square = pow(i,2);
        cube = pow(i,3);
        printf("%-4s%4i%-5s%10.6f%-4s%6i%-4s%6i\n",
                "",i,"",square_root,"",square,"",cube);
        i++;

    } while (i <= 10);

    return 0;
}
