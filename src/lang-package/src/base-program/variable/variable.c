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
#include "../../program-handlers/class-handler/class_handler.h"
#include "../../program-handlers/error-handler/error_handler.h"
#include "../../program-handlers/function-handler/function_handler.h"
#include "../../program-handlers/variable-handler/variable_handler.h"
#include "../../types/Object/t_Object.h"
#include "var_description.h"
#include "../function/function.h"
#include "../class/class.h"

static inst_error_t *__get_function(prog_hand_t *prog_handler, function_t **dest, class_t *self,
        char *funct_name, class_t **param_types, int param_count);
static inst_error_t *__convert_super(prog_hand_t *prog_handler, class_t *self,
        class_t **super_class, int parent_levels);

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
    // Reset values if necessary
    if (dest->initialised) {
        if (strcmp(dest->desc->type->class_name, type)) {
            error = run_function(prog_handler, dest, "free_data", NULL, NULL, 0);
            if (error != NULL) return error;
        }
    }
    error = init_var_desc(prog_handler, dest->desc, type, name);
    return error;
}

inst_error_t *init_var_exact(prog_hand_t *prog_handler, var_t *dest, void *data) {
    inst_error_t *error;
    if (dest == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }
    if (dest->desc->type->has_managed_data) {
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

    // Convert parameter types
    class_t **param_types = (class_t **)malloc(param_count*sizeof(class_t *));
    for (int i = 0; i < param_count; i++) {
        param_types[i] = params[i]->desc->type;
    }

    function_t *function;
    error = __get_function(prog_handler, &function, self->desc->type, funct_name, param_types,
                            param_count);
    if (error != NULL) return error;
    error = function_run(prog_handler, function, self, return_var, params, param_count);
    return error;
}

inst_error_t *run_super_function(prog_hand_t *prog_handler, var_t *self, char *funct_name,
        var_t *return_var, var_t **params, int param_count, int parent_levels) {
    inst_error_t *error;
    if (self == NULL || funct_name == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Convert parameter types
    class_t **param_types = (class_t **)malloc(param_count*sizeof(class_t *));
    for (int i = 0; i < param_count; i++) {
        param_types[i] = params[i]->desc->type;
    }

    function_t *function;
    class_t *var_class = self->desc->type;
    error = __convert_super(prog_handler, var_class, &var_class, parent_levels);
    if (error != NULL) return error;
    error = __get_function(prog_handler, &function, var_class, funct_name, param_types,
                            param_count);
    if (error != NULL) return error;
    error = function_run(prog_handler, function, self, return_var, params, param_count);
    return error;
}

inst_error_t *get_member_field(prog_hand_t *prog_handler, var_t *self, var_t **dest, 
        char *field_name) {
    inst_error_t *error;
    if (self == NULL || dest == NULL || field_name == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Produce error if variable's data is not managed with a Variable Handler
    if (!self->desc->type->has_managed_data) {
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
    if (!self->desc->type->has_managed_data) {
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

static inst_error_t *__convert_super(prog_hand_t *prog_handler, class_t *self,
        class_t **super_class, int parent_levels) {
    inst_error_t *error;

    // Loop through parent classes
    for (int i = 0; i < parent_levels; i++) {
        if (!self->has_managed_data) {
            return new_error(prog_handler, "ErrInvalidDataFormat");
        }
        get_parent(prog_handler, self, &self);
    }
    if (!self->has_managed_data && parent_levels > 0) {
        return new_error(prog_handler, "ErrInvalidDataFormat");
    }
    // Convert to parent class
    *super_class = self;
    return NULL;
}

static inst_error_t *__get_function(prog_hand_t *prog_handler, function_t **dest, class_t *self,
        char *funct_name, class_t **param_types, int param_count) {
    inst_error_t *error;

    // Loop through parent classes until a suitable function is found
    while (self != NULL) {
        // Attempt to get function
        add_err(prog_handler, "ErrFunctionNotDefined");
        error = fhand_get_function(prog_handler, self->inst_methods, dest, funct_name, param_types,
                                    param_count);

        if (!err_is_equal(error, "ErrFunctionNotDefined")) { // Function was found
            remove_err(prog_handler, "ErrFunctionNotDefined");
            return error;
        }

        get_parent(prog_handler, self, &self);
        // Function can not be run if a parent does not have managed data
        if (!self->has_managed_data) {
            break;
        }
    }
    // Attempt to get function from object class
    if (self != NULL) {
        // Get class
        cls_object_t *class;
        error = get_class(prog_handler, &class, OBJECT_CLS_NAME);
        if (error != NULL) return error;
        // Get function and return any errors
        return fhand_get_function(prog_handler, self->inst_methods, dest, funct_name, param_types,
                                    param_count);
    }
    // Return ErrFunctionNotDefined
    return new_error(prog_handler, "ErrFunctionNotDefined");
}