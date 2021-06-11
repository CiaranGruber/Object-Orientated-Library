/*
Generic Class Header File
By Ciaran Gruber

Used to provide a structure used to represent a generic class
*/

#ifndef GENERIC_CLASS
#define GENERIC_CLASS

#define MAX_FUNCT 50

#include <stdlib.h>
#include "../../program-handlers/function-handler/function_handler.h"
#include "../../program-handlers/program-handler/program_handler.h"
#include "../generic-variable/variable.h"
#include "../generic-function/function_set.h"

/* A structure that holds the various features contained in a Generic Class */
typedef struct gen_class class_t;

/* A structure that holds the various features contained in a Generic Class */
struct gen_class {
    char *class_name;            // A string representing the type
    size_t size;                 // An integer representing the size assuming a fixed size
    class_t *parent;             // The parent Generic Class which this class inherits from
    funct_hand_t *funct_handler; // The function handler for the Generic Class
    var_t **class_vars;          // The class-based variables that are a part of the Generic Class
    int class_var_count;         // The number of class-based variables
};

/*
Frees the memory occupuied by a Generic Class structure

*src: The Generic Function structure whose memory is to be freed 
*/
void free_class(class_t *dest);

/*
Creates a new Generic Class that can be added to the class handler

*prog_handler: The program handler that contains the class and error handlers
*dest: A pointer to where the Generic Class structure will be stored
*class_name: The name of the Generic Class
size: The size of the data in the class
*parent: The parent which the Generic Class will inherit from - Set to NULL for default
*funct_handler: The function handler used in the class - Set to NULL for default
**class_vars: A list of class variables or static member fields within the class
class_var_count: The number of class variables or static member fields within the class

Errors:
    ErrInvalidParameters: Thrown if either *class_name or *dest is NULL
*/
inst_error_t *new_class(prog_hand_t *prog_handler, class_t *dest, char *class_name, size_t size, 
        class_t *parent, funct_hand_t *funct_handler, var_t **class_vars, int class_var_count);

/*
Creates a new instance of the class by using the given constructors to construct the instance

*prog_handler: The program handler that contains the class and error handlers
*class_name: The name of the class that the instance is to be created from
*dest: The destination to store the new instance variable into
**params: The parameters used to construct the instance
param_count: The number of parameters to use when creating the instance

Errors:
    ErrInvalidParameters: Thrown if either *class_name or *dest are set to NULL
*/
inst_error_t *new_instance(prog_hand_t *prog_handler, char *class_name, var_t *dest, var_t **params, 
        int param_count);

#endif