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
inst_error_t *s_funct_hand_create(prog_hand_t *prog_handler, s_funct_hand_t *dest);

/*
Adds a function to the Static Function Handler

*prog_handler: The program handler that contains the class and error handlers
*self: The Static Function Handler that is to be modified
*function: The function to add to the Static Function Handler

Errors:
    ErrInvalidParameters: Thrown if 'self' or 'function' is set to NULL
    ErrOutOfMemory: Thrown if there is not enough memory to add a Static Function Set if required
    ErrFunctionAlreadyExists: Thrown if the given function already exists in the Function Handler
*/
inst_error_t *sfhand_add_function(prog_hand_t *prog_handler, s_funct_hand_t *self, s_function_t *function);

/*
Removes a function from the Static Function Handler

*prog_handler: The program handler that contains the class and error handlers
*self: The Static Function Handler to remove the function from
*function: The function to remove from the Static Function Handler

Errors:
    ErrInvalidParameters: Thrown if 'self' or 'function' is set to NULL
    ErrFunctionNotDefined: Thrown if the given function can not be found within the Static Function Handler
*/
inst_error_t *sfhand_remove_function(prog_hand_t *prog_handler, s_funct_hand_t *self,
        s_function_t *function);

/*
Removes a function from the Static Function Handler by its name and parameters

*prog_handler: The program handler that contains the class and error handlers
*self: The Function Handler to remove the function from
*name: The name of the function to remove
*return_type: The return type of the function
**param_types: The list of parameters that are within the function
param_count: The number of parameters within the function that is to be removed

Errors:
    ErrInvalidParameters: Thrown if 'self' or 'name' is set to NULL
    ErrFunctionNotDefined: Thrown if the given function can not be found within the Static Function Handler
*/
inst_error_t *sfhand_remove_function_by_name(prog_hand_t *prog_handler, s_funct_hand_t *self,
        char *name, class_t **param_types, int param_count);

/*
Runs a function in the function handler with the specified name and parameters

*prog_handler: The program handler that contains the class and error handlers
*self: The Static Function Handler used to find and run the function
*name: The name of the function that is to be run
*return_var: A pointer to the variable that is returned after running the function
**params: The list of parameters that will be passed into the function
param_count: The number of parameters that are passed into the function

Returns: A variable depending on the function that is run

Errors: Any errors that are produced from running the function as well as the following
    ErrInvalidParameters: Thrown if 'self' or 'name' is set to NULL
    ErrFunctionNotDefined: Thrown when the function does not exist
*/
inst_error_t *s_funct_hand_run(prog_hand_t *prog_handler, s_funct_hand_t *self, char *name, 
        var_t *return_var, var_t **params, int param_count);

/*
Gets the return type of a function within the handler that has the equivalent parameters

*prog_handler: The program handler that contains the class and error handlers
*self: The function set to search for the return type
*char: The name of the function set that holds the function
**param_types: The parameter types used to call the function
param_count: The number of parameters used within the function

Errors:
    ErrInvalidParameters: Thrown if 'self' or 'return_type' is set to NULL
    ErrFunctionNotDefined: Thrown if a function matching the parameters was not found
*/
inst_error_t *s_function_get_return(prog_hand_t *prog_handler, s_funct_hand_t *self, char *name,
        class_t **return_type, class_t **param_types, int param_count);

/*
Returns whether the function exists in the Static Function Handler and if it does, returns a
reference to the node before that function

*prog_handler: The program handler that contains the class and error handlers
*result: A boolean value representing whether the function already exists or not
*self: The function set that is to be searched
**prev_node: A pointer to the previous node reference
**param_types: The parameter types used to call the function
param_count: The number of parameters used within the function

Returns: A boolean value stored in 'result' that shows whether the function was found

Errors:
    ErrInvalidParameters: Thrown if 'result', 'self' or 'name' is set to NULL
*/
inst_error_t *s_function_exists(prog_hand_t *prog_handler, bool *result, 
        s_funct_hand_t *self, char *name, s_funct_hand_node_t **prev_node, class_t **param_types,
        int param_count);

#endif