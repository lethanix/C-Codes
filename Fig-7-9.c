/***********************************************/
/*************     Figure 7-9      *************/
/***********************************************/

/*
 *  Purpose:
 *      To illustrate sharing data.
 *      */

#include <stdio.h>

// Make data in Fig-7-8.c visible

/*  Declaration of variables defined in Fig-7-8.c:
 *      array values
 *      num_vals
 *      */
extern const int num_vals;
extern double values[];

/* Funtion prototype (declaration) */
void sub1 ();

#define PI 3.141592     // Pi

int main () {

    for (int i = 0; i < num_vals; ++i) {
        values[i] *= PI;
    }

//    Call a function
    sub1();

    return 0;
}

/***********************************************/
/***********************************************/

void sub1 () {
    /*
     *  Purpose:
     *      To illustrate sharing data.
     *      */

    for (int j = 0; j < num_vals; ++j) {
        printf("%lf\t",values[j]);
    }
    printf("\n");
}