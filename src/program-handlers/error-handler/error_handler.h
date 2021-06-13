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
#include "../../types/Error/t_Error.h"

/* A node in the Error Handler that contains an allowed error and a link to the next node */
typedef struct err_hand_node err_hand_node_t;

/* A node in the Error Handler that contains an allowed error and a link to the next node */
struct err_hand_node {
    cls_error_t *allowed_error; // The error that is allowed as part of the Error Handler
    err_hand_node_t *next;      // A pointer to the next node in the Error Handler
};

/* A structure that holds the allowed errors contained in a Error Handler */
struct gen_err_hand {
    err_hand_node_t *first; // A pointer to the first node in the Error Handler
};

/*
Frees the memory occupuied by a Error Handler structure

*src: The Error Handler structure whose memory is to be freed
*/
void free_err_hand(err_hand_t *src);

/*
Initialises an Error Handler by resetting the structure without freeing memory

*src: The Error Handler to initialise
*/
void init_err_hand(err_hand_t *src);

/*
Adds a class to the Error Handler if the given error does not already exist

*prog_handler: The program handler that contains the class and error handlers
*error: The error class to add to the Error Handler
*/
inst_error_t *add_err(prog_hand_t *prog_handler, cls_error_t *error);

/*
Handles any existing errors by exiting the program if the errors have not been cauught as well as
printing the related error messages

*prog_handler: The program handler that contains the class and error handlers
*error_instance: The error class to add to the Error Handler
*/
void handle_err(prog_hand_t *prog_handler, inst_error_t *error_instance);

/*
Deletes an error from the Error Handler based upon the class of error

*prog_handler: The program handler that contains the class and error handlers
*error: The error class to delete from the Error Handler
*/
inst_error_t *remove_err(prog_hand_t *prog_handler, cls_error_t *error);

#endif