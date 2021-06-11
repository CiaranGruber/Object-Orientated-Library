/*
Generic Function Set
By Ciaran Gruber

The Generic Function Set is used to provide the implementation for a set of functions that 
have the same name which may be used as a form of overloading

File-specific:
Function Set - Header File
The structures used to represent the Generic Function Set
*/

#ifndef FUNCTION_SET
#define FUNCTION_SET

#include "function.h"

typedef struct funct_node funct_node_t;

/* A node in the Generic Function Set that contains a function and a link to the next node */
struct funct_node {
    function_t *function; // The function that is within the node
    funct_node_t *next;   // The next node in the list
};

/* A structure that holds the various features contained in a Generic Function */
typedef struct {
    char *name;          // The name of the Generic Function Set and is equal all functions within
    funct_node_t *first; // The first node within the Generic Function Set
} function_set_t;

/*
Frees the memory occupuied by a Generic Function Set structure

*src: The Generic Function Set structure whose memory is to be freed 
*/
void free_funct_set(function_set_t *src);

/*
Creates a new Generic Function Set in which functions of the same name can be added

*prog_handler: The program handler that contains the class and error handlers
*dest: A pointer to where the Generic Function Set structure will be stored
*name: The name of the Generic Function Set

Errors:
    ErrOutOfMemory: Thrown if there is not enough memory to create the function set
*/
inst_error_t *funct_set_create(prog_hand_t *prog_handler, function_set_t *dest, char *name);

/*
Adds another Generic Function to the Generic Function Set

*prog_handler: The program handler that contains the class and error handlers
*self: The Generic Function Set that is to be modified
*function: The function to add to the Generic Function Set

Errors:
    ErrInvalidParameters: Thrown if the function does not have the same name as the function set
    ErrFunctionAlreadyExists: Thrown if a function with the same parameters already exists within
                              the function set
*/
inst_error_t *funct_set_add(prog_hand_t *prog_handler, function_set_t *self, function_t *function);

/*
Removes a function from the function set based upon the parameter types, also freeing its associated
memory

*prog_handler: The program handler that contains the class and error handlers
*self: The Generic Function Set to be modified
**param_types: The types for each of the parameters within the function to remove
param_count: The number of parameters used within the function to remove

Errors:
    ErrFunctionNotDefined: Thrown if the function that is to be removed does not exist in the set
*/
inst_error_t *funct_set_remove(prog_hand_t *prog_handler, function_set_t *self, 
        class_t **param_types, int param_count);

/*
Runs a function within the Generic Function Set, choosing the function with the correct parameters

*prog_handler: The program handler that contains the class and error handlers
*self: The Generic Function Set to run the function from
*return_val: The returned value after running the function
**params: A list of parameters that are to be passed when running the function
param_count: The number of parameters passed to the function

Returns: Any value returned by the function that is run

Errors: Returns any error run by the function as well as the possible following errors
    ErrFunctionNotDefined: Thrown if a function that matches the parameters given does not exist
*/
inst_error_t *function_set_run(prog_hand_t *prog_handler, function_set_t *self, var_t *return_val, var_t **params, int param_count);

#endif