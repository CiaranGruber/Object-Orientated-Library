/*
Object Type
By Ciaran Gruber

The Object class and instance provides a base class that all functions should be based off of by
default

Parent Class: None

File-specific:
Object Type - Code File
The code used to provide for the implementation of a Object type
*/

#include <string.h>
#include "t_Object.h"
#include "../type_creator.h"
#include "../String/t_String.h"
#include "../Integer/t_Integer.h"
#include "../../base-program/class/class.h"
#include "../../program-handlers/error-handler/error_handler.h"
#include "../../program-handlers/class-handler/class_handler.h"
#include "../../program-handlers/variable-handler/variable_handler.h"
#include "../../base-program/variable/variable.h"
#include "../../base-program/function/function.h"

// Initialisation Functions - Used to initialise the class

static inst_error_t *add_init_object_inst(prog_hand_t *prog_handler, cls_object_t *object_class);
static inst_error_t *add_to_string(prog_hand_t *prog_handler, cls_object_t *object_class,
        cls_string_t *string_class);
static inst_error_t *add_str_len(prog_hand_t *prog_handler, cls_object_t *object_class,
        cls_integer_t *int_class);
static inst_error_t *add_new_copy_vals(prog_hand_t *prog_handler, cls_object_t *object_class);

// Non-Static Functions

static inst_error_t *to_string(prog_hand_t *prog_handler, inst_object_t *object,
        inst_string_t *return_var, inst_object_t **params);
static inst_error_t *str_len(prog_hand_t *prog_handler, inst_object_t *self,
        inst_integer_t *return_var, var_t **void_params);
static inst_error_t *new_copy_vals(prog_hand_t *prog_handler, inst_object_t *self, 
        var_t *void_return, inst_object_t **params);

inst_error_t *new_object_cls(prog_hand_t *prog_handler) {
    inst_error_t *error;

    error = new_class(prog_handler, OBJECT_CLS_NAME, NULL, true, 0);
    return error;
}

inst_error_t *init_object_cls(prog_hand_t *prog_handler) {
    inst_error_t *error;

    // Classes
    cls_object_t *object_class;
    cls_integer_t *int_class;
    cls_string_t *string_class;

    // Get Object class
    error = get_class(prog_handler, &object_class, OBJECT_CLS_NAME);
    if (error != NULL) return error;

    // Get Integer class
    error = get_class(prog_handler, &int_class, INTEGER_CLS_NAME);
    if (error != NULL) return error;

    // Get String class
    error = get_class(prog_handler, &string_class, STRING_CLASS_NAME);
    if (error != NULL) return error;

    // Initialise class
    error = init_class(prog_handler, object_class);
    if (error != NULL) return error;

    // Add Functions
    error = add_init_object_inst(prog_handler, object_class);
    if (error != NULL) return NULL;
    error = add_to_string(prog_handler, object_class, string_class);
    if (error != NULL) return NULL;
    error = add_str_len(prog_handler, object_class, int_class);
    if (error != NULL) return NULL;
    error = add_init_object_inst(prog_handler, object_class);
    if (error != NULL) return NULL;
}

static inst_error_t *add_init_object_inst(prog_hand_t *prog_handler, cls_object_t *object_class) {
    inst_error_t *error;
    function_t *new_func;
    class_t **param_types;
    int param_count = 0;
    
    new_func = (function_t *)malloc(sizeof(function_t));
    if (new_func == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }

    param_types = NULL;

    error = new_function(prog_handler, new_func, OBJECT_CLS_NAME, init_object_inst, NULL, 
                            param_types, param_count);
    if (error != NULL) return error;
    error = add_function(prog_handler, object_class, new_func);
    if (error != NULL) return error;
}

static inst_error_t *add_to_string(prog_hand_t *prog_handler, cls_object_t *object_class,
        cls_string_t *string_class) {
    inst_error_t *error;
    function_t *new_func;
    class_t **param_types;
    int param_count = 1;
    
    new_func = (function_t *)malloc(sizeof(function_t));
    if (new_func == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }

    param_types = NULL;

    error = new_function(prog_handler, new_func, "to_string", to_string, string_class, param_types,
                            param_count);
    if (error != NULL) return error;
    error = add_function(prog_handler, object_class, new_func);
    if (error != NULL) return error;
}

static inst_error_t *add_str_len(prog_hand_t *prog_handler, cls_object_t *object_class,
        cls_integer_t *int_class) {
    inst_error_t *error;
    function_t *new_func;
    class_t **param_types;
    int param_count = 0;
    
    new_func = (function_t *)malloc(sizeof(function_t));
    if (new_func == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }

    param_types = NULL;

    error = new_function(prog_handler, new_func, "str_len", str_len, int_class, param_types,
                            param_count);
    if (error != NULL) return error;
    error = add_function(prog_handler, object_class, new_func);
    if (error != NULL) return error;
}

static inst_error_t *add_new_copy_vals(prog_hand_t *prog_handler, cls_object_t *object_class) {
    inst_error_t *error;
    function_t *new_func;
    class_t **param_types;
    int param_count = 0;
    
    new_func = (function_t *)malloc(sizeof(function_t));
    if (new_func == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }

    param_types = NULL;

    error = new_function(prog_handler, new_func, OBJECT_CLS_NAME, new_copy_vals, NULL, param_types,
                            param_count);
    if (error != NULL) return error;
    error = add_function(prog_handler, object_class, new_func);
    if (error != NULL) return error;
}

inst_error_t *init_object_inst(prog_hand_t *prog_handler, inst_object_t *object,
                                var_t *void_return, var_t **void_params) {
    inst_error_t *error;

    class_t *class = object->desc->type;

    // Free data if it is already initialised
    if (object->initialised) {
        if (class->uses_inst_var_handler) {
            free_var_hand(object->data);
        } else {
            free(object->data);
        }
    }

    // Do not initialise data if the class does not use the variable handler in its instances
    if (class->uses_inst_var_handler == false) {
        return NULL;
    }

    // Set up new variable handler
    var_hand_t *var_handler = (var_hand_t *)malloc(sizeof(var_hand_t));
    object->data = var_handler;

    // Add member fields to instance
    while (class != NULL) {
        var_desc_hand_node_t *node = class->mem_fields->first;
        // Loop through member fields in each class
        while (node != NULL) {
            var_desc_t *node_data = node->var_desc;
            var_t *new_variable = (var_t *)malloc(sizeof(var_t));

            // Set variable description
            error = set_var_desc(prog_handler, new_variable, node_data->type->class_name, 
                                    node_data->name);
            if (error != NULL) return error;

            // Initialise variable
            error = init_var(prog_handler, new_variable, NULL, 0);
            if (error != NULL) return error;

            // Add variable to instance member fields
            add_var(prog_handler, var_handler, new_variable);
            node = node->next;
        }
        class = class->parent;
    }

    return NULL;
}

/*
Copies the data from another object variable of the same type

Parameters:
1. Object - The object to copy from

Returns:
Object - The constructed object
*/
static inst_error_t *new_copy_vals(prog_hand_t *prog_handler, inst_object_t *self, 
        var_t *void_return, inst_object_t **params) {
    
    inst_object_t *other = params[0];

    if (self->desc->type != other->desc->type) {
        return new_error(prog_handler, "ErrIncompatibleTypes");
    }
}

/*
Converts the object to a simple string that can be printed to the console

Parameters:
1. Object - The object to convert to a string

Returns:
String - The string that is used to represent the variable
*/
static inst_error_t *to_string(prog_hand_t *prog_handler, inst_object_t *self, 
        inst_string_t *return_var, var_t **params) {
    inst_error_t *error;

    // Set up return variable
    inst_integer_t *length = (inst_integer_t *)malloc(sizeof(inst_integer_t));
    new_var(prog_handler, length);
    error = run_function(prog_handler, self, "str_len", length, NULL, 0);
    if (error != NULL) return error;
    set_var_desc(prog_handler, return_var, STRING_CLASS_NAME, return_var->desc->name);
    init_var(prog_handler, return_var, NULL, 0); // NEEDS TO PRODUCE A STRING ############################
}

/*
Gets the expected string length that would be produced after using to_string(). Note: For every
'to_string' method, there should also be a 'str_len' method

Parameters: None

Returns:
Integer - An integer representing the length of the string
*/
static inst_error_t *str_len(prog_hand_t *prog_handler, inst_object_t *self,
        inst_integer_t *return_var, var_t **void_params) {
    inst_error_t *error;
}