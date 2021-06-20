/*
Package Title: Lang Package - Development
Package Author: Ciaran Gruber

Dependencies:
    Lang Package - End User

Package Description:
This package contains the package used when developing types that may be used by the library
*/

#ifndef PKG_LANG_DEV
#define PKG_LANG_DEV

#include <stdbool.h>
#include <stdlib.h>
#include "pkg_eu_lang.h"

/*
Sets the class details used when initialising a new class by setting the major elements of a class

*prog_handler: The program handler that contains the class and error handlers
*class_name: The name of the class that is to be created
*parent_class: The name of the parent class of the class to be created, set to NULL for no parent
                class
managed_data: A boolean value representing whether the data is managed or unmanaged
size: The size of the data when creating unmanaged classes

Errors:
    ErrInvalidParameters: Thrown if 'class' or 'class_name' is set to NULL
    ErrOutOfMemory: Thrown if there is not enough memory to create the classes
    ErrClassNotDefined: Thrown if the parent class does not exist in the program handler yet
*/
inst_error_t *new_class(prog_hand_t *prog_handler, char *class_name, char *parent_class,
        bool managed_data, size_t size);

/*
Initialises the handlers used within a class

*prog_handler: The program handler that contains the class and error handlers
*class: The class that will be initialised

Errors:
    ErrInvalidParameters: Thrown if 'class' is set to NULL
    ErrOutOfMemory: Thrown if there is not enough memory to initialise the package
*/
inst_error_t *init_class(prog_hand_t *prog_handler, class_t *class);

/*
Creates a new function by specifying every individual part of the function

*prog_handler: The program handler that contains the class and error handlers
*dest: A pointer to where the Function structure will be stored
*name: The name of the function that is to be created
(*function)(prog_hand_t *, var_t *, var_t *, var_t **): A pointer to the function that this Function
                                                        will run
*inst_type: The class of the instance that will be passed to the function
*return_type: The class that the function will return
**param_types: A list of classes that correlate to the types for each of the parameters
param_count: The number of parameters in the function

Errors:
    ErrInvalidParameters: Thrown if: 'dest', 'name', or '(*function)' is set to NULL
    ErrOutOfMemory: Thrown when there is not enough memory to create the function
*/
inst_error_t *new_function(prog_hand_t *prog_handler, function_t *dest, char *name,
        inst_error_t *(*function)(prog_hand_t *, var_t *, var_t *,var_t **), class_t *return_type,
        class_t **param_types, int param_count);

/*
Creates a new function by specifying every individual part of the function

*prog_handler: The program handler that contains the class and error handlers
*dest: A pointer to where the Static Function structure will be stored
*name: The name of the function that is to be created
(*function)(prog_hand_t *, var_t *, var_t **): A pointer to the function that this Static Function
                                               will run
*return_type: The class that the function will return
**param_types: A list of classes that correlate to the types for each of the parameters
param_count: The number of parameters in the function

Errors:
    ErrInvalidParameters: Thrown if: 'dest', 'name', or '(*function)' is set to NULL
    ErrOutOfMemory: Thrown when there is not enough memory to create the function
*/
inst_error_t *new_s_function(prog_hand_t *prog_handler, s_function_t *dest, char *name,
        inst_error_t *(*function)(prog_hand_t *, var_t *,var_t **), class_t *return_type,
        class_t **param_types, int param_count);

/*
Attempts to add a function to a class

*prog_handler: The program handler that contains the class and error handlers
*class: The class to add the function to
*function: The function to add to the class

Errors:
    ErrInvalidParameters: Thrown if 'class' or 'function' is set to NULL
    ErrOutOfMemory: Thrown if there is not enough memory needed to add the function to the class
    ErrFunctionAlreadyExists: Thrown if the given function already exists in the class
*/
inst_error_t *add_function(prog_hand_t *prog_handler, class_t *class, function_t *function);

/*
Removes a function from a class

*prog_handler: The program handler that contains the class and error handlers
*self: The class to remove the function from
*function: The function to remove from the class

Errors:
    ErrInvalidParameters: Thrown if 'class' or 'function' is set to NULL
    ErrFunctionNotDefined: Thrown if the given function can not be found within the class
*/
inst_error_t *remove_function(prog_hand_t *prog_handler, class_t *class, function_t *function);

/*
Removes a function from the class by its name and parameters

*prog_handler: The program handler that contains the class and error handlers
*class: The class to remove the function from
*name: The name of the function to remove
**param_types: The list of parameters that are within the function
param_count: The number of parameters within the function that is to be removed

Errors:
    ErrInvalidParameters: Thrown if 'class' or 'name' is set to NULL
    ErrFunctionNotDefined: Thrown if the given function can not be found within the class
*/
inst_error_t *remove_function_by_name(prog_hand_t *prog_handler, class_t *class, char *name,
        class_t **param_types, int param_count);

/*
Attempts to add a static function to a class

*prog_handler: The program handler that contains the class and error handlers
*class: The class to add the function to
*function: The function to add to the class

Errors:
    ErrInvalidParameters: Thrown if 'class' or 'function' is set to NULL
    ErrOutOfMemory: Thrown if there is not enough memory needed to add the function to the class
    ErrFunctionAlreadyExists: Thrown if the given function already exists in the class
*/
inst_error_t *add_s_function(prog_hand_t *prog_handler, class_t *class, s_function_t *function);

/*
Removes a static function from a class

*prog_handler: The program handler that contains the class and error handlers
*class: The class to remove the function from
*function: The function to remove from the class

Errors:
    ErrInvalidParameters: Thrown if 'class' or 'function' is set to NULL
    ErrFunctionNotDefined: Thrown if the given function can not be found within the class
*/
inst_error_t *remove_s_function(prog_hand_t *prog_handler, class_t *class, s_function_t *function);

/*
Removes a static function from the class using its name and parameters

*prog_handler: The program handler that contains the class and error handlers
*class: The class to remove the function from
*name: The name of the function to remove
*return_type: The return type of the function
**param_types: The list of parameters that are within the function
param_count: The number of parameters within the function that is to be removed

Errors:
    ErrInvalidParameters: Thrown if 'class' or 'name' is set to NULL
    ErrFunctionNotDefined: Thrown if the given function can not be found within the class
*/
inst_error_t *remove_s_function_by_name(prog_hand_t *prog_handler, class_t *class, char *name,
        class_t **param_types, int param_count);

/*
Attempts to add a member field to a class

*prog_handler: The program handler that contains the class and error handlers
*class: The class to add the member field to
*name: The name of the member field to add to the class
*type: The type of the member field that is to be added

Errors:
    ErrInvalidParameters: Thrown if 'class', 'name', or 'type' is set to NULL
    ErrOutOfMemory: Thrown if there is not enough memory needed to add the member field to the class
    ErrVariableNameTaken: Thrown if the given member field already exists in the class
*/
inst_error_t *add_member_field(prog_hand_t *prog_handler, class_t *class, char *name,
        class_t *type);

/*
Attempts to add a class variable to a class

*prog_handler: The program handler that contains the class and error handlers
*class: The class to add the class variable to
*name: The name of the class variable to add to the class
*type: The type of the class variable that is to be added

Errors:
    ErrInvalidParameters: Thrown if 'class' or 'class_var' is set to NULL
    ErrOutOfMemory: Thrown if there is not enough memory needed to add the class variable to the class
    ErrVariableNameTaken: Thrown if the given class variable already exists in the class
*/
inst_error_t *add_class_var(prog_hand_t *prog_handler, class_t *class, var_t *class_var);

#endif