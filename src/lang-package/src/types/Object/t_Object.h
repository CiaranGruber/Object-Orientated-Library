/*
Object Type
By Ciaran Gruber

The Object class and instance provides a base class that all functions should be based off of by
default

Parent Class: None

File-specific:
Object Type - Header File
The structures used to manage the Object class and instances
*/

#ifndef TYPE_OBJECT
#define TYPE_OBJECT

/* The class name that is used to represent an Object */
#define OBJECT_CLS_NAME "Object"

#include "../../typedefs.h"

/*
Creates a new Object class and stores it into the Class Handler within the program

*prog_handler: The program handler that contains the class and error handlers

Parent Class: None

Errors:
    ErrOutOfMemory: Thrown if there is not enough memory to create an store the class
    ErrClassAlreadyExists: Thrown if the class already exists within the program handler
*/
inst_error_t *new_object_cls(prog_hand_t *prog_handler);

/*
Initialises an Object class by creating the relevant functions and variables within the class. 
Note:
All class dependencies must have been created (not necessarily initialised) and exist within
the class handler

*prog_handler: The program handler that contains the class and error handlers

Class Dependencies:
    Object
    Integer
    String

Errors:
    ErrOutOfMemory: Thrown if there is not enough memory to create the functions and class variables
    ErrClassNotDefined: Thrown if any required classes do not already exist in the program handler
*/
inst_error_t *init_object_cls(prog_hand_t *prog_handler);

/*
Type: Non-Static

Constructs an Object by setting each of its member fields to NULL

Parameters: None

Returns: None
*/
inst_error_t *init_object_inst(prog_hand_t *prog_handler, inst_object_t *object,
                                var_t *void_return, var_t **void_params);

#endif