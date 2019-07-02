
#include <stdio.h>
#include <stdlib.h>

int main() {
    double a[4] = {1., 2., 3., 4.};
    double b[4] = {5., 6., 7., 8.};
    double c[4], d[4];
    int n = 0;

//    Element by element addition
    for (int i = 0; i < 4 ; ++i) {
        c[i] = a[i] + b[i];
    }

//    C can't handle:
//     d = a + b;
//    so a loop is needed
    do {
        d[n] = a[n] + b[n];
        n++;
    } while ( n < 4 );

    printf("c = ");
    for (int j = 0; j < 4 ; ++j) {
        printf("%6.1lf ", c[j]);
    }

    printf("\nd = ");
    for (int j = 0; j < 4 ; ++j) {
        printf("%6.1lf ", d[j]);
    }
    printf("\n");


    return 0;
}