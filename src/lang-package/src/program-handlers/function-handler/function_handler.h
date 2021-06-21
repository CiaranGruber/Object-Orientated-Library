/*
Function Handler
By Ciaran Gruber

The Function Handler is used to handle the use of various Function Sets within a class

File-specific:
Function Handler - Header File
The structures used to represent a Function Handler
*/

#ifndef FUNCTION_HANDLER
#define FUNCTION_HANDLER

#include "../../typedefs.h"

/*
Frees the memory occupuied by a Function Handler structure

*src: The Function Handler structure whose memory is to be freed
*/
void free_funct_hand(funct_hand_t *src);

/*
Creates a new Function Handler by resetting the source variable

*prog_handler: The program handler that contains the class and error handlers
*dest: The pointer to the Function Handler to initialise

Errors:
    ErrInvalidParameters: Thrown if 'dest' is set to NULL
*/
inst_error_t *new_fhand(prog_hand_t *prog_handler, funct_hand_t *dest);

/*
Adds a function to the Function Handler

*prog_handler: The program handler that contains the class and error handlers
*self: The Function Handler that is to be modified
*function: The function to add to the Function Handler

Errors:
    ErrInvalidParameters: Thrown if 'self' or 'function' is set to NULL
    ErrOutOfMemory: Thrown if there is not enough memory to add a Function Set if required
    ErrFunctionAlreadyExists: Thrown if the given function already exists in the Function Handler
*/
inst_error_t *fhand_add_function(prog_hand_t *prog_handler, funct_hand_t *self, function_t *function);

/*
Removes a function from the Function Handler

*prog_handler: The program handler that contains the class and error handlers
*self: The Function Handler to remove the function from
*name: The name of the function to remove
**param_types: The list of parameters that are within the function
param_count: The number of parameters within the function that is to be removed

Errors:
    ErrInvalidParameters: Thrown if 'self' or 'name' is set to NULL
    ErrFunctionNotDefined: Thrown if the given function can not be found within the Function Handler
*/
inst_error_t *fhand_remove_function(prog_hand_t *prog_handler, funct_hand_t *self, char *name,
        class_t **param_types, int param_count);

/*
Gets a function from the handler based upon the name and parameters

*prog_handler: The program handler that contains the class and error handlers
*self: The Function Set to get the function from
**dest: A pointer to the function
**param_types: The parameters used within the function
param_count: The number of parameters used by the function

Errors:
    ErrInvalidParameters: Thrown if 'self' or 'dest' is set to NULL
    ErrFunctionNotDefined: Thrown if the function could not be found
*/
inst_error_t *fhand_get_function(prog_hand_t *prog_handler, funct_hand_t *self, function_t **dest,
        char *name, class_t **param_types, int param_count);

/*
Returns whether the function exists in the Function Handler and if it does, returns a
reference to the node before that function

*prog_handler: The program handler that contains the class and error handlers
*result: A boolean value representing whether the function already exists or not
*self: The function set that is to be searched
*name: The name of the function
**param_types: The parameter types used to call the function
param_count: The number of parameters used within the function

Returns: A boolean value stored in 'result' that shows whether the function was found

Errors:
    ErrInvalidParameters: Thrown if 'result', 'self' or 'name' is set to NULL
*/
inst_error_t *fhand_function_exists(prog_hand_t *prog_handler, bool *result, funct_hand_t *self,
        char *name, class_t **param_types, int param_count);

#endif