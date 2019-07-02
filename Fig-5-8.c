//
// Created by Louis Murguia on 2019-04-09.
//

/*  Purpose:
 *      To calculate the behavior of a capacitor as follows:
 *      1.  If capacitance and voltage are known, calculate
 *          charge, number of electrons, and energy stored.
 *      2.  If charge and voltage are known, calculate capa-
 *          citance, number of electrons, and energy stored.
 *          */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ELECTRONS_PER_COULOMB 6.241461e18

int main (){

//    Data dictionary: declare variable types, definitions, & units
    double_t c;         // Capacitance of the capacitor (farads)
    double_t charge;    // Charge on the capacitor (coulombs)
    double_t electrons; // Number of electrons on the plates of the capacitor
    double_t energy;    // Energy stored in the electric field (joules)
    int type;           // Type of input data available for the calculation:
                        // 1: C and V
                        // 2: CHARGE and V
    double_t v;         // Voltage on the capacitor (volts).
    char buff[BUFSIZ];  // Input buffer
    char *ptr;


//    Prompt user for the type of input data available.
    printf("This program calculates information about a"
           "capacitor.\nPlease specify the type of information\n"
           "available from the following list:\n"
           "\t1 -- capacitance and voltage\n"
           "\t2 -- charge and voltage\n"
           "\vSelect options 1 or 2: ");

//    Get response and validate it.
    while(1) {
        fgets(buff,BUFSIZ, stdin);
        type = strtol(buff, &ptr, 10);
        if ( (type == 1) || (type == 2) )
            break;
        else
            fprintf(stderr,"\n\tInvalid response: %i\n"
                           "\tPlease enter 1 or 2: ",type);
    }

//    Get additional data based upon the type of calculation.
    if ( type == 1 ) {

//        Get cappacitance
        printf("Enter capacitance in farads: ");
        fgets(buff, BUFSIZ, stdin);
        c = strtod(buff, &ptr);

//        Get voltage.
        printf("Enter voltage in volts: ");
        fgets(buff, BUFSIZ, stdin);
        v = strtod(buff, &ptr);

    }

    else {

//        Get charge.
        printf("Enter charge in coulombs: ");
        fgets(buff, BUFSIZ, stdin);
        charge = strtod(buff, &ptr);

//        Get voltage.
        printf("Enter voltage in volts: ");
        fgets(buff, BUFSIZ, stdin);
        v = strtod(buff, &ptr);

    }  // End of if - input

//    Calculate the unknown quantities.
    if ( type == 1 )
        charge = c*v;                           // Charge
    else
        c = charge / v;                         // Capacitance

    electrons = charge * ELECTRONS_PER_COULOMB; // Electrons
    energy = 0.5 * c * pow(v,2);                // Energy

//    Write out answers.
    printf("For this capacitor: "
           "\n\tVoltage             = %10.2f V\n"
           "\tCapacitance         = %10.3E F\n"
           "\tTotal charge        = %10.3E C\n"
           "\tNumber of electrons = %10.3E\n"
           "\tTotal energy        = %10.4f joules\n"
           ,v, c, charge, electrons, energy);

    return 0;
}
