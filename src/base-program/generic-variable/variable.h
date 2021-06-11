/*
Generic Variable Header File
By Ciaran Gruber

The header file holding the type, function prototypes, and other relevant info
*/

#ifndef GENERIC_VAR
#define GENERIC_VAR

#include <stdlib.h>
#include "../../program-handlers/program-handler/program_handler.h"

/* A structure that holds the various features contained in a Generic Variable */
typedef struct gen_var var_t;

/* A structure that holds the various features contained in a Generic Variable */
struct gen_var {
    class_t *type; // A reference to the type used to represent a variable
    void *data;    // The data in bytes used to represent the variable
};

/*
Frees the memory occupuied by a Generic Variable structure

*src: The Generic Variable structure whose memory is to be freed
*/
void free_var(var_t *src);

/*
Creates a new instance of a variable, copying the data exactly

*prog_handler: The program handler that contains the class and error handlers
*dest: The location to store the new variable
*type: The name of the variable's class
*data: The data that is to be copied into the variable

Errors:
    ErrOutOfMemory: Thrown if there is not enough space to copy the instance data
    ErrInvalidParams: Thrown if the variable type is not specified
    ErrClassUndefined: Thrown if the given class type does not exist in the class handler
*/
inst_error_t *new_var_exact(prog_hand_t *prog_handler, var_t *dest, char *type, void *data);

/*
Runs a function that is a part of a variable based upon the function name and parameters

*prog_handler: The program handler that contains the class and error handlers
*self: The variable to run the function for
*funct_name: The name of the function to run
*return_var: The variable to store the return value after running the function
**params: The list of parameters with which to run the function
param_count: The number of parameters in the params list

Returns: Returns a variable that is dependent on the function

Errors: Throws any errors related to the function that is run
*/
inst_error_t *var_run_func(prog_hand_t *prog_handler, var_t *self, char *funct_name, 
        var_t *return_var, var_t **params, int param_count);

#endif