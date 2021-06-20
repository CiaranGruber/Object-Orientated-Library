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
#include "../../program-handlers/error-handler/error_handler.h"
#include "../../program-handlers/function-handler/function_handler.h"
#include "../../program-handlers/variable-handler/variable_handler.h"
#include "var_description.h"

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

inst_error_t *set_var_desc(prog_hand_t *prog_handler, var_t *dest, char *type, char *name) {
    inst_error_t *error;
    error = init_var_desc(prog_handler, dest->desc, type, name);
    return error;
}

inst_error_t *init_var_exact(prog_hand_t *prog_handler, var_t *dest, void *data) {
    inst_error_t *error;
    if (dest == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }
    if (dest->desc->type->uses_inst_var_handler) {
        return new_error(prog_handler, "ErrInvalidDataFormat");
    }

    // Copy data
    dest->data = (void *)malloc(dest->desc->type->size);
    if (dest->data == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }
    // If given data is NULL, leave data blank
    if (data != NULL) {
        memcpy(dest->data, data, dest->desc->type->size);
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
    // Loop through parent classes until a suitable function is found
    while (curr_class != NULL) {
        // Attempt to run function
        error = add_err(prog_handler, "ErrFunctionNotDefined");
        if (error != NULL) return error;
        error = funct_hand_run(prog_handler, curr_class->inst_methods, funct_name, self, return_var,
                                params, param_count);
        // Function was run successfully and will return NULL or other error occurred and will 
        // return the error that occurred
        if (strcmp(error->desc->type->class_name, "ErrFunctionNotDefined")) {
            remove_err(prog_handler, "ErrFunctionNotDefined");
            return error;
        }

        curr_class = curr_class->parent;
    }
    // Return ErrFunctionNotDefined
    return new_error(prog_handler, "ErrFunctionNotDefined");
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

inst_error_t *get_type(prog_hand_t *prog_handler, var_t *self, class_t **dest) {
    inst_error_t *error;
    if (self == NULL || dest == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    *dest = self->desc->type;
    return NULL;
}

inst_error_t *get_var_name(prog_hand_t *prog_handler, var_t *self, char **dest) {
    inst_error_t *error;
    if (self == NULL || dest == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    *dest = (char *)malloc(strlen(self->desc->name)*sizeof(char));
    if (*dest == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }
    strcpy(*dest, self->desc->name);

    return NULL;
}