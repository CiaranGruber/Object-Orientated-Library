/*
Variable
By Ciaran Gruber

The Variable is used to represent a named variable of specific type

File-specific:
Variable - Code File
The code used to provide for the implementation of a Variable
*/

#include <string.h>
#include "variable.h"

// ################### MUST BE ADJUSTED TO INCORPORATE MEMBER FIELDS #######################
void free_var(var_t *src) {
    if (src == NULL) return;

    free(src->data);
    free_var_desc(src->desc);
    free(src);
}

inst_error_t *new_var(prog_hand_t *prog_handler, var_t *dest) {
    if (dest == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    dest->initialised = false;
    dest->data = NULL;
    dest->desc = (var_desc_t *)malloc(sizeof(var_desc_t));
    new_var_desc(prog_handler, dest->desc);
}

inst_error_t *init_var_exact(prog_hand_t *prog_handler, var_t *dest, var_desc_t *var_desc, 
        void *data) {
    inst_error_t *error;
    if (dest == NULL || var_desc == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    dest->desc = var_desc;

    // Copy data
    dest->data = (void *)malloc(var_desc->type->size);
    if (dest->data == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }
    // If given data is NULL, leave data blank
    if (data != NULL) {
        memcpy(dest->data, data, var_desc->type->size);
    }

    dest->initialised = true;
    return NULL;
}

inst_error_t *run_function(prog_hand_t *prog_handler, var_t *self, char *funct_name, 
        var_t *return_var, var_t **params, int param_count) {
    inst_error_t *error;
    if (self == NULL || funct_name == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    class_t *curr_class = self->desc->type;
    cls_error_t *function_not_defined;
    get_class(prog_handler, &function_not_defined, "ErrFunctionNotDefined");
    error = add_err(prog_handler, function_not_defined);
    if (error != NULL) return error;
    // Loop through parent classes until a suitable function is found
    while (curr_class != NULL) {
        // Remove FunctionNotDefined error handling if it is the final class
        if (curr_class->parent == NULL) {
            remove_err(prog_handler, function_not_defined);
        }

        // Attempt to run function
        error = funct_hand_run(prog_handler, curr_class->inst_methods, funct_name, self, return_var,
                                params, param_count);
        // Continue serarching for functions in parent classes if function is not defined
        if (error != NULL && error->desc->type != function_not_defined) {
            return error;
        }

        curr_class = curr_class->parent;
    }
    // Error will be ErrFunctionNotDefined if the function could not be found
    return error;
}

inst_error_t *get_member_field(prog_hand_t *prog_handler, var_t *self, var_t **dest, 
        char *field_name) {
    inst_error_t *error;
    if (self == NULL || dest == NULL || field_name == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Produce error if variable's data is not managed with a Variable Handler
    if (!self->desc->type->uses_inst_var_handler) {
        return new_error(prog_handler, "ErrInvalidDataFormat");
    }
    
    // Get member field
    var_hand_t *var_handler = (var_hand_t *)self->data;
    error = get_var(prog_handler, var_handler, dest, field_name);
    return error;
}

inst_error_t *get_data(prog_hand_t *prog_handler, var_t *self, void **dest) {
    inst_error_t *error;
    if (self == NULL || dest == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Produce error if variable's data is not managed with a Variable Handler
    if (!self->desc->type->uses_inst_var_handler) {
        return new_error(prog_handler, "ErrInvalidDataFormat");
    }

    // Point to new data
    *dest = self->data;

    return NULL;
}