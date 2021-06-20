/*
Error Type
By Ciaran Gruber

The Error type provides the base type for all Error types

Parent Class: Object

File-specific:
Error type - Header File
The structures used to manage the Error class and instances
*/

#ifndef TYPE_ERROR
#define TYPE_ERROR

#define ERROR_CLS_NAME "Error" // The class name that is used to represent an Error

#include "../../typedefs.h"

/* A structure useds to represent the data used in an error variable */
typedef struct {
    cls_error_t *type;           // The type that is used to represent the error
    char *message;               // The message that is created by the error
    s_function_t *parent_function; // The parent function from which the error was produced
    inst_error_t *parent_error;  // The error that caused this error to be produced
} error_data_t;

/*
Creates a new Error class and stores it into the Class Handler within the program
Note: The parent class must have been created before this class is created

*prog_handler: The program handler that contains the class and error handlers

Parent Class:
    Object

Errors:
    ErrOutOfMemory: Thrown if there is not enough memory to create an store the class
    ErrClassAlreadyExists: Thrown if the class already exists within the program handler
*/
inst_error_t *new_error_cls(prog_hand_t *prog_handler);

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
inst_error_t *init_error_cls(prog_hand_t *prog_handler);

#endif