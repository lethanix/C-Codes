/**************************************************************/
/********************     Box-Muller      *********************/
/**************************************************************/

/*  Purpose:
 *      To generate values from the standard normal distribution
 *      with mean 0 and standard deviation 1, using the standard
 *      Box-Muller transform.
 *
 *  Record of revisions:
 *      Date        Programmer          Description of change
 *      ====        ==========          =======================
 *      03/07/19    Louis C. Murguía    Original code.
 *                                      Creation of header.
 */

#ifndef RNDBM_H
#define RNDBM_H

#define randomBM Box_Muller_Function_randomBM
#define setSeed Box_Muller_Function_setSeed

/** Declaration of functions:
 *****************************
 */

/* How to use setSeed():
 *      This MUST be called FIRST in order to set the seed
 *      only once in the program.
 */
extern void setSeed(void);

/* How to use randomBM():
 *      The first int argument indicates the number of the
 *      following arguments.
 *
 *      - For the value 1: you only need one random value:
 *          randomBM(1, &variable_where_is_saved);
 *
 *      - For the value 2: you need numerous random values:
 *          randomBM(2, array_where_are_saved, size_array);
 *
 *      The variable/array where the value(s) is/are saved
 *      must be of type double; size_array must be int.
 */
extern int randomBM(int , ...);


#endif // RNDBM_H
