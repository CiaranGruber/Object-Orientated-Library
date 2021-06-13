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

#include <stdbool.h>
#include <stdlib.h>
#include "../../program-handlers/variable-description-handler/var_desc_handler.h"
#include "../../program-handlers/variable-handler/variable_handler.h"
#include "../../program-handlers/static-function-handler/static_function_handler.h"
#include "../../program-handlers/program-handler/program_handler.h"
#include "../variable/variable.h"
#include "../variable/var_description.h"

/* A structure that holds the various features contained in a Class */
struct gen_class {
    char *class_name;             // A string representing the type
    /*
    A boolean value representing whether an instance of the class has instance variables or
    unstructured data

    Note:
    Most class will set this to true. Variables who inherit only from Object and do not represent
    their data as a variable handler should be the only ones that have this set to 'true'.
    Furthermore, classes who do not have their data managed with a variable handler may not be used
    as a parameter in functions as the variable may not have the members fields called for in a
    function
    */
    bool uses_inst_var_handler;
    size_t size;                    // An integer representing the size of the variable
    class_t *parent;                // The parent Class which this class inherits from
    s_funct_hand_t *static_methods; // The function handler for the class
    funct_hand_t *inst_methods;     // The method handler for instances of the class
    var_hand_t *class_vars;         // The variables shared by all members of the class
    var_desc_hand_t *mem_fields;    // The member fields in instances of this class
};

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

#endif