/*
Function Handler
By Ciaran Gruber

The Function Handler is used to handle the functions within a class

File-specific:
Function Handler - Header File
The structures used to represent a Function Handler
*/

#ifndef FUNCTION_SET_LIST
#define FUNCTION_SET_LIST

#include "function_set.h"

/* A node in the Function Handler that contains a function set and a link to the next node */
typedef struct funct_set_node funct_set_node_t;

/* A node in the Function Handler that contains a function set and a link to the next node */
struct funct_set_node {
    function_set_t *function_set; // The function set contained within the node
    funct_set_node_t *next;       // The next node in the Function Handler
};

/* A structure that holds the function sets contained in a Function Handler */
typedef struct {
    funct_set_node_t *first;
} funct_hand_t;

/*
Frees the memory occupuied by a Function Handler structure

*src: The Function Handler structure whose memory is to be freed
*/
void free_funct_hand(funct_hand_t *src);

/*
Adds a function to the Function Handler

*prog_handler: The program handler that contains the class and error handlers
*self: The Function Handler that is to be modified
*function: The function to add to the Function Handler

Errors:
    ErrInvalidParameters: Thrown if the Function Handler or Program Handler is set to NULL
    ErrOutOfMemory: Thrown if there is not enough memory to add a Generic Function Set if required
    ErrFunctionAlreadyExists: Thrown if the given function already exists in the Function Handler
*/
inst_error_t *add_function(prog_hand_t *prog_handler, funct_hand_t *self, function_t *function);

/*
Removes a function from the Function Handler

*prog_handler: The program handler that contains the class and error handlers
*self: The Function Handler to remove the function from
*function: The function to remove from the Function Handler

Errors:
    ErrFunctionNotDefined: Thrown if the given function can not be found within the Function Handler
*/
inst_error_t *remove_function(prog_hand_t *prog_handler, funct_hand_t *self, function_t *function);

/*
Removes a function from the Function Handler by its name and parameters

*prog_hander: The program handler that contains the class and error handlers
*self: The Function Handler to remove the function from
*name: The name of the function to remove
**param_types: The list of parameters that are within the function
param_count: The number of parameters within the function that is to be removed

Errors:
    ErrFunctionNotDefined: Thrown if the given function can not be found within the Function Handler
*/
inst_error_t *remove_function_by_name(prog_hand_t *prog_handler, funct_hand_t *self, char *name, 
        class_t **param_types, int param_count);

/*
Runs a function in the function handler with the specified name and parameters

*prog_hander: The program handler that contains the class and error handlers
*self: The Function Handler used to find and run the function
*name: The name of the function that is to be run
*return_var: A pointer to the variable that is returned after running the function
**params: The list of parameters that will be passed into the function
param_count: The number of parameters that are passed into the function

Returns: A variable depending on the function that is run

Errors: Any errors that are produced from running the function as well as the following
    ErrFunctionNotDefined: Thrown when the function does not exist
*/
inst_error_t *run_function(prog_hand_t *prog_handler, funct_hand_t *self, char *name, 
        var_t *return_var, var_t **params, int param_count);

#endif