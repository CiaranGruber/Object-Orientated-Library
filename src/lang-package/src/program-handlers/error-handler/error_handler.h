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

#include "../../typedefs.h"

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

Errors:
    ErrInvalidParameters: Thrown if 'error' is set to NULL
*/
inst_error_t *add_err(prog_hand_t *prog_handler, char *error_name);

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

Errors:
    ErrInvalidParameters: Thrown if 'error' is set to NULL
*/
inst_error_t *remove_err(prog_hand_t *prog_handler, char *error_name);

/*
Compares an instance of an error to the expected error that was to be produced

*actual: The error instance that was produced by the function
*expected: The name of the error that was expected to occur

Returns: A boolean value representing whether the error and the given name is the same
*/
bool err_is_equal(inst_error_t *actual, char *expected);

/*
Creates a new instance of an error and returns a pointer to the new error

*prog_handler: The program handler that contains the class and error handlers
*error_type: The name of the error type

Returns: The error associated with the given type
*/
inst_error_t *new_error(prog_hand_t *prog_handler, char *error_type);

#endif