/***********************************************/
/************     Figure 7-20      *************/
/***********************************************/

void funcs_as_arguments (double x, double y, void (*func) (double, double, double *), double *result) {
    /*
     *  Purpose:
     *      To test passing functions names as arguments.
     *      */

    /*  Data dictionary: declare argument types & definitions
     *      func        Pointer to a function
     *      x           First value
     *      y           Last value
     *      result      Result (out)
     *      */

    (*func) (x, y, result);

}   // end of funcs_as_arguments
