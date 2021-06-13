/*
Function Set
By Ciaran Gruber

The Function Set is used to provide the details for a set of functions that have the same
name which may be used as a form of overloading

File-specific:
Function Set - Code File
The code used to provide for the implementation of a Function Set
*/

#include <string.h>
#include "function_set.h"

void free_funct_set(function_set_t *src) {
    if (src == NULL) return;

    free(src->name);
    // Free individual functions
    funct_node_t *next, *curr = src->first;
    while (curr != NULL) {
        next = curr->next;
        free_function(curr->function);
        free(curr);
        curr = next;
    }
    free(src);
}

inst_error_t *new_funct_set(prog_hand_t *prog_handler, function_set_t *dest, char *name) {
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

inst_error_t *funct_set_add(prog_hand_t *prog_handler, function_set_t *self, function_t *function) {
    inst_error_t *error;
    if (self == NULL || function == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Return an error if the function name is not the same as the function set name
    if (strcmp(self->name, function->name)) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Attempt to find existing function that match the parameters
    funct_node_t *prev;
    bool is_found;
    error = f_set_function_exists(prog_handler, &is_found, self, &prev, function->param_types, 
                                function->param_count);
    if (error != NULL) return error;
    if (is_found) {
        return new_error(prog_handler, "ErrFunctionAlreadyExists");
    }

    // Add function
    funct_node_t *function_node = (funct_node_t *)malloc(sizeof(funct_node_t));
    function_node->function = function;
    function_node->next = NULL;
    if (self->first == NULL) {
        self->first = function_node;
    }
    prev->next = function_node;

    return NULL;
}

inst_error_t *funct_set_remove(prog_hand_t *prog_handler, function_set_t *self, 
        class_t **param_types, int param_count) {
    inst_error_t *error;
    if (self == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Find the function
    funct_node_t *prev, *curr;
    bool is_found;
    error = f_set_function_exists(prog_handler, &is_found, self, &prev, param_types, 
                                param_count);
    if (error != NULL) return error;
    if (!is_found) {
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
        free_function(curr->function);
        free(curr);
    }

    return NULL;
}

inst_error_t *function_set_run(prog_hand_t *prog_handler, function_set_t *self, var_t *inst_var,
        var_t *return_var, var_t **params, int param_count) {
    inst_error_t *error;
    if (self == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Convert parameters to parameter types
    funct_node_t *node;
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
    bool is_found;
    error = f_set_function_exists(prog_handler, &is_found, self, &node, param_types, 
                                param_count);
    if (error != NULL) return error;

    if (!is_found) {
        return new_error(prog_handler, "ErrFunctionNotDefined");
    }
    if (node == NULL) {
        node = self->first;
    } else {
        node = node->next;
    }

    // Run the function
    error = function_run(prog_handler, node->function, inst_var, return_var, params, param_count);
    return error;
}

inst_error_t *funct_set_get_return(prog_hand_t *prog_handler, function_set_t *self, 
        class_t **return_type, class_t **param_types, int param_count) {
    inst_error_t *error;
    if (self == NULL || return_type == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Attempt to find function
    funct_node_t *node;
    bool is_found;
    error = f_set_function_exists(prog_handler, &is_found, self, &node, param_types, 
                                param_count);
    if (error != NULL) return error;

    if (!is_found) {
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

inst_error_t *f_set_function_exists(prog_hand_t *prog_handler, bool *result, function_set_t *self, 
        funct_node_t **prev_node, class_t **param_types, int param_count) {
    inst_error_t *error;
    if (result == NULL || self == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    funct_node_t *curr = self->first;
    *prev_node = NULL;
    while(curr != NULL) {
        function_t *func = curr->function;
        is_function_equal(prog_handler, result, func, param_types, param_count);
        if (*result) {
            return NULL;
        }

        if (prev_node != NULL) *prev_node = curr;
        curr = curr->next;
    }
    *result = false;
    return NULL;
}