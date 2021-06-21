/*
Function
By Ciaran Gruber

The Function is a type of function that is called by a instance and typically uses the instance data
to perform the function

File-specific:
Function - Code File
The code used to provide for the implementation of a Function
*/

#include <string.h>
#include "function.h"
#include "../../program-handlers/error-handler/error_handler.h"
#include "../class/class.h"
#include "../variable/variable.h"

void free_function(function_t *src) {
    if (src == NULL) return;

    free(src->name);
    free(src->param_types);
    free(src);
}

inst_error_t *new_function(prog_hand_t *prog_handler, function_t *dest, char *name,
        inst_error_t *(*function)(prog_hand_t *, var_t *, var_t *,var_t **), class_t *return_type,
        class_t **param_types, int param_count) {
    inst_error_t *error;
    if (dest == NULL || name == NULL || function == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Copy name
    dest->name = (char *)malloc(strlen(name)*sizeof(char));
    if (dest->name == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }
    // Copy passed values
    dest->function = function;
    dest->return_type = return_type;
    // Copy parameter types
    dest->param_types = (class_t **)malloc(param_count*sizeof(class_t *));
    if (dest->param_types == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }
    dest->param_count = param_count;

    return NULL;
}

inst_error_t *function_run(prog_hand_t *prog_handler, function_t *self, var_t *variable, 
        var_t *return_val, var_t **params, int param_count) {
    inst_error_t *error;
    if (self == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Check variable count
    if (self->param_count != param_count) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }
    // Check variable types
    for (int i = 0; i < param_count; i++) {
        class_t *curr_class = params[i]->desc->type;
        // Loop through to see if the variable is a child of a suitable class
        while (curr_class != NULL || !curr_class->has_managed_data) {
            if (curr_class == self->param_types[i]) {
                break;
            }
            curr_class = curr_class->parent;
        }
        // Suitable class was not found
        if (curr_class == NULL) {
            return new_error(prog_handler, "ErrInvalidParameters");
        }
    }
    // Format return variable
    set_var_desc(prog_handler, return_val, self->return_type->class_name, return_val->desc->name);
    error = run_function(prog_handler, return_val, "free_data", NULL, NULL, 0);
    if (error != NULL) return error;

    // Run function and handle any errors
    error = self->function(prog_handler, variable, return_val, params);
    return error;
}

inst_error_t *is_function_equal(prog_hand_t *prog_handler, bool *result, function_t *self,
        class_t **param_types, int param_count) {
    inst_error_t *error;
    if (result == NULL || self == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Check parameter count
    if (self->param_count != param_count) {
        *result = false;
        return NULL;
    }

    // Check parameters
    class_t *curr_class;
    for (int i = 0; i < param_count; i++) {
        curr_class = param_types[i];
        // Loop through to see if the variable is a child of a suitable class
        while (curr_class != NULL || !curr_class->has_managed_data) {
            if (curr_class == param_types[i]) {
                break;
            }
            curr_class = curr_class->parent;
        }
        // If parameter is not the same, function is not the same
        if (curr_class != param_types[i]) {
            *result = false;
            return NULL;
        }
    }

    // Return that they are the same
    *result = true;
    return NULL;
}