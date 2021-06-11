/*
Generic Class Code
By Ciaran Gruber

The generic variable code that contains the actual code used for the generic variable type
*/

#include <string.h>
#include "class.h"

void free_class(class_t *src) {
    free(src->class_name);
    for (int i = 0; i < src->class_var_count; i++) {
        free_var(src->class_vars[i]);
    }
    free_funct_hand(src->funct_handler);
    free(src);
}

inst_error_t *new_class(prog_hand_t *prog_handler, class_t *dest, char *class_name, size_t size, 
        class_t *parent, funct_hand_t *funct_handler, var_t **class_vars, int class_var_count) {
    inst_error_t *error = (inst_error_t *)malloc(sizeof(inst_error_t));

    // Check params
    if (class_name == NULL || dest == NULL) {
        new_instance(prog_handler, "ErrInvalidParameters", error, NULL, 0);
        handle_err(prog_handler, error);
        return error;
    }

    dest->parent = parent;
    if (funct_handler == NULL) {
        funct_hand_t *new_handler = (funct_hand_t *)malloc(sizeof(funct_hand_t));
        dest->funct_handler = new_handler;
    } else {
        dest->funct_handler = funct_handler;
    }
    dest->class_vars = class_vars;
    dest->class_var_count = class_var_count;

    free(error);
    return NULL;
}

inst_error_t *new_instance(prog_hand_t *prog_handler, char *class_name, var_t *dest, var_t **params, 
                            int param_count) {
    inst_error_t *error;

    class_t *class;
    // Get class for variable
    error = get_class(prog_handler, class, class_name);
    handle_err(prog_handler, error);
    if (error != NULL) return error;
    // Run constructor
    error = run_function(prog_handler, class->funct_handler, class_name, dest, params, param_count);
    return error;
}