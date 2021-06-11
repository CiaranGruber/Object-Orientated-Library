/*
Function
By Ciaran Gruber

The Generic Function is used to provide the implementation for a single function and also provides
error handling

File-specific:
Generic Function - Header File
The structures used to represent the Generic Function
*/

#ifndef GENERIC_FUNCTION
#define GENERIC_FUNCTION

#include "../generic-variable/variable.h"
#include "../../program-handlers/program-handler/program_handler.h"

/* A structure that holds the various features contained in a Generic Function */
typedef struct gen_function function_t;

/* A structure that holds the various features contained in a Generic Function */
struct gen_function {
    char *name;                                  // The name of the Generic Function
    inst_error_t *(*function)(var_t *,var_t **); // A pointer to the related function
    class_t *return_type;                        // The return type of the function
    class_t **param_types;                       // The functions used for each of the parameters
    int param_count;                             // The number of parameters in the Generic Function
};

/*
Frees the memory occupuied by a Generic Function structure

*src: The Generic Function structure whose memory is to be freed 
*/
void free_function(function_t *src);

/*
Creates a new function by specifying every individual part of the fucntion

*prog_handler: The program handler that contains the class and error handlers
*dest: A pointer to where the Generic Function structure will be stored
*name: The name of the function that is to be created
(*function)(var_t *, var_t **): A pointer to the function that this Generic Function will run
*return_type: The class that the function will return
**param_types: A list of classes that correlate to the types for each of the parameters
param_count: The number of parameters in the function

Errors:
    ErrOutOfMemory: Thrown when there is not enough memory to create the function
*/
inst_error_t *function_create(prog_hand_t *prog_handler, function_t *dest, char *name, 
                                inst_error_t *(*function)(var_t *,var_t **), class_t *return_type,
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
    ErrInvalidParameters: Thrown if the parameters or parameter counts do not match the function
*/
inst_error_t *function_run(prog_hand_t *prog_handler, function_t *self, var_t *return_val, 
                            var_t **params, int param_count);

#endif