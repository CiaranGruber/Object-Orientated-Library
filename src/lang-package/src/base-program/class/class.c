/*
Class
By Ciaran Gruber

A Class provides a the type information for variables, containing the methods as well as the member
fields used within a Variable

File-specific:
Class - Code File
The code used to provide for the implementation of a Class
*/

#include <string.h>
#include "class.h"
#include "../variable/variable.h"
#include "../static-function/static_function.h"
#include "../../program-handlers/class-handler/class_handler.h"
#include "../../program-handlers/error-handler/error_handler.h"
#include "../../program-handlers/function-handler/function_handler.h"
#include "../../program-handlers/static-function-handler/static_function_handler.h"
#include "../../program-handlers/variable-handler/variable_handler.h"
#include "../../program-handlers/variable-description-handler/var_desc_handler.h"
#include "../../types/Object/t_Object.h"

static inst_error_t *__get_s_function(prog_hand_t *prog_handler, s_function_t **dest, class_t *self,
        char *funct_name, class_t **param_types, int param_count);
static inst_error_t *__get_function(prog_hand_t *prog_handler, function_t **dest, class_t *self,
        char *funct_name, class_t **param_types, int param_count);
static inst_error_t *__convert_super(prog_hand_t *prog_handler, class_t *self,
        class_t **super_class, int parent_levels);

void free_class(class_t *src) {
    if (src == NULL) return;

    free(src->class_name);
    free_s_funct_hand(src->static_methods);
    free_funct_hand(src->inst_methods);
    free_var_hand(src->class_vars);
    free_var_desc_hand(src->mem_fields);
    free(src);
}

inst_error_t *init_var(prog_hand_t *prog_handler, var_t *dest, var_t **params, 
        int param_count) {
    inst_error_t *error;
    if (dest == NULL || dest->desc == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Free existing data if source is initialised
    if (dest->initialised = true) {
        free(dest->data);
    }

    // Run object constructor
    error = init_object_inst(prog_handler, dest, NULL, NULL);

    // Run constructor for specific class. If there is no constructor, leave as-is
    class_t *class = dest->desc->type;
    add_err(prog_handler, "ErrFunctionNotDefined");
    error = run_function(prog_handler, dest, class->class_name, dest, params, param_count);
    // Check error
    if (error == NULL || !err_is_equal(error, "ErrFunctionNotDefined")) {
        remove_err(prog_handler, "ErrFunctionNotDefined");
        return error;
    }

    // Mark as initialised
    dest->initialised = true;
    return NULL;
}

inst_error_t *run_super_s_function(prog_hand_t *prog_handler, class_t *self, char *funct_name, 
        var_t *return_var, var_t **params, int param_count, int super_amount) {
    inst_error_t *error;

    class_t *super_class;
    error = __convert_super(prog_handler, self, &super_class, super_amount);
    if (error != NULL) return error;
    error = run_s_function(prog_handler, super_class, funct_name, return_var, params, param_count);
    return error;
}

inst_error_t *run_s_function(prog_hand_t *prog_handler, class_t *self, char *funct_name, 
        var_t *return_var, var_t **params, int param_count) {
    inst_error_t *error;
    if (self == NULL || funct_name == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Get params as class list
    class_t **param_types = (class_t **)malloc(param_count*sizeof(class_t *));
    if (param_types == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }
    for (int i = 0; i < param_count; i++) {
        param_types[i] = params[i]->desc->type;
    }

    // Get function
    s_function_t *function;
    __get_s_function(prog_handler, &function, self, funct_name, param_types, param_count);
    if (function == NULL) {
        return new_error(prog_handler, "ErrFunctionNotDefined");
    }
    // Run function
    error = s_function_run(prog_handler, function, return_var, params, param_count);
    return error;
}

inst_error_t *get_super_return_type(prog_hand_t *prog_handler, class_t *self, char *funct_name,
        class_t **return_type, class_t **param_types, int param_count, int super_amount) {
    inst_error_t *error;

    class_t *super_class;
    error = __convert_super(prog_handler, self, &super_class, super_amount);
    if (error != NULL) return error;
    error = get_return_type(prog_handler, super_class, funct_name, return_type, param_types,
                                param_count);
    return error;
}

inst_error_t *get_return_type(prog_hand_t *prog_handler, class_t *self, char *funct_name,
        class_t **return_type, class_t **param_types, int param_count) {
    inst_error_t *error;
    if (self == NULL || funct_name == NULL || return_type == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Get function
    function_t *function;
    __get_function(prog_handler, &function, self, funct_name, param_types, param_count);
    if (function == NULL) {
        return new_error(prog_handler, "ErrFunctionNotDefined");
    }
    // Set return type
    *return_type = function->return_type;
    return NULL;
}

inst_error_t *get_super_s_return_type(prog_hand_t *prog_handler, class_t *self, char *funct_name,
        class_t **return_type, class_t **param_types, int param_count, int super_amount) {
    inst_error_t *error;

    class_t *super_class;
    error = __convert_super(prog_handler, self, &super_class, super_amount);
    if (error != NULL) return error;
    error = get_s_return_type(prog_handler, super_class, funct_name, return_type, param_types,
                                param_count);
    return error;
}

inst_error_t *get_s_return_type(prog_hand_t *prog_handler, class_t *self, char *funct_name,
        class_t **return_type, class_t **param_types, int param_count) {
    inst_error_t *error;
    if (self == NULL || funct_name == NULL || return_type == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Get function
    s_function_t *function;
    __get_s_function(prog_handler, &function, self, funct_name, param_types, param_count);
    if (function == NULL) {
        return new_error(prog_handler, "ErrFunctionNotDefined");
    }
    // Set return type
    *return_type = function->return_type;
    return NULL;
}

inst_error_t *get_class_var(prog_hand_t *prog_handler, class_t *self, var_t **dest,
        char *var_name) {
    inst_error_t *error;
    if (self == NULL || dest == NULL || var_name == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    error = get_var(prog_handler, self->class_vars, dest, var_name);
    return error;
}

inst_error_t *get_parent(prog_hand_t *prog_handler, class_t *self, class_t **dest) {
    inst_error_t *error;
    if (self == NULL || dest == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    *dest = self->parent;
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

static inst_error_t *__get_s_function(prog_hand_t *prog_handler, s_function_t **dest, class_t *self,
        char *funct_name, class_t **param_types, int param_count) {
    inst_error_t *error;

    // Loop through parent classes until a suitable function is found
    while (self != NULL) {
        // Attempt to get function
        add_err(prog_handler, "ErrFunctionNotDefined");
        error = sfhand_get_function(prog_handler, self->static_methods, dest, funct_name, 
                                    param_types, param_count);

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
        return sfhand_get_function(prog_handler, self->static_methods, dest, funct_name,
                                    param_types, param_count);
    }
    // Return ErrFunctionNotDefined
    return new_error(prog_handler, "ErrFunctionNotDefined");
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