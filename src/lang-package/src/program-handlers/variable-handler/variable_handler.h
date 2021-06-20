/*
Variable Handler
By Ciaran Gruber

The Variable Handler structure is used to handle Variables in instances and classes 

File-specific:
Variable Handler - Header File
The structures used to handle the Variables within an instance and class
*/

#ifndef VARIABLE_HANDLER
#define VARIABLE_HANDLER

#include "../../typedefs.h"

/*
Frees the memory occupuied by a Variable Handler structure

*src: The Variable Handler structure whose memory is to be freed
*/
void free_var_hand(var_hand_t *src);

/*
Creates a new Variable Handler by resetting the source variable

*prog_handler: The program handler that contains the class and error handlers
*dest: The pointer to the Variable Handler to initialise

Errors:
    ErrInvalidParameters: Thrown if the Variable Handler is set to NULL
*/
inst_error_t *var_hand_create(prog_hand_t *prog_handler, var_hand_t *src);

/*
Adds a variable to the Variable Handler

*prog_handler: The program handler that contains the class and error handlers
*self: The Variable Handler that is to be modified
*variable: The variable to add to the Variable Handler

Errors:
    ErrInvalidParameters: Thrown if the Variable Handler or variable is set to NULL
    ErrOutOfMemory: Thrown if there is not enough memory to add a Variable if required
    ErrVariableNameTaken: Thrown if a variable with the same name already exists in the Variable
                          Handler
*/
inst_error_t *add_var(prog_hand_t *prog_handler, var_hand_t *self, var_t *variable);

/*
Removes a Variable from the Variable Handler

*prog_handler: The program handler that contains the class and error handlers
*self: The Variable Handler to remove the Variable from
*variable: The variable to remove from the Variable Handler

Errors:
    ErrInvalidParameters: Thrown if '*self' or '*variable' is set to NULL
    ErrVariableNotDefined: Thrown if the given variable can not be found within the Variable Handler
*/
inst_error_t *remove_var(prog_hand_t *prog_handler, var_hand_t *self, var_t *variable);

/*
Removes a Variable from the Variable Handler by its name and parameters

*prog_handler: The program handler that contains the class and error handlers
*self: The Variable Handler to remove the Variable from
*name: The name of the variable to remove

Errors:
    ErrInvalidParameters: Thrown if '*self' or '*name' is set to NULL
    ErrVariableNotDefined: Thrown if a variable with the given name can not be found within the
                           Variable Handler
*/
inst_error_t *remove_var_by_name(prog_hand_t *prog_handler, var_hand_t *self, char *name);

/*
Gets a Variable from the Variable Handler

*prog_handler: The program handler that contains the class and error handlers
*self: The Variable Handler to remove the Variable from
**dest: A pointer to the Variable that will be found 
*name: The name of the variable to get

Errors:
    ErrInvalidParameters: Thrown if any of the values are set to NULL
    ErrVariableNotDefined: Thrown if a variable with the given name can not be found within the
                           Variable Handler
*/
inst_error_t *get_var(prog_hand_t *prog_handler, var_hand_t *self, var_t **dest, char *name);

#endif