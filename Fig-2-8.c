//
// Created by Louis Murguia on 2019-03-24.
//

/*  Purpose:
 *      To calculate the current, real, reactive, and apparent power,
 *      and the power factor supplied to a load.
 *      */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Data dictionary: declare constants
#define DEG_2_RAD 0.01745329    // Deg to radians factor

int main() {
    // Data dictionary: declare variable types, definitions, & units
    double amps;        // Current in the load (A)
    double p;           // Real power of load (W)
    double pf;          // Power factor of load (no units)
    double q;           // Reactive power of the load (VAR)
    double s;           // Apparent power of the load (VA)
    double theta;       // Impedance angle of the load (deg)
    double volts;       // Rms voltage of the power source (V)
    double z;           // Magnitude of the load impedance (ohms)

    char buf[BUFSIZ];   // Buffer input
    char *ptr;

    // Prompt the user for the rms voltage.
    printf("Enter the rms voltage of the source: ");
    fgets(buf, BUFSIZ, stdin);
    volts = strtod(buf, &ptr);

    // Prompt the user for the magnitude and angle of the impedance.
    printf("Enter the magnitude and angle of the impedance\nin ohms and degrees: \n");

    printf("\tMagnitude (ohms): ");
    fgets(buf, BUFSIZ, stdin);
    z = strtod(buf,&ptr);

    printf("\tAngle (degrees): ");
    fgets(buf, BUFSIZ, stdin);
    theta = strtod(buf, &ptr);

    // Perform calculations
    amps = volts / z;                           // Rms current
    p = volts * amps * cos(theta * DEG_2_RAD);  // Real power
    q = volts * amps * sin(theta * DEG_2_RAD);  // Reactive power
    s = volts * amps;                           // Apparent power
    pf = cos(theta * DEG_2_RAD);                // Power factor

    // Write out the results.
    printf("\nVoltage = %.2lf volts\n", volts);
    printf("Impedance = %.2lf ohms at %.2lf degrees\n", z, theta);
    printf("Current = %.2lf amps\n", amps);
    printf("Real Power = %.2lf watts\n", p);
    printf("Reactive Power = %.2lf VAR\n",q);
    printf("Apparent Power = %.2lf VA\n", s);
    printf("Power Factor = %lf\n",pf);

    // Finish up.
    return 0;
}