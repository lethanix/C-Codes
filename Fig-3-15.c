//
// Created by Louis Murguia on 2019-03-26.
//

/*  Purpose:
 *      This program accepts a character string containing a
 *      day of the week, and responds with a message specifying
 *      whether the day is a weekday or falls on the weekend.
 *      */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 11
#define NUM_WEEKDAYS 5
#define NUM_DAYS 7
#define ERROR -1

int main() {

//    Declare the variables used in this program.
    char c_day[LEN];            // Character string containing day
    char c_type[LEN];           // Character string with day type
    const char *weekday[7];     // Weekday array of strings
    weekday[0] = "Monday\n";
    weekday[1] = "Tuesday\n";
    weekday[2] = "Wednesday\n";
    weekday[3] = "Thursday\n";
    weekday[4] = "Friday\n";
    weekday[5] = "Saturday\n";
    weekday[6] = "Sunday\n";
    int indx = ERROR;           // Index of the weekday array

//    Prompt the user for the day of the week
    printf("Enter the name of the day: ");
    fgets(c_day, LEN, stdin);


//    Get the corresponding day of the week.

    for (int i = 0; i < 7; ++i)
        if (strcmp(c_day, weekday[i]) == 0) {
            indx = i;
            break;
        }


    if ( indx < NUM_WEEKDAYS && indx != ERROR)
        strcpy(c_type, "Weekday");

    else if ( indx >= NUM_WEEKDAYS && indx < NUM_DAYS)
        strcpy(c_type, "Weekend");

    else {
        fprintf(stderr, "Invalid day\n");
        exit(ERROR);
    }

//    Write the resulting day type
    printf("Day Type = %s\n", c_type);

    return 0;

}