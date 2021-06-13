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
#include "../../types/Object/t_Object.h"

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

    // Run constructor for specific class
    class_t *class = dest->desc->type;
    cls_error_t *undef_func_cls;
    get_class(prog_handler, &undef_func_cls, "ErrFunctionNotDefined");
    error = add_err(prog_handler, undef_func_cls);
    if (error != NULL) return error;
    error = run_function(prog_handler, dest, class->class_name, dest, params, param_count);
    // Check error
    if (error == NULL || error->desc->type != undef_func_cls) {
        remove_err(prog_handler, undef_func_cls);
        return error;
    }

    // Mark as initialised
    dest->initialised = true;
    return NULL;
}

inst_error_t *run_s_function(prog_hand_t *prog_handler, class_t *self, char *funct_name, 
        var_t *return_var, var_t **params, int param_count) {
    inst_error_t *error;
    if (self == NULL || funct_name == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    cls_error_t *function_not_defined;
    get_class(prog_handler, &function_not_defined, "ErrFunctionNotDefined");
    error = add_err(prog_handler, function_not_defined);
    if (error != NULL) return error;
    // Loop through parent classes until a suitable function is found
    while (self != NULL) {
        // Remove FunctionNotDefined error handling if it is the final class
        if (self->parent == NULL) {
            remove_err(prog_handler, function_not_defined);
        }

        // Attempt to run function
        error = s_funct_hand_run(prog_handler, self->static_methods, funct_name, return_var, params,
                                param_count);
        // Continue serarching for functions in parent classes if function is not defined
        if (error != NULL && error->desc->type != function_not_defined) {
            return error;
        }

        self = self->parent;
    }
    // Error will be ErrFunctionNotDefined if the function could not be found
    return error;
}

inst_error_t *get_s_return_type(prog_hand_t *prog_handler, class_t *self, char *funct_name,
        class_t **return_type, class_t **param_types, int param_count) {
    inst_error_t *error;
    if (self == NULL || funct_name == NULL || return_type == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    cls_error_t *function_not_defined;
    get_class(prog_handler, &function_not_defined, "ErrFunctionNotDefined");
    // Loop through parent classes until a suitable function is found
    while (self != NULL) {
        // Remove FunctionNotDefined error handling if it is the final class
        if (self->parent == NULL) {
            remove_err(prog_handler, function_not_defined);
        }

        // Attempt to get function type
        error = add_err(prog_handler, function_not_defined);
        if (error != NULL) return error;
        error = s_function_get_return(prog_handler, self->static_methods, funct_name, return_type, 
                                        param_types, param_count);
        // Continue serarching for functions in parent classes if function is not defined
        if (error != NULL && error->desc->type != function_not_defined) {
            return error;
        }

        self = self->parent;
    }
    // Error will be ErrFunctionNotDefined if the function could not be found
    return error;
}

inst_error_t *get_return_type(prog_hand_t *prog_handler, class_t *self, char *funct_name,
        class_t **return_type, class_t **param_types, int param_count) {
    inst_error_t *error;
    if (self == NULL || funct_name == NULL || return_type == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    cls_error_t *function_not_defined;
    get_class(prog_handler, &function_not_defined, "ErrFunctionNotDefined");
    // Loop through parent classes until a suitable function is found
    while (self != NULL) {
        // Remove FunctionNotDefined error handling if it is the final class
        if (self->parent == NULL) {
            remove_err(prog_handler, function_not_defined);
        }

        // Attempt to get function type
        error = add_err(prog_handler, function_not_defined);
        if (error != NULL) return error;
        error = function_get_return(prog_handler, self->inst_methods, funct_name, return_type, 
                                        param_types, param_count);
        // Continue serarching for functions in parent classes if function is not defined
        if (error != NULL && error->desc->type != function_not_defined) {
            return error;
        }

        self = self->parent;
    }
    // Error will be ErrFunctionNotDefined if the function could not be found
    return error;
}