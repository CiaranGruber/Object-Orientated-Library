/*
Static Function Handler
By Ciaran Gruber

The Static Function Handler is used to handle the use of various Static Function Sets within a class

File-specific:
Static Function Handler - Header File
The structures used to represent a Static Function Handler
*/

#ifndef STATIC_FUNCTION_HANDLER
#define STATIC_FUNCTION_HANDLER

#include "../../typedefs.h"

/*
Frees the memory occupuied by a Static Function Handler structure

*src: The Static Function Handler structure whose memory is to be freed
*/
void free_s_funct_hand(s_funct_hand_t *src);

/*
Creates a new Static Function Handler by resetting the source variable

*prog_handler: The program handler that contains the class and error handlers
*dest: The pointer to the Static Function Handler to initialise

Errors:
    ErrInvalidParameters: Thrown if 'dest' is set to NULL
*/
inst_error_t *new_sfhand(prog_hand_t *prog_handler, s_funct_hand_t *dest);

/*
Adds a function to the Static Function Handler

*prog_handler: The program handler that contains the class and error handlers
*self: The Static Function Handler that is to be modified
*function: The function to add to the Static Function Handler

Errors:
    ErrInvalidParameters: Thrown if 'self' or 'function' is set to NULL
    ErrOutOfMemory: Thrown if there is not enough memory to add a Static Function Set if required
    ErrStatic FunctionAlreadyExists: Thrown if the given function already exists in the Static Function Handler
*/
inst_error_t *sfhand_add_function(prog_hand_t *prog_handler, s_funct_hand_t *self, s_function_t *function);

/*
Removes a function from the Static Function Handler

*prog_handler: The program handler that contains the class and error handlers
*self: The Static Function Handler to remove the function from
*name: The name of the function to remove
**param_types: The list of parameters that are within the function
param_count: The number of parameters within the function that is to be removed

Errors:
    ErrInvalidParameters: Thrown if 'self' or 'name' is set to NULL
    ErrStatic FunctionNotDefined: Thrown if the given function can not be found within the Static Function Handler
*/
inst_error_t *sfhand_remove_function(prog_hand_t *prog_handler, s_funct_hand_t *self, char *name,
        class_t **param_types, int param_count);

/*
Gets a function from the handler based upon the name and parameters

*prog_handler: The program handler that contains the class and error handlers
*self: The Static Function Set to get the function from
**dest: A pointer to the function
**param_types: The parameters used within the function
param_count: The number of parameters used by the function

Errors:
    ErrInvalidParameters: Thrown if 'self' or 'dest' is set to NULL
    ErrStatic FunctionNotDefined: Thrown if the function could not be found
*/
inst_error_t *sfhand_get_function(prog_hand_t *prog_handler, s_funct_hand_t *self, s_function_t **dest,
        char *name, class_t **param_types, int param_count);

/*
Returns whether the function exists in the Static Function Handler and if it does, returns a
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
inst_error_t *sfhand_function_exists(prog_hand_t *prog_handler, bool *result, s_funct_hand_t *self,
        char *name, class_t **param_types, int param_count);

#endif