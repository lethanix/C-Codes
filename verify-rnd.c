//
// Created by Louis Murguia on 2019-07-08.
//

#include <stdio.h>
#include "rndbm.h"

int main ()
{
    double value;
    setSeed();


    for (int i = 0; i < 10; ++i) {
        printf("%lf\n", value);
        randomBM(1,&value);

    }
    return 0;
}