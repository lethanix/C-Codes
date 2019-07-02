/***********************************************/
/************     Figure 7-17      *************/
/***********************************************/

/*  Purpose:
 *      To test the sinc function sinc(x)
 *      */

#include <stdio.h>
#include <stdlib.h>

/*  Declaration of function defined in Fig-7-16.c:
 *      sinc
 *      */
extern double sinc (double);

int main () {

//    Data dictionary: declare variable types & definitions
    double x;           // Input value to evaluate
    char buff[BUFSIZ];  // Input buffer
    char *ptr;          // Buffer pointer

//    Get value to evaluate
    printf("Enter x: ");
    fgets(buff, BUFSIZ, stdin);
    x = strtod(buff, &ptr);

//    Write answer.
    printf("sinc(x) = %8.5lf\n", sinc(x) );

    return 0;
}
