/*
Program Handler
By Ciaran Gruber

The Program Handler structure contains the error handling and class handling structures used
throughout the library

File-specific:
Program Handler - Header File
The structures used to handle the program
*/

#ifndef PROGRAM_HANDLER
#define PROGRAM_HANDLER

#include "../class-handler/class_handler.h"
#include "../error-handler/error_handler.h"

/* A structure containing all the handlers required for the program */
typedef struct {
    cls_hand_t *cls_handler; // The class handler for the program
    err_hand_t *err_handler; // The error handler for the program
} prog_hand_t;

/*
Frees the memory that a Program Handler takes including the class and error handlers

*src: The Program Handler to clear
*/
void free_prog_hand(prog_hand_t *src);

#endif