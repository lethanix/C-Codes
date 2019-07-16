//
//  main.c
//  try
//
//  Created by Louis Murguia on 7/15/19.
//  Copyright © 2019 Louis Murguia. All rights reserved.
//

#include <stdio.h>
#define POS 10
#define N 2

void getPosition( double x[POS][N], int position,
                 int particle) {
    // Base Case
    if ( position > POS )
        return;
    x[position][0] = position;
    printf("x[%d] = %lf\n", position, x[position][0]);
    getPosition(x, position + 1, 0);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    static double x[POS][N];
    getPosition(x, 0, 0);
    
    return 0;
}

