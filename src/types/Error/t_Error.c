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
#include "../helper_type.h"
#include "../Object/t_Object.h"
#include "../String/t_String.h"
#include "../Integer/t_Integer.h"

// Initialisation Functions - Used to initialise the class

static inst_error_t *add_message(prog_hand_t *prog_handler, cls_error_t *error_class);
static inst_error_t *add_to_string(prog_hand_t *prog_handler, cls_error_t *error_class,
        cls_string_t *string_class, cls_integer_t *integer_class);
static inst_error_t *add_str_len(prog_hand_t *prog_handler, cls_error_t *error_class,
        cls_object_t *object_class, cls_string_t *string_class, cls_integer_t *integer_class);

inst_error_t *new_error_cls(prog_hand_t *prog_handler, cls_error_t *dest) {
    inst_error_t *error;

    // Create class name
    cls_integer_t *class = (cls_integer_t *)malloc(sizeof(cls_integer_t));
    class->class_name = (char *)malloc(strlen(ERROR_CLASS_NAME));
    if (class->class_name == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }
    strcpy(class->class_name, ERROR_CLASS_NAME);

    // Set parent class
    cls_object_t *object_class;
    error = get_class(prog_handler, &object_class, OBJECT_CLASS_NAME);
    if (error != NULL) return error;
    class->parent = object_class;

    // Set integer data description
    class->uses_inst_var_handler = false;
    class->size = sizeof(int);

    error = add_class(prog_handler, class);
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
    error = get_class(prog_handler, &error_class, ERROR_CLASS_NAME);
    if (error != NULL) return error;

    // Get String class
    error = get_class(prog_handler, &string_class, STRING_CLASS_NAME);
    if (error != NULL) return error;

    // Initialise Static Function Handler
    error = init_static_handler(prog_handler, error_class);
    if (error != NULL) return error;
    static_methods = error_class->static_methods;
    
    // Initialise Non-Static Function Handler
    error = init_inst_handler(prog_handler, error_class);
    if (error != NULL) return error;
    inst_methods = error_class->inst_methods;

    // Initialise Class Variable Handler
    error = init_class_variables(prog_handler, error_class);
    if (error != NULL) return error;
    class_vars = error_class->class_vars;

    // Initialise Member Field Handler
    error = init_member_fields(prog_handler, error_class);
    if (error != NULL) return error;
    mem_fields = error_class->mem_fields;

    // Add Functions

    // Add Member Fields
    error = add_message(prog_handler, error_class);
    if (error != NULL) return error;
}

static inst_error_t *add_to_string(prog_hand_t *prog_handler, cls_error_t *error_class,
        cls_string_t *string_class, cls_integer_t *integer_class) {
    
}

static inst_error_t *add_str_len(prog_hand_t *prog_handler, cls_error_t *error_class,
        cls_object_t *object_class, cls_string_t *string_class, cls_integer_t *integer_class) {
    
}

static inst_error_t *add_message(prog_hand_t *prog_handler, cls_error_t *error_class) {
    inst_error_t *error;

    var_desc_t *message = (var_desc_t *)malloc(sizeof(var_desc_t));
    error = new_var_desc(prog_handler, message);
    if (error == NULL) return error;
    error = init_var_desc(prog_handler, message, STRING_CLASS_NAME, "message");

    return error;
}

inst_error_t *new_error(prog_hand_t *prog_handler, char *error_type) {
    inst_error_t *error = (inst_error_t *)malloc(sizeof(inst_error_t));
    new_var(prog_handler, error);
    init_var_desc(prog_handler, error->desc, error_type, "error_var");
    init_var(prog_handler, error, NULL, 0);
    handle_err(prog_handler, error);
    return error;
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