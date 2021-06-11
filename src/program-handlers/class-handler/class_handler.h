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

#include "../program-handler/program_handler.h"
#include "../../base-program/generic-class/class.h"

/* A node in the Class Handler that contains a class and a link to the next node */
typedef struct class_node class_node_t;

/* A node in the Class Handler that contains a class and a link to the next node */
struct class_node {
    class_t *class;     // The class contained within the node
    class_node_t *next; // The next node in the Class Handler
};

/* A structure that holds the classes contained in a Class Handler */
typedef struct {
    class_node_t *first; // The first class node in the Class Handler
} cls_hand_t;

/*
Frees the memory occupuied by a Class Handler structure

*src: The Class Handler structure whose memory is to be freed
*/
void free_cls_hand(cls_hand_t *src);

/*
Adds a class to the Class Handler assuming that the given class does not already exist

*prog_handler: The program handler that contains the class and error handlers
*class: The class to add to the Class Handler

Errors:
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
    ErrInvalidParameters: Thrown if class_name or *dest is equal to NULL
    ErrClassNotDefined: Thrown if the class_name does not exist in the Class Handler
*/
inst_error_t *get_class(prog_hand_t *prog_handler, class_t **dest, char *class_name);

#endif