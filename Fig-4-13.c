//
// Created by Louis Murguia on 2019-03-28.
//

/*  Purpose:
 *      To calculate distance traveled by a ball thrown at a specified
 *      angle THETA and at a specified velocity V0 from a point on the
 *      surface of the earth, ignoring the effects of air friction and
 *      the earth's curvature.
 *      */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Data dictionary: declare constants
#define DEGREES_2_RAD 0.01745329    // Deg ==> rad conv.
#define GRAVITY -9.81               // Accel. due to gravity (m/s)


int main() {

//    Data dictionary: declare variable types, definitions, & units
    int max_degrees;    // Angle at which the max rng occurs (degrees)
    double max_range;   // Maximum range for the ball at vel v0 (meters)
    double range;       // Range of the ball at a particular angle (meters)
    double radian;      // Angle at which the ball was thrown (in radians)
    int theta;          // Angle at which the ball was thrown (in degrees)
    double v0;          // Velocity of the ball (in m/s)

//    Initialize variables.
    max_range = 0;
    max_degrees = 0;
    v0 = 20;

//    Loop over all specified angles.
    for (theta = 0; theta < 90; ++theta) {

//        Get angle in radians
        radian = (double) theta * DEGREES_2_RAD;

//        Calculate range in meters.
        range = ( -2 * pow(v0,2) / GRAVITY ) * sin(radian) * cos(radian);

//        Write out the range for this angle.
        printf("Theta = %i degrees; Range = %lf meters\n", theta, range);

//        Compare the range to the previous maximum range. If this
//        range is larger, save it and the angle at which it occurred.
        if ( range > max_range ) {
            max_range = range;
            max_degrees = theta;
        }
    }

//    Skip a line, and then write out the maximum range and the angle
//    at which it occurred.
    printf("\nMax range = %lf at %i degrees\n", max_range, max_degrees);

    return 0;
}