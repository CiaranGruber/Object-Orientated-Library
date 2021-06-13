/*
Static Function
By Ciaran Gruber

The Static Function is a function that is called by classes and does not directly modify a
variable's data in a way similar to the Function

File-specific:
Static Function - Header File
The structures used to represent the Static Function
*/

#ifndef STATIC_FUNCTION
#define STATIC_FUNCTION

#include "../../program-handlers/program-handler/program_handler.h"

/* A structure that holds the various features contained in a Static Function */
struct gen_s_function {
    char *name;            // The name of the Static Function
    /* 
    A pointer to the related function that is run

    Parameters:
    prog_hand_t *: The program handler that holds the class and error handlers
    var_t *: The variable that the function returns
    var_t **: The parameters that the function uses - Number of parameters is constant
    */
    inst_error_t *(*function)(prog_hand_t *, var_t *, var_t **); 
    class_t *return_type;  // The return type of the function
    class_t **param_types; // The functions used for each of the parameters
    int param_count;       // The number of parameters in the Static Function
};

/*
Frees the memory occupied by a Static Function structure

*src: The Static Function structure whose memory is to be freed 
*/
void free_s_function(s_function_t *src);

/*
Creates a new function by specifying every individual part of the fucntion

*prog_handler: The program handler that contains the class and error handlers
*dest: A pointer to where the Static Function structure will be stored
*name: The name of the function that is to be created
(*function)(prog_hand_t *, var_t *, var_t **): A pointer to the function that this Static Function
                                               will run
*return_type: The class that the function will return
**param_types: A list of classes that correlate to the types for each of the parameters
param_count: The number of parameters in the function

Errors:
    ErrInvalidParameters: Thrown if: 'dest', 'name', or '(*function)' is set to NULL
    ErrOutOfMemory: Thrown when there is not enough memory to create the function
*/
inst_error_t *new_s_function(prog_hand_t *prog_handler, s_function_t *dest, char *name,
        inst_error_t *(*function)(prog_hand_t *, var_t *,var_t **), class_t *return_type,
        class_t **param_types, int param_count);

/*
Runs a given function, storing the returned values and any errors

*prog_handler: The program handler that contains the class and error handlers
*self: The function that is to be run
*return_val: The variable in which to store the returned value - Note memory must be pre-allocated
**params: A lsit of parameters to pass into the function
param_count: The number of parameters that ahve been passed into the function

Returns: A variable depending on the function that is run

Errors: Returns any error run by the function as well as the possible following errors
    ErrInvalidParameters: Thrown if: 
                          'self' is set to NULL; or 
                          the parameters do not match the function
*/
inst_error_t *s_function_run(prog_hand_t *prog_handler, s_function_t *self, var_t *return_val,
        var_t **params, int param_count);

/*
Returns whether the Static Function contains the same details as those that are provided

*prog_handler: The program handler that contains the class and error handlers
*result: A boolean value representing whether the function is equal
*self: The function to test
**param_types: A list of classes that correlate to the types for each of the parameters
param_count: The number of parameters in the function

Returns: A boolean value stored in 'result' that shows whether the function was equal

Errors:
    ErrInvalidParameters: Thrown if 'result' or 'self' is set to NULL
*/
inst_error_t *is_s_function_equal(prog_hand_t *prog_handler, bool *result, s_function_t *self,
        class_t **param_types, int param_count);

#endif