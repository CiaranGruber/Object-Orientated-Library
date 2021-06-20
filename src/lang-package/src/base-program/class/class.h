/*
Class
By Ciaran Gruber

A Class provides a the type information for variables, containing the methods as well as the member
fields used within a Variable

File-specific:
Class - Header File
The structures used to represent a Class
*/

#ifndef CLASS
#define CLASS

#define MAX_FUNCT 50

#include "../../typedefs.h"

/*
Frees the memory occupuied by a Class structure

*src: The Class structure whose memory is to be freed 
*/
void free_class(class_t *dest);

/*
Creates a new instance of the class by using the given constructors to construct the instance

*prog_handler: The program handler that contains the class and error handlers
*dest: The destination to store the new instance variable into - Variable description must be set
**params: The parameters used to construct the instance
param_count: The number of parameters to use when creating the instance

Errors: Any errors when initialising the instance
    ErrInvalidParameters: Thrown if 'dest' or 'dest->desc' is set to NULL
    ErrOutOfMemory: Thrown if there is not enough memory
*/
inst_error_t *init_var(prog_hand_t *prog_handler, var_t *dest, var_t **params, int param_count);

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
Gets a specified class variable from the class based upon its name

*prog_handler: The program handler that contains the class and error handlers
*self: The class that has the given class variable
**dest: A pointer to the class variable
*var_name: The name of the class variable

Errors:
    ErrInvalidParameters: Thrown if 'self', 'dest', or 'var_name' is set to NULL
    ErrVariableNotDefined: Thrown if the given class variable does not exist
*/
inst_error_t *get_class_var(prog_hand_t *prog_handler, class_t *self, var_t **dest,
        char *var_name);

/*
Gets a reference to the parent of the specified class

*prog_handler: The program handler that contains the class and error handlers
*self: The class to get the parent class of
**dest: A pointer to the parent class

Errors:
    ErrInvalidParameters: Thrown if 'self' or 'dest' is set to NULL
*/
inst_error_t *get_parent(prog_hand_t *prog_handler, class_t *self, class_t **dest);

#endif