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

#include "../../program-handlers/program-handler/program_handler.h"
#include "function.h"

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
inst_error_t *funct_set_add(prog_hand_t *prog_handler, function_set_t *self, function_t *function);

/*
Removes a function from the function set based upon the parameter types, also freeing its associated
memory

*prog_handler: The program handler that contains the class and error handlers
*self: The Function Set to be modified
*return_cls: The class of the variable that is returned
**param_types: The types for each of the parameters within the function to remove
param_count: The number of parameters used within the function to remove

Errors:
    ErrInvalidParameters: Thrown if 'self' is set to NULL
    ErrFunctionNotDefined: Thrown if the function that is to be removed does not exist in the set
*/
inst_error_t *funct_set_remove(prog_hand_t *prog_handler, function_set_t *self, 
        class_t **param_types, int param_count);

/*
Runs a function within the Function Set, choosing the function with the correct parameters

*prog_handler: The program handler that contains the class and error handlers
*self: The Function Set to run the function from
*inst_var: The instance variable that is passed to the function
*return_val: The returned value after running the function
**params: A list of parameters that are to be passed when running the function
param_count: The number of parameters passed to the function

Returns: Any value returned by the function that is run

Errors: Returns any error run by the function as well as the possible following errors
    ErrInvalidParameters: Thrown if 'self' is set to NULL
    ErrFunctionNotDefined: Thrown if a function that matches the parameters given does not exist
*/
inst_error_t *function_set_run(prog_hand_t *prog_handler, function_set_t *self, var_t *inst_var,
        var_t *return_var, var_t **params, int param_count);

/*
Gets the return type of a function from the set that has the equivalent parameters

*prog_handler: The program handler that contains the class and error handlers
*self: The function set to search for the return type
**param_types: The parameter types used to call the function
param_count: The number of parameters used within the function

Errors:
    ErrInvalidParameters: Thrown if 'self' or 'return_type' is set to NULL
    ErrFunctionNotDefined: Thrown if a function matching the parameters was not found
*/
inst_error_t *funct_set_get_return(prog_hand_t *prog_handler, function_set_t *self, 
        class_t **return_type, class_t **param_types, int param_count);

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
inst_error_t *f_set_function_exists(prog_hand_t *prog_handler, bool *result, function_set_t *self, 
        funct_node_t **prev_node, class_t **param_types, int param_count);

#endif