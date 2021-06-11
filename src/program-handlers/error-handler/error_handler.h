/*
Error Handler
By Ciaran Gruber

The Error Handler structure is used to handle errors within the program

File-specific:
Error Handler - Header File
The structures used to handle errors
*/

#ifndef ERROR_HANDLING
#define ERROR_HANDLING

#include <stdlib.h>
#include "../program-handler/program_handler.h"
#include "../../types/type-error/t_Error.h"

/* A node in the Error Handler that contains an allowed error and a link to the next node */
typedef struct err_hand_node err_hand_node_t;

/* A node in the Error Handler that contains an allowed error and a link to the next node */
struct err_hand_node {
    cls_error_t *allowed_error; // The error that is allowed as part of the Error Handler
    err_hand_node_t *next;      // A pointer to the next node in the Error Handler
};

/* A structure that holds the allowed errors contained in a Error Handler */
typedef struct {
    err_hand_node_t *first; // A pointer to the first node in the Error Handler
} err_hand_t;

/*
Frees the memory occupuied by a Error Handler structure

*src: The Error Handler structure whose memory is to be freed
*/
void free_err_hand(err_hand_t *src);

/*
Adds a class to the Error Handler if the given error does not already exist

*self: The program handler that contains the class and error handlers
*error: The error class to add to the Error Handler
*/
void add_err(prog_hand_t *self, cls_error_t *error);

/*
Handles any existing errors by exiting the program if the errors have not been cauught as well as
printing the related error messages

*self: The program handler that contains the class and error handlers
*error_instance: The error class to add to the Error Handler
*/
void handle_err(prog_hand_t *self, inst_error_t *error_instance);

/*
Deletes an error from the Error Handler based upon the class of error

*self: The program handler that contains the class and error handlers
*error: The error class to delete from the Error Handler
*/
void del_err(prog_hand_t *self, cls_error_t *error);

#endif