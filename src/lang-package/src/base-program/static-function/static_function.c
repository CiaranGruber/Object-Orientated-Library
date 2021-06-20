/*
Static Function
By Ciaran Gruber

The Static Function is a function that is called by classes and does not directly modify a
variable's data in a way similar to the Static Function

File-specific:
Static Function - Code File
The code used to provide for the implementation of a Static Function
*/

#include <string.h>
#include "static_function.h"
#include "../../program-handlers/error-handler/error_handler.h"

void free_s_function(s_function_t *src) {
    if (src == NULL) return;

    free(src->name);
    free(src->param_types);
    free(src);
}

inst_error_t *new_s_function(prog_hand_t *prog_handler, s_function_t *dest, char *name, 
        inst_error_t *(*function)(prog_hand_t *, var_t *,var_t **), class_t *return_type, 
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

inst_error_t *s_function_run(prog_hand_t *prog_handler, s_function_t *self, var_t *return_val,
        var_t **params, int param_count) {
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
        while (curr_class != NULL || !curr_class->uses_inst_var_handler) {
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
    // Run function and handle any errors
    error = self->function(prog_handler, return_val, params);
    return error;
}

inst_error_t *is_s_function_equal(prog_hand_t *prog_handler, bool *result, s_function_t *self,
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
        while (curr_class != NULL || !curr_class->uses_inst_var_handler) {
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