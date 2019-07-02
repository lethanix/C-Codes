//
// Created by Louis Murguia on 2019-03-28.
//

/*  Purpose:
 *      To compare two strings to see if they are equivalent,
 *      ignoring case.
 *      */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 20

int main() {

//    Data dictionary: declare variable types, definitions, & units
    int i;              // Loop index
    char str1[LEN];     // First string to compare
    char str1a[LEN];    // Copy of first string to compare
    char str2[LEN];     // Second string to compare
    char str2a[LEN];    // Copy of second string to compare
    char buff[LEN];     // Input buffer

//    Prompt for the strings
    printf("Enter first string to compare: ");
    fgets(buff, LEN, stdin);
    strncpy(str1, buff, strcspn(buff, "\n"));   // Save input in str1 without the \n at the end
    printf("Enter second string to compare: ");
    fgets(buff, LEN, stdin);
    strncpy(str2, buff, strcspn(buff, "\n"));   // Save input in str2 without the \n at the end

//    Make copies so that the original strings are not modified
    strcpy(str1a, str1);
    strcpy(str2a, str2);

//    Now shift lowercase letters to uppercase.
    for ( i = 0; i < LEN ; ++i) {
        if ( str1a[i] >= 'a' && str1a[i] <= 'z' )
            str1a[i] = (char) ( (double) str1a[i] - 32 );
    }   // End for

    for ( i = 0; i < LEN ; ++i) {
        if ( str2a[i] >= 'a' && str2a[i] <= 'z' )
            str2a[i] = (char) ( (double) str2a[i] - 32 );
    }   // End for

//    Compare strings and write result
    if ( strcmp(str1a, str2a) == 0 )
        printf("'%s' = '%s' ignoring case.\n", str1, str2);
    else
        printf("'%s' /= '%s' ignoring case.\n", str1, str2);

    return 0;
}