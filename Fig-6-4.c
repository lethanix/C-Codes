
#include <stdio.h>
#include <math.h>


int main() {

    int number[11];
    int square[11];

//    Initialize number and calculate square.
    for (int i = 0; i < 11 ; ++i) {
        number[i] = i;                  // Initialize number
        square[i] = pow(number[i], 2);   // Calculate square
    }

//    Write out each number and its square.
    for (int i = 0; i < 11 ; ++i) {
        printf("Number = %6i Square = %6i\n", number[i], square[i]);
    }

    return 0;
}