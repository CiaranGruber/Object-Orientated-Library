/*
Function Set
By Ciaran Gruber

The Function Set is used to provide the implementation for a set of Functions that have the same
name which may be used as a form of overloading

File-specific:
Function Set - Header File
The structures used to represent the Function Set
*/

#ifndef FUNCTION_SET
#define FUNCTION_SET

#include "../../typedefs.h"

typedef struct funct_node funct_node_t;

/* A node in the Function Set that contains a function and a link to the next node */
struct funct_node {
    function_t *function; // The function that is within the node
    funct_node_t *next;   // The next node in the list
};

/* A structure that holds the various features contained in a Function Set */
struct gen_function_set {
    char *name;          // The name of the Function Set and is equal all functions within
    funct_node_t *first; // The first node within the Function Set
};

/*
Frees the memory occupuied by a Function Set structure

*src: The Function Set structure whose memory is to be freed 
*/
void free_funct_set(function_set_t *src);

/*
Creates a new Function Set in which functions of the same name can be added

*prog_handler: The program handler that contains the class and error handlers
*dest: A pointer to where the Function Set structure will be stored
*name: The name of the Function Set

Errors:
    ErrInvalidParameters: Thrown if 'dest' or 'name' is set to NULL
    ErrOutOfMemory: Thrown if there is not enough memory to create the function set
*/
inst_error_t *new_funct_set(prog_hand_t *prog_handler, function_set_t *dest, char *name);

/*
Adds another Function to the Function Set

*prog_handler: The program handler that contains the class and error handlers
*self: The Function Set that is to be modified
*function: The function to add to the Function Set

Errors:
    ErrInvalidParameters: Thrown if: 'self' or 'function is set to NULL; or 
                          self->name != function->name
    ErrFunctionAlreadyExists: Thrown if a function with the same parameters already exists within
                              the function set
*/
inst_error_t *fset_add_function(prog_hand_t *prog_handler, function_set_t *self, function_t *function);

/*
Removes a function from the function set based upon the parameter types, also freeing its associated
memory

*prog_handler: The program handler that contains the class and error handlers
*self: The Function Set to be modified
**param_types: The types for each of the parameters within the function to remove
param_count: The number of parameters used within the function to remove

Errors:
    ErrInvalidParameters: Thrown if 'self' is set to NULL
    ErrFunctionNotDefined: Thrown if the function that is to be removed does not exist in the set
*/
inst_error_t *fset_remove(prog_hand_t *prog_handler, function_set_t *self, 
        class_t **param_types, int param_count);

/*
Gets a function from the set based upon the parameters and number of parameters

*prog_handler: The program handler that contains the class and error handlers
*self: The Function Set to get the function from
**dest: A pointer to the function
**param_types: The parameters used within the function
param_count: The number of parameters used by the function

Errors:
    ErrInvalidParameters: Thrown if 'self' or 'dest' is set to NULL
    ErrFunctionNotDefined: Thrown if the function could not be found
*/
inst_error_t *fset_get_function(prog_hand_t *prog_handler, function_set_t *self, function_t **dest,
        class_t **param_types, int param_count);

/*
Returns whether the function exists and if it does, returns a reference to the node before that
function

*prog_handler: The program handler that contains the class and error handlers
*result: A boolean value representing whether the function already exists or not
*self: The function set that is to be searched
**prev_node: A pointer to the previous node reference
**param_types: The parameter types used to call the function
param_count: The number of parameters used within the function

Returns: A boolean value stored in 'result' that shows whether the function was found

Errors:
    ErrInvalidParameters: Thrown if 'result' or 'self' is set to NULL
*/
inst_error_t *fset_function_exists(prog_hand_t *prog_handler, function_set_t *self, bool *result,
        class_t **param_types, int param_count);

#endif