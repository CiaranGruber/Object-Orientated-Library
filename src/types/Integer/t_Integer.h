/*
Integer Type
By Ciaran Gruber

The Integer Class is one of the base variable types that hold data in its own data holding.
Therefore, the integer class would not inherit member fields and data is accessed directly

Parent Class: Object

File-specific:
Integer Type - Header File
The structures used to manage the Integer class and instances
*/

#ifndef TYPE_INTEGER
#define TYPE_INTEGER

#define INTEGER_CLASS_NAME "Integer" // The class name that is used to represent an Integer

#include "../../program-handlers/program-handler/program_handler.h"
#include "../Object/t_Object.h"

/* A type of variable used to represent an Integer instance */
typedef inst_object_t inst_integer_t;
/* A type of class used to represent an Integer class */
typedef cls_object_t cls_integer_t;

/*
Creates a new Integer class and stores it into the Class Handler within the program
Note: The parent class must have been created before this class is created

*prog_handler: The program handler that contains the class and error handlers

Parent Class: Object

Errors:
    ErrOutOfMemory: Thrown if there is not enough memory to create an store the class
    ErrClassAlreadyExists: Thrown if the class already exists within the program handler
*/
inst_error_t *new_integer_cls(prog_hand_t *prog_handler);

/*
Initialises an Integer class by creating the relevant functions and variables within the class. 
Note:
All class dependencies must have been created (not necessarily initialised) and exist within
the class handler

*prog_handler: The program handler that contains the class and error handlers

Class Dependencies:
    Integer

Errors:
    ErrOutOfMemory: Thrown if there is not enough memory to create the functions and class variables
    ErrClassNotDefined: Thrown if any required classes do not already exist in the program handler
*/
inst_error_t *init_integer_cls(prog_hand_t *prog_handler);

#endif