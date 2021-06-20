/*
Static Function Set
By Ciaran Gruber

The Static Function Set is used to provide the details for a set of functions that have the same
name which may be used as a form of overloading

File-specific:
Static Function Set - Code File
The code used to provide for the implementation of a Static Function Set
*/

#include <string.h>
#include "static_function_set.h"
#include "static_function.h"
#include "../../program-handlers/error-handler/error_handler.h"

void free_s_funct_set(s_function_set_t *src) {
    if (src == NULL) return;

    free(src->name);
    // Free individual functions
    s_funct_node_t *next, *curr = src->first;
    while (curr != NULL) {
        next = curr->next;
        free_s_function(curr->function);
        free(curr);
        curr = next;
    }
    free(src);
}

inst_error_t *new_s_funct_set(prog_hand_t *prog_handler, s_function_set_t *dest, char *name) {
    inst_error_t *error;
    if (dest == NULL || name == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    dest->first = NULL;
    // Copy name of function set
    dest->name = (char *)malloc(strlen(name)*sizeof(char));
    if (dest->name == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }
    strcpy(dest->name, name);

    return NULL;
}

inst_error_t *s_funct_set_add(prog_hand_t *prog_handler, s_function_set_t *self, s_function_t *function) {
    inst_error_t *error;
    if (self == NULL || function == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Return an error if the function name is not the same as the function set name
    if (strcmp(self->name, function->name)) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Attempt to find existing function that match the parameters
    s_funct_node_t *prev;
    bool function_exists;
    error = f_set_s_function_exists(prog_handler, &function_exists, self, &prev, function->param_types, 
                                function->param_count);
    if (error != NULL) return error;
    if (function_exists) {
        return new_error(prog_handler, "ErrFunctionAlreadyExists");
    }

    // Add function
    s_funct_node_t *function_node = (s_funct_node_t *)malloc(sizeof(s_funct_node_t));
    function_node->function = function;
    function_node->next = NULL;
    if (self->first == NULL) {
        self->first = function_node;
    }
    prev->next = function_node;

    return NULL;
}

inst_error_t *s_funct_set_remove(prog_hand_t *prog_handler, s_function_set_t *self, 
        class_t **param_types, int param_count) {
    inst_error_t *error;
    if (self == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Find the function
    s_funct_node_t *prev, *curr;
    bool function_exists;
    error = f_set_s_function_exists(prog_handler, &function_exists, self, &prev, param_types, 
                                param_count);
    if (error != NULL) return error;
    if (!function_exists) {
        return new_error(prog_handler, "ErrFunctionNotDefined");
    }
    if (prev == NULL) {
        curr = self->first;
    } else {
        curr = prev->next;
    }

    // Remove the function and free memory
    if (curr->function != NULL) {
        if (self->first) { // Function is first
            self->first = curr->next;
        } else { // Function is in the middle
            prev->next = curr->next;
        }
        free_s_function(curr->function);
        free(curr);
    }

    return NULL;
}

inst_error_t *s_function_set_run(prog_hand_t *prog_handler, s_function_set_t *self,
        var_t *return_val, var_t **params, int param_count) {
    inst_error_t *error;
    if (self == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Convert parameters to parameter types
    s_funct_node_t *node;
    class_t **param_types;
    if (params == NULL) {
        param_types = (class_t **)malloc(param_count*sizeof(class_t *));
        for (int i = 0; i < param_count; i++) {
            param_types[i] = params[i]->desc->type;
        }
    } else {
        param_types = NULL;
    }
    // Find function
    bool function_exists;
    error = f_set_s_function_exists(prog_handler, &function_exists, self, &node, param_types, 
                                param_count);
    if (error != NULL) return error;

    if (!function_exists) {
        return new_error(prog_handler, "ErrFunctionNotDefined");
    }
    if (node == NULL) {
        node = self->first;
    } else {
        node = node->next;
    }

    // Run the function
    error = s_function_run(prog_handler, node->function, return_val, params, param_count);
    return error;
}

inst_error_t *s_funct_set_get_return(prog_hand_t *prog_handler, s_function_set_t *self, 
        class_t **return_type, class_t **param_types, int param_count) {
    inst_error_t *error;
    if (self == NULL || return_type == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Attempt to find function
    s_funct_node_t *node;
    bool function_exists;
    error = f_set_s_function_exists(prog_handler, &function_exists, self, &node, param_types, 
                                param_count);
    if (error != NULL) return error;

    if (!function_exists) {
        return new_error(prog_handler, "ErrFunctionNotDefined");
    }
    if (node == NULL) {
        node = self->first;
    } else {
        node = node->next;
    }

    // Set the return type
    *return_type = node->function->return_type;
    return NULL;
}

inst_error_t *f_set_s_function_exists(prog_hand_t *prog_handler, bool *result, s_function_set_t *self, 
        s_funct_node_t **prev_node, class_t **param_types, int param_count) {
    inst_error_t *error;
    if (result == NULL || self == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    s_funct_node_t *curr = self->first;
    *prev_node = NULL;
    while(curr != NULL) {
        s_function_t *func = curr->function;
        is_s_function_equal(prog_handler, result, func, param_types, param_count);
        if (*result) {
            return NULL;
        }

        if (prev_node != NULL) *prev_node = curr;
        curr = curr->next;
    }
    *result = false;
    return NULL;
}