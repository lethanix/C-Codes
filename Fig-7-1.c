/***********************************************/
/*************     Figure 7-1      *************/
/***********************************************/

/*
     *  Purpose:
     *      To calculate the hypotenuse of a right triangle from the two
     *      other sides.
     *      */

#include <math.h>

// Length of:       side 1          side 2          hypotenuse
void calc_hypotenuse ( double_t side_1, double_t side_2, double_t *hypotenuse ) {

//    Data dictionary: declare local variable types & definitions
    double_t temp;      // Temporary variable

//    Calculate hypotenuse
    temp = pow(side_1,2) + pow(side_2,2);
    *hypotenuse = sqrt(temp);

}