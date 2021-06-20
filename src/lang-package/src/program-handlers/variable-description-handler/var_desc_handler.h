/*
Variable Description Handler
By Ciaran Gruber

The Variable Description Handler structure is used to handle the Variable Descriptions for classes

File-specific:
Variable Description Handler - Header File
The structures used to handle the Variable Desciprion a class
*/

#ifndef VARIABLE_DESCRIPTION_HANDLER
#define VARIABLE_DESCRIPTION_HANDLER

#include "../../typedefs.h"

/*
Frees the memory occupied by a Variable Description Handler structure

*src: The Variable Description Handler structure whose memory is to be freed
*/
void free_var_desc_hand(var_desc_hand_t *src);

/*
Creates a new Variable Description Handler by resetting the source variable

*prog_handler: The program handler that contains the class and error handlers
*dest: The pointer to the Variable Description Handler to initialise

Errors:
    ErrInvalidParameters: Thrown if the Variable Description Handler is set to NULL
*/
inst_error_t *var_desc_hand_create(prog_hand_t *prog_handler, var_desc_hand_t *src);

/*
Adds a variable to the Variable Description Handler

*prog_handler: The program handler that contains the class and error handlers
*self: The Variable Description Handler that is to be modified
*var_desc: The Variable Description to add to the Variable Description Handler

Errors:
    ErrInvalidParameters: Thrown if the '*self' or '*var_desc' is set to NULL
    ErrOutOfMemory: Thrown if there is not enough memory to add a Variabel Description if required
    ErrVariableNameTaken: Thrown if a variable description with the same name already exists in the
                          Variable Description Handler
*/
inst_error_t *add_var_desc(prog_hand_t *prog_handler, var_desc_hand_t *self, var_desc_t *var_desc);

/*
Removes a Variable Description from the Variable Description Handler

*prog_handler: The program handler that contains the class and error handlers
*self: The Variable Description Handler to remove the Variable Description from
*variable: The variable to remove from the Variable Description Handler

Errors:
    ErrInvalidParameters: Thrown if '*self' or '*var_desc' is set to NULL
    ErrVariableNotDefined: Thrown if the given variable description can not be found within the
                           Variable Handler
*/
inst_error_t *remove_var_desc(prog_hand_t *prog_handler, var_desc_hand_t *self, 
        var_desc_t *var_desc);

/*
Removes a Variable Description from the Variable Description Handler by its name and parameters

*prog_handler: The program handler that contains the class and error handlers
*self: The Variable Description Handler to remove the Variable from
*name: The name of the variable description to remove

Errors:
    ErrInvalidParameters: Thrown if the 'self' or 'name' is set to NULL
    ErrVariableNotDefined: Thrown if a variable description with the given name can not be found 
                           within the Variable Description Handler
*/
inst_error_t *remove_var_desc_by_name(prog_hand_t *prog_handler, var_desc_hand_t *self, 
        char *name);

/*
Gets a Variable Description from the Variable Description Handler

*prog_handler: The program handler that contains the class and error handlers
*self: The Variable Description Handler to remove the Variable Description from
**dest: A pointer to the Variable Description that will be found 
*name: The name of the variable description to get

Errors:
    ErrInvalidParameters: Thrown if any of the values are set to NULL
    ErrVariableNotDefined: Thrown if a variable description with the given name can not be found
                           within the Variable Description Handler
*/
inst_error_t *get_var_desc(prog_hand_t *prog_handler, var_desc_hand_t *self, var_desc_t **dest,
        char *name);

#endif