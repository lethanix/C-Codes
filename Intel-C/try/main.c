//
//  main.c
//  try
//
//  Created by Louis Murguia on 7/15/19.
//  Copyright © 2019 Louis Murguia. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define POS 3
#define N 5

static double x[POS][N];

void getPosition( double x[POS][N], int position,
                 int particle) {
    // Base Case
    if ( position > POS )
        return;
    x[position][0] = position;
    printf("x[%d] = %lf\n", position, x[position][0]);
    getPosition(x, position + 1, 0);
}

void setUniformDist(double a, int part_num) {
    
    // Base Case
    if (part_num == N)
        return;
    
    // Position the particle (part_num)
    x[0][part_num] = (2*a/(N-1)) * (double)part_num - a;

    // Position the next particle (part_num + 1)
    setUniformDist(a, part_num + 1);
    
}

void setInitialPosition(double a) {
    if (a == 0)
        return;
    else
        setUniformDist(a,0);
}

void print() {
    int i,j;
    for (i=0; i<POS; i++) {
        for (j=0; j<N ; j++) {
            printf("%lf\t", x[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    double a = 0;
    char buff[BUFSIZ];  // Input buffer
    char * p;          // Buffer pointer
    // getPosition(x, 0, 0);
    
    printf("What is the initial position of particles?\n"
           "\t1)Enter 0 to position all particles in 0.\n"
           "\n\t2)Enter a value to position them uniformly\n"
           "\tdistributed in the interval [-value, value].\n"
           "Value: ");
    fgets(buff, BUFSIZ, stdin);
    a = strtod(buff, &p);
    
    printf("\nBEFORE:\n");
    print();
    
    setInitialPosition(a);
    
    printf("\nAFTER:\n");
    print();
    
    
    
    
    // double example[2][2] = {0.0};
    
    return 0;
}

