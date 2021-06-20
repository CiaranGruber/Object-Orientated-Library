/*
Error Type
By Ciaran Gruber

The Error class and instance provides a base class that all functions should be based off of by
default

Parent Class: Object

File-specific:
Error Type - Code File
The code used to provide for the implementation of an Error type
*/

#include <stdio.h>
#include <string.h>
#include "t_Error.h"
#include "../type_creator.h"
#include "../Object/t_Object.h"
#include "../String/t_String.h"
#include "../Integer/t_Integer.h"
#include "../../program-handlers/error-handler/error_handler.h"
#include "../../program-handlers/class-handler/class_handler.h"
#include "../../base-program/variable/variable.h"
#include "../../base-program/class/class.h"

// Initialisation Functions - Used to initialise the class

inst_error_t *new_error_cls(prog_hand_t *prog_handler) {
    inst_error_t *error;

    // Create class
    error = new_class(prog_handler, ERROR_CLS_NAME, OBJECT_CLS_NAME, true, 0);
    return error;
}

inst_error_t *init_error_cls(prog_hand_t *prog_handler) {
    inst_error_t *error;

    // Handlers
    s_funct_hand_t *static_methods;
    funct_hand_t *inst_methods;
    var_hand_t *class_vars;
    var_desc_hand_t *mem_fields;
    // Classes
    cls_object_t *object_class;
    cls_error_t *error_class;
    cls_string_t *string_class;
    cls_integer_t *integer_class;

    // Get Error class
    error = get_class(prog_handler, &error_class, ERROR_CLS_NAME);
    if (error != NULL) return error;

    // Get String class
    error = get_class(prog_handler, &string_class, STRING_CLASS_NAME);
    if (error != NULL) return error;

    // Initialise Error class
    error = init_class(prog_handler, error_class);

    // Add Functions

    // Add Member Fields
    error = add_member_field(prog_handler, error_class, "message", string_class);
    if (error != NULL) return error;
}

static inst_error_t *add_to_string(prog_hand_t *prog_handler, cls_error_t *error_class,
        cls_string_t *string_class, cls_integer_t *integer_class) {
    
}

static inst_error_t *add_str_len(prog_hand_t *prog_handler, cls_error_t *error_class,
        cls_object_t *object_class, cls_string_t *string_class, cls_integer_t *integer_class) {
    
}

/*
Prints the details related to an error to stderr 

Parameters:
1. Error - The error that is to be printed

Returns: None
*/
static inst_error_t *print_error(prog_hand_t *prog_handler, var_t *return_var,
        inst_error_t **params) {
    inst_error_t *error = params[0];

    
}