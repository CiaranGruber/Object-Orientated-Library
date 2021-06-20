/*
Package Title: Lang Package - End User
Package Author: Ciaran Gruber

Package Description:
This package contains the package used when developing types that may be used by the library
*/

#ifndef PKG_LANG_EU
#define PKG_LANG_EU

/* A structure containing all the handlers required for the program */
typedef struct gen_prog_hand prog_hand_t;
/* A structure that holds the various features contained in a Static Function */
typedef struct gen_s_function s_function_t;
/* A structure that holds the various features contained in a Function */
typedef struct gen_function function_t;
/* A structure that holds the various features contained in a Class */
typedef struct gen_class class_t;
/* A structure that holds the various features contained in a Variable */
typedef struct gen_var var_t;

#define INTEGER_CLASS_NAME "Integer" // The class name that is used to represent an Integer
#define OBJECT_CLASS_NAME "Object" // The class name that is used to represent an Object
#define ERROR_CLASS_NAME "Error" // The class name that is used to represent an Error

/* A type of variable used to represent an Error instance */
typedef var_t inst_error_t;
/* A type of class used to represent an Error class */
typedef class_t cls_error_t;
/* A type of variable used to represent an Object instance */
typedef var_t inst_object_t;
/* A type of class used to represent an Object class */
typedef class_t cls_object_t;
/* A type of variable used to represent an Integer instance */
typedef inst_object_t inst_integer_t;
/* A type of class used to represent an Integer class */
typedef cls_object_t cls_integer_t;

#include <stdbool.h>

/*
Initialises the Language package and returns a program handler that can be used throughout the
program

Returns: A reference to the created program handler
*/
prog_hand_t *new_lang_package();

/*
Imports the Language package by creating and initialising each of the classes within the program

prog_handler: The program handler that the package is importing into

Errors:
    None due to error classes not existing
*/
inst_error_t *import_lang_package(prog_hand_t *prog_handler);

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
Runs a Static Function passing in the relevant parameters

*prog_handler: The program handler that contains the class and error handlers
*self: The class in which the function is located
*funct_name: The name of the function to run
*return_var: The variable to store the return value after running the function
**params: The list of parameters with which to run the function
param_count: The number of parameters in the params list

Returns: Returns a variable that is dependent on the function

Errors: Throws any errors related to the function that is run
    ErrInvalidParameters: Thrown if 'self' or 'funct_name' is set to NULL
*/
inst_error_t *run_s_function(prog_hand_t *prog_handler, class_t *self, char *funct_name, 
        var_t *return_var, var_t **params, int param_count);

/*
Gets the return type of the Function that would be run given the parameters

*prog_handler: The program handler that contains the class and error handlers
*self: The class that has the given function name
*funct_name: The name of the function to add
**return_type: A pointer to the class that will be returned
**param_types: A list of classes that define the parameters of the function
param_count: The number of parameters in the function

Errors:
    ErrInvalidParameters: Thrown if 'self' or 'funct_name' is set to NULL
    ErrFunctionNotDefined: Thrown if a function with the given parameters doesn't exist
*/
inst_error_t *get_return_type(prog_hand_t *prog_handler, class_t *self, char *funct_name,
        class_t **return_type, class_t **param_types, int param_count);

/*
Gets the return type of the Static Function that would be run given the parameters

*prog_handler: The program handler that contains the class and error handlers
*self: The class that has the given function name
*funct_name: The name of the function to add
**return_type: A pointer to the class that will be returned
**param_types: A list of classes that define the parameters of the function
param_count: The number of parameters in the function

Errors:
    ErrInvalidParameters: Thrown if 'self' or 'funct_name' is set to NULL
    ErrFunctionNotDefined: Thrown if a function with the given parameters doesn't exist
*/
inst_error_t *get_s_return_type(prog_hand_t *prog_handler, class_t *self, char *funct_name,
        class_t **return_type, class_t **param_types, int param_count);

/*
Gets a class from the Class Handler based upon the class name

*prog_handler: The program handler that contains the class and error handlers
**dest: The location to store the retrieved class pointer to
*class_name: The name of the class to retrieve from the Class Handler

Errors:
    ErrInvalidParameters: Thrown if 'dest' or 'class_name' is set to NULL
    ErrClassNotDefined: Thrown if the class_name does not exist in the Class Handler
*/
inst_error_t *get_class(prog_hand_t *prog_handler, class_t **dest, char *class_name);

/*
Gets a specified class variable from the class based upon its name

*prog_handler: The program handler that contains the class and error handlers
*self: The class that has the given class variable
*var_name: The name of the class variable

Errors:
    ErrInvalidParameters: Thrown if 'self', 'dest', or 'var_name' is set to NULL
    ErrVariableNotDefined: Thrown if the given class variable does not exist
*/
inst_error_t *get_class_var(prog_hand_t *prog_handler, class_t *self, var_t **dest,
        char *var_name);

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
Sets the values used to describe a variable that is required during initialisation

*prog_handler: The program handler that contains the class and error handlers
*dest: A pointer to the variable
*type: The name of the variable's class
*name: The unique name for the variable that will be copied

Errors:
    ErrInvalidParameters: Thrown if 'dest', 'type', or 'name' is NULL
    ErrOutOfMemory: Thrown if there is not enough space to copy the name
    ErrClassNotDefined: Thrown if the given class type does not exist in the class handler
*/
inst_error_t *set_var_desc(prog_hand_t *prog_handler, var_t *dest, char *type, char *name);

/*
Creates a new instance of a variable, copying the data exactly

*prog_handler: The program handler that contains the class and error handlers
*dest: The location to store the new variable
*data: The data that is to be copied into the variable

Errors:
    ErrInvalidParameters: Thrown if 'var_desc' or 'dest' is set to NULL
    ErrOutOfMemory: Thrown if there is not enough space to copy the instance data
    ErrInvalidDataFormat: Thrown if the variable class does not support unmanaged data
*/
inst_error_t *init_var_exact(prog_hand_t *prog_handler, var_t *dest, void *data);

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

/*
Adds a class to the Error Handler if the given error does not already exist

*prog_handler: The program handler that contains the class and error handlers
*error: The error class to add to the Error Handler

Errors:
    ErrInvalidParameters: Thrown if 'error' is set to NULL
*/
inst_error_t *add_err(prog_hand_t *prog_handler, char *error_name);

/*
Deletes an error from the Error Handler based upon the class of error

*prog_handler: The program handler that contains the class and error handlers
*error: The error class to delete from the Error Handler

Errors:
    ErrInvalidParameters: Thrown if 'error' is set to NULL
*/
inst_error_t *remove_err(prog_hand_t *prog_handler, char *error_name);

/*
Compares an instance of an error to the expected error that was to be produced

*prog_handler: The program handler that contains the class and error handlers
*actual: The error instance that was produced by the function
*expected: The name of the error that was expected to occur

Returns: A boolean value representing whether the error and the given name is the same
*/
bool err_is_equal(inst_error_t *actual, char *expected);

#endif