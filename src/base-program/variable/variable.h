/*
Variable
By Ciaran Gruber

The Variable is used to represent a named variable of specific type

File-specific:
Variable - Header File
The structures used to represent the Variable
*/

#ifndef VARIABLE
#define VARIABLE

#include <stdlib.h>
#include <stdbool.h>
#include "../../program-handlers/program-handler/program_handler.h"
#include "../../program-handlers/function-handler/function_handler.h"

/* A structure that holds the various features contained in a Variable */
struct gen_var {
    var_desc_t *desc; // The description of the variable with key features within the variable
    void *data;       // The data in bytes used to represent the variable
    bool initialised; // Whether the data has been initialised or not
};

/*
Frees the memory occupuied by a Variable structure

*src: The Variable structure whose memory is to be freed
*/
void free_var(var_t *src);

/*
Creates a new variable by resetting it to the default values

*dest: The variable that is to be reset

Errors:
    ErrInvalidParameters: Thrown if 'dest' is set to NULL
*/
inst_error_t *new_var(prog_hand_t *prog_handler, var_t *dest);

/*
Creates a new instance of a variable, copying the data exactly

*prog_handler: The program handler that contains the class and error handlers
*dest: The location to store the new variable
*type: The name of the variable's class
*name: The unique name for the variable
*data: The data that is to be copied into the variable

Errors:
    ErrInvalidParameters: Thrown if 'var_desc' or 'dest' is set to NULL
    ErrOutOfMemory: Thrown if there is not enough space to copy the instance data
    ErrClassUndefined: Thrown if the given class type does not exist in the class handler
*/
inst_error_t *init_var_exact(prog_hand_t *prog_handler, var_t *dest, var_desc_t *var_desc, 
        void *data);

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
    ErrInvalidParameters: Thrown if 'self' or 'funct_name' is set to NULL
*/
inst_error_t *run_function(prog_hand_t *prog_handler, var_t *self, char *funct_name, 
        var_t *return_var, var_t **params, int param_count);

/*
Gets a member field from a variable that inherits from Object classes which use a Variable Handler

*prog_handler: The program handler that contains the class and error handlers
*self: The variable to get a member field from
**dest: The location to store the retrieved member field to
*field_name: The name of the field to retrieve

Errors:
    ErrInvalidParameters: Thrown if 'self', 'dest' or 'field_name' is set to NULL
    ErrVariableNotDefined: Thrown when the given field does not exist
    ErrInvalidDataFormat: Thrown when the class does not handle its data using a Variable Handler
*/
inst_error_t *get_member_field(prog_hand_t *prog_handler, var_t *self, var_t **dest, 
        char *field_name);

/*
Gets the data from a variable that does not handle its data using a variable handler

*prog_handler: The program handler that contains the class and error handlers
*self: The variable used to retrieve the data from
**dest: A pointer to the data that is retrieved

Errors:
    ErrInvalidParameters: Thrown if 'self' or 'dest' is set to NULL
    ErrorInvalidDataFormat: Thrown when the variable handles its data using a Variable Handler
*/
inst_error_t *get_data(prog_hand_t *prog_handler, var_t *self, void **dest);

#endif