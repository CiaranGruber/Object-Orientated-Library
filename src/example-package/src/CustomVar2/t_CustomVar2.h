/*
<Custom Var 2> Type
By <Author>

<Type Description>

Parent Class: <Custom Var 2>

File-specific:
<Custom Var 2> Type - Header File
The structures used to manage the <Custom Var> class and instances
*/

#ifndef TYPE_CUSTOM_VAR_2
#define TYPE_CUSTOM_VAR_2

#include "../../dependencies/pkg_dev_lang.h"
#include "../CustomVar/t_CustomVar.h"

#define CUSTOM_VAR_CLS_NAME "CustomVar" // The class name that is used to represent a <Custom Var 2>

/* A type of variable used to represent a <Custom Var 2> instance */
typedef inst_custom_var_t inst_custom_var_2_t;
/* A type of class used to represent a <Custom Var 2> class */
typedef cls_custom_var_t cls_error_t;

/*
Creates a new <Custom Var 2> class and stores it into the Class Handler within the program
Note: The parent class must have been created before this class is created

*prog_handler: The program handler that contains the class and error handlers

Parent Class:
    <Custom Var>

Errors:
    ErrOutOfMemory: Thrown if there is not enough memory to create an store the class
    ErrClassAlreadyExists: Thrown if the class already exists within the program handler
*/
inst_error_t *new_custom_var_2_cls(prog_hand_t *prog_handler);

/*
Initialises a <Custom Var 2> class by creating the relevant functions and variables within the class.
Class dependencies do not need to be initialised in order for initialisation

*prog_handler: The program handler that contains the class and error handlers

Class Dependencies:
    <Dependencies>

Error:
    ErrOutOfMemory: Thrown if there is not enough memory to create the functions and class variables
    ErrClassNotDefined: Thrown if any required classes do not already exist in the program handler
*/
inst_error_t *init_custom_var_2_cls(prog_hand_t *prog_handler);

#endif