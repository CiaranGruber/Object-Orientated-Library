/*
Class Handler
By Ciaran Gruber

The Class Handler is used to handle classes within the program 

File-specific:
Class Handler - Header File
The structures used to handle classes within a program
*/

#ifndef CLASS_HANDLER
#define CLASS_HANDLER

#include "../../typedefs.h"

/*
Frees the memory occupuied by a Class Handler structure

*src: The Class Handler structure whose memory is to be freed
*/
void free_cls_hand(cls_hand_t *src);

/*
Initialises the Class Handler structure by resetting its values

*src: The Class Handler to initialise
*/
void init_cls_hand(cls_hand_t *src);

/*
Adds a class to the Class Handler assuming that the given class does not already exist

*prog_handler: The program handler that contains the class and error handlers
*class: The class to add to the Class Handler

Errors:
    ErrInvalidParameters: Thrown if 'class' is set to NULL
    ErrClassAlreadyExists: Thrown if the class is already contained within the Class Handler
    ErrOutOfMemory: Thrown if the class can not be added due to a lack of memory
*/
inst_error_t *add_class(prog_hand_t *prog_handler, class_t *class);

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
Checks whether a class exists and if it does, stores it in the 'dest' variable if it is specified

*prog_handler: The program handler that contains the class and error handlers
*result: A pointer to the integer where the result is meant to be stored
**dest: The location to store the retrieved class pointer to
*class_name: The name of the class to retrieve from the Class Handler

Errors:
    ErrInvalidParameters: Thrown if 'result' or 'class_name' is set to NULL
*/
inst_error_t *class_exists(prog_hand_t *prog_handler, bool *result, class_t **dest,
        char *class_name);

#endif