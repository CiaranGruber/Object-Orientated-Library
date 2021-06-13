/*
ErrFunctionNotDefined Type
By Ciaran Gruber

The ErrFunctionNotDefined type is a type of error that is thrown when the requested function is
not defined yet

Parent Class: Error

File-specific:
ErrFunctionNotDefined type - Header File
The structures used to manage the ErrFunctionNotDefined class and instances
*/

#ifndef TYPE_ERR_FUNCTION_NOT_DEFINED
#define TYPE_ERR_FUNCTION_NOT_DEFINED

#include "../../../../program-handlers/program-handler/program_handler.h"

/*
Creates a new ErrFunctionNotDefined class and stores it into the Class Handler within the program
Note: The parent class must have been created before this class is created

*prog_handler: The program handler that contains the class and error handlers

Parent Class:
    Error

Errors:
    ErrOutOfMemory: Thrown if there is not enough memory to create an store the class
    ErrClassAlreadyExists: Thrown if the class already exists within the program handler
*/
inst_error_t *new_err_function_not_defined_cls(prog_hand_t *prog_handler);

/*
Initialises an Error class by creating the relevant functions and variables within the class.
Class dependencies do not need to be initialised in order for initialisation

*prog_handler: The program handler that contains the class and error handlers

Class Dependencies:
    String

Error:
    ErrOutOfMemory: Thrown if there is not enough memory to create the functions and class variables
    ErrClassNotDefined: Thrown if any required classes do not already exist in the program handler
*/
inst_error_t *init_err_function_not_defined_cls(prog_hand_t *prog_handler, cls_error_t *dest);

#endif