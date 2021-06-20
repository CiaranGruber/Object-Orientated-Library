/*
String Type
By Ciaran Gruber

The String class provides a method for storing strings and is composed of Char types

Parent Class: None

File-specific:
String Type - Header File
The structures used to manage the String class and instances
*/

#ifndef TYPE_STRING
#define TYPE_STRING

#define STRING_CLASS_NAME "String" // The class name that is used to represent an Object

#include "../../typedefs.h"

/* A type of variable used to represent a String instance */
typedef inst_object_t inst_string_t;
/* A type of class used to represent a String class */
typedef cls_object_t cls_string_t;

/*
Creates a new String class and stores it into the Class Handler within the program
Note: The parent class must have been created before this class is created

*prog_handler: The program handler that contains the class and error handlers

Parent Class: Object

Errors:
    ErrOutOfMemory: Thrown if there is not enough memory to create an store the class
    ErrClassAlreadyExists: Thrown if the class already exists within the program handler
*/
inst_error_t *new_string_cls(prog_hand_t *prog_handler, cls_string_t *dest);

/*
Initialises a String class by creating the relevant functions and variables within the class. 
Note:
All class dependencies must have been created (not necessarily initialised) and exist within
the class handler

*prog_handler: The program handler that contains the class and error handlers

Class Dependencies:
    Char

Errors:
    ErrOutOfMemory: Thrown if there is not enough memory to create the functions and class variables
    ErrClassNotDefined: Thrown if any required classes do not already exist in the program handler
*/
inst_error_t *init_string_cls(prog_hand_t *prog_handler);

#endif