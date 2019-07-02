//
// Created by Louis Murguia on 2019-03-26.
//

/*  Purpose:
 *      This program displays the day of week corresponding to
 *      an input integer value.
 *      */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 11

int main() {

//    Data dictionary: declare variable types, definitions, & units
    char c_day[LEN];    // Character string containing day
    long int i_day;     // Integer day of week
    char buf[BUFSIZ];   // Input buffer
    char *ptr;

//    Prompt the user for the numeric day of the week
    printf("Enter the day of the week (1-7): ");
    fgets(buf, BUFSIZ, stdin);
    i_day = strtol(buf, &ptr, 10);

//    Get the corresponding day of the week.

    switch (i_day) {
        case 1:
            strcpy(c_day, "Sunday");
            break;
        case 2:
            strcpy(c_day, "Monday");
            break;
        case 3:
            strcpy(c_day, "Tuesday");
            break;
        case 4:
            strcpy(c_day, "Wednesday");
            break;
        case 5:
            strcpy(c_day, "Thursday");
            break;
        case 6:
            strcpy(c_day, "Friday");
            break;
        case 7:
            strcpy(c_day, "Saturday");
            break;
        default:
            strcpy(c_day, "Invalida day");
            break;
    }

//    Write the resulting day
    printf("Day = %s\n", c_day);

    return 0;

}