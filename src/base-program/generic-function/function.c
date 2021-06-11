/*
Generic Function
By Ciaran Gruber

The Generic Function is used to provide the implementation for a single function and also provides
error handling

File-specific:
Generic Function - Code File
The code used to provide for the implementation of a Generic Function
*/

#include "function.h"

void free_function(function_t *src) {
    free(src->name);
    free(src->param_types);
    free(src);
}

inst_error_t *function_create(prog_hand_t *prog_handler, function_t *dest, char *name, 
                                inst_error_t *(*function)(var_t *,var_t **), class_t *return_type,
                                class_t **param_types, int param_count) {
    inst_error_t *error = (inst_error_t *)malloc(sizeof(inst_error_t));

    dest->name = (char *)malloc(strlen(name)*sizeof(char));
    if (dest->name == NULL) {
        new_instance(prog_handler, "ErrOutOfMemory", error, NULL, 0);
        handle_err(prog_handler, error);
        return error;
    }
    dest->function = function;
    dest->return_type = return_type;
    dest->param_types = (class_t **)malloc(param_count*sizeof(class_t *));
    if (dest->param_types == NULL) {
        new_instance(prog_handler, "ErrOutOfMemory", error, NULL, 0);
        handle_err(prog_handler, error);
        return error;
    }
    dest->param_count = param_count;

    free(error);
    return NULL;
}

inst_error_t *function_run(prog_hand_t *prog_handler, function_t *self, var_t *return_val, 
                            var_t **variables, int var_count) {
    inst_error_t *error = (inst_error_t *)malloc(sizeof(inst_error_t));

    // Check variable count
    if (self->param_count != var_count) {
        new_instance(prog_handler, "ErrInvalidParameters", error, NULL, 0);
        handle_err(prog_handler, error);
        return error;
    }
    // Check variable types
    for (int i = 0; i < var_count; i++) {
        if (variables[i]->type != self->param_types[i]) {
            new_instance(prog_handler, "ErrInvalidParameters", error, NULL, 0);
            handle_err(prog_handler, error);
            return error;
        }
    }
    // Run function and handle any errors
    free(error);
    error = self->function(return_val, variables);
    handle_err(prog_handler, error);
    return error;
}