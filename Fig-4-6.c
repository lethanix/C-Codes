//
// Created by Louis Murguia on 2019-03-28.
//

/*  Purpose:
 *      This program calculates the day of year corresponding to a
 *      specified date. It illustrates the use of counting loops
 *      and the SWITCH construct.
 *      */
#include <stdio.h>
#include <stdlib.h>

int main() {

//    Data dictionary: declare variable types, definitios, & units
    int day;            // Day (dd)
    int day_of_year;    // Day of year
    int i;              // Index variable
    int leap_day;       // Extra day for leap day
    int month;          // Month (mm)
    int year;           // Year (yyyy)
    char buff[BUFSIZ];  // Input buffer
    char *ptr;

//    Get day, month, and year to convert
    printf("This program calculates the day of year given the \
    \ncurrent date. Please enter\n");
    printf("\tCurrent month (1-12):\t");
    fgets(buff, BUFSIZ, stdin);
    month = strtol(buff, &ptr, 10);

    printf("\tCurrent day (1-31):\t");
    fgets(buff, BUFSIZ, stdin);
    day = strtol(buff, &ptr, 10);

    printf("\tCurrent year:\t\t");
    fgets(buff, BUFSIZ, stdin);
    year = strtol(buff, &ptr, 10);

//    Check for leap year, and add extra day if necessary
    if ((year % 400) == 0)
        leap_day = 1;       // Years divisible by 400 are leap years

    else if ((year % 100) == 0)
        leap_day = 0;       // Other centuries are not leap years

    else if ((year % 4) == 0)
        leap_day = 1;       // Otherwise every 4th year is a leap year

    else
        leap_day = 0;       // Other years are not leap years

//    Calculate day or year
    day_of_year = day;

    for (i = 1; i < month; ++i) {
//        Add days in months from January to last month
        switch(i) {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                day_of_year += 31;
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                day_of_year += 30;
                break;
            case 2:
                day_of_year += (28 + leap_day);
                break;
        }   // End switch
    }   // End for

//    Tell user
    printf("\n\tDay\t\t\t= %i\n", day);
    printf("\tMonth\t\t\t= %i\n", month);
    printf("\tYear\t\t\t= %i\n", year);
    printf("\tDay of year\t\t= %i\n", day_of_year);

    return 0;
}