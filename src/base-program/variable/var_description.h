/*
Variable Description
By Ciaran Gruber

The Variable Description is used to describe an the key parts of an uninitialised variable that can
be used when constructing an instance

File-specific:
Variable Desciption - Header File
The structures used to describe a uninitialised variable
*/

#ifndef VARIABLE_DESCRIPTION
#define VARIABLE_DESCRIPTION

#include <stdlib.h>
#include "../../program-handlers/program-handler/program_handler.h"

/* A structure that holds the various features contained in a Variable */
struct gen_var_desc {
    class_t *type;    // A reference to the type used to represent a variable
    char *name;       // The name that is unique to the variable within its scope
    bool initialised; // A boolean representing whether the variable has been initialised yet
};

/*
Frees the memory occupuied by a Variable Description structure

*src: The Variable structure whose memory is to be freed
*/
void free_var_desc(var_desc_t *src);

/*
Creates a template for a new variable description by setting the relevant details to default values

*dest: The Variable Description that is to be reset

Errors:
    ErrInvalidParameters: Thrown if 'dest' is set to NULL
*/
inst_error_t *new_var_desc(prog_hand_t *prog_handler, var_desc_t *dest);

/*
Creates a new Variable Description based upon the type and name provided

*prog_handler: The program handler that contains the class and error handlers
*dest: The location to store the new variable
*type: The name of the variable's class
*name: The unique name for the variable that will be copied

Errors:
    ErrInvalidParameters: Thrown if 'dest', 'type', or 'name' is NULL
    ErrOutOfMemory: Thrown if there is not enough space to copy the name
    ErrClassNotDefined: Thrown if the given class type does not exist in the class handler
*/
inst_error_t *init_var_desc(prog_hand_t *prog_handler, var_desc_t *dest, char *type, char *name);

#endif