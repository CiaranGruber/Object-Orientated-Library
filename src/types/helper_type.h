/*
Type Construction Helper Functions
By Ciaran Gruber

The functions defined are used to help in the process of creating and initialising classes

Parent Class: None

File-specific:
Type Construction Helper Functions - Header File
The function prototypes for the helper functions defined
*/

#ifndef TYPE_CONSTRUCTION_HELPER_FUNCTIONS
#define TYPE_CONSTRUCTION_HELPER_FUNCTIONS

#include "../program-handlers/program-handler/program_handler.h"

/*
Initialises the Non-Static Function Handler for a given Class

*prog_handler: The program handler that contains the class and error handlers
*class: The class that the Non-Static Function Handler will be initialised for

Errors:
    ErrOutOfMemory: Thrown if there is not enough memory to create the Function Handler
*/
inst_error_t *init_inst_handler(prog_hand_t *prog_handler, class_t *class);

/*
Initialises the Static Function Handler for a given Class

*prog_handler: The program handler that contains the class and error handlers
*class: The class that the Static Function Handler will be initialised for

Errors:
    ErrOutOfMemory: Thrown if there is not enough memory to create the Function Handler
*/
inst_error_t *init_static_handler(prog_hand_t *prog_handler, class_t *class);

/*
Initialises the Variable Handler used for handling class variables for a given Class

*prog_handler: The program handler that contains the class and error handlers
*class: The class that the Variable Handler will be initialised for

Errors:
    ErrOutOfMemory: Thrown if there is not enough memory to create the Function Handler
*/
inst_error_t *init_class_variables(prog_hand_t *prog_handler, class_t *class);

/*
Initialises the Variable Description Handler used for handling member fields for a given Class

*prog_handler: The program handler that contains the class and error handlers
*class: The class that the Variable Description Handler will be initialised for

Errors:
    ErrOutOfMemory: Thrown if there is not enough memory to create the Function Handler
*/
inst_error_t *init_member_fields(prog_hand_t *prog_handler, class_t *class);

#endif