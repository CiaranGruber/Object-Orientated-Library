/*
Generic Variable Code
By Ciaran Gruber

The generic variable code that contains the actual code used for the generic variable type
*/

#include <string.h>
#include "variable.h"

void free_var(var_t *src) {
    free(src->data);
    free(src);
}

inst_error_t *new_var_exact(prog_hand_t *prog_handler, var_t *dest, char *type, void *data) {
    inst_error_t *error;

    // Get class
    error = get_class(prog_handler, dest->type, type);
    handle_err(prog_handler, error);
    if (error != NULL) return error;

    // Copy data
    dest->data = (void *)malloc(dest->type->size);
    if (dest->data == NULL) {
        error = (inst_error_t *)malloc(sizeof(inst_error_t));
        new_instance(prog_handler, error, "ErrOutOfMemory", NULL, 0);
        handle_err(prog_handler, error);
        return error;
    }
    memcpy(dest->data, data, dest->type->size);

    return NULL;
}

inst_error_t *var_run_func(prog_hand_t *prog_handler, var_t *self, char *funct_name, 
        var_t *return_var, var_t **params, int param_count) {
    inst_error_t *error;

    funct_hand_t *function_handler = self->type->funct_handler;
    error = run_function(prog_handler, function_handler, funct_name, return_var, params, param_count);
    handle_err(prog_handler, error);
    return error;
}