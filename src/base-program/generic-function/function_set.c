/*
Generic Function Set
By Ciaran Gruber

The Generic Function Set is used to provide the details for a set of functions that have the same
name which may be used as a form of overloading

File-specific:
Function Set - Code File
The code used to provide for the implementation of a Generic Function Set
*/

#include <string.h>
#include "function_set.h"

void free_funct_set(function_set_t *src) {
    free(src->name);
    // Free functions
    funct_node_t *next, *curr = src->first;
    while (curr != NULL) {
        next = curr->next;
        free_function(curr->function);
        free(curr);
        curr = next;
    }
    free(src);
}

inst_error_t *funct_set_create(prog_hand_t *prog_handler, function_set_t *dest, char *name) {
    inst_error_t *error = (inst_error_t *)malloc(sizeof(inst_error_t));

    dest->name = (char *)malloc(strlen(name)*sizeof(char));
    if (dest->name == NULL) {
        new_instance(prog_handler, "ErrOutOfMemory", error, NULL, 0);
        handle_err(prog_handler, error);
        return error;
    }
    strcpy(dest->name, name);

    free(error);
    return NULL;
}

inst_error_t *funct_set_add(prog_hand_t *prog_handler, function_set_t *self, function_t *function) {
    inst_error_t *error = (inst_error_t *)malloc(sizeof(inst_error_t));

    if (strcmp(self->name, function->name)) {
        new_instance(prog_handler, "ErrInvalidParameters", error, NULL, 0);
        handle_err(prog_handler, error);
        return error;
    }
    funct_node_t *check_func, *prev;
    __find_function(self, check_func, prev, function->param_types, function->param_count);
    if (check_func != NULL) {
        new_instance(prog_handler, "ErrFunctionAlreadyExists", error, NULL, 0);
        handle_err(prog_handler, error);
        return error;
    }
    funct_node_t *function_node;
    function_node->function = function;
    function_node->next = NULL;
    if (self->first == NULL) {
        self->first = function_node;
    }
    prev->next = function_node;

    free(error);
    return NULL;
}

inst_error_t *funct_set_remove(prog_hand_t *prog_handler, function_set_t *self, 
        class_t **param_types, int param_count) {
    inst_error_t *error = (inst_error_t *)malloc(sizeof(inst_error_t));

    funct_node_t *func, *prev;
    __find_function(self, func, prev, param_types, param_count);
    if (func == NULL) {
        new_instance(prog_handler, "ErrFunctionNotDefined", error, NULL, 0);
        handle_err(prog_handler, error);
        return error;
    }

    if (func != NULL) {
        if (self->first) { // Function is first
            self->first = func->next;
        } else { // Function is in the middle
            prev->next = func->next;
        }
        free_function(func->function);
        free(func);
    }

    free(error);
    return NULL;
}

inst_error_t *function_set_run(prog_hand_t *prog_handler, function_set_t *self,
        var_t *return_val, var_t **params, int param_count) {
    inst_error_t *error = (inst_error_t *)malloc(sizeof(inst_error_t));
    funct_node_t *function;
    __find_function(self, function, NULL, params, param_count);
    if (function == NULL) {
        new_instance(prog_handler, "ErrFunctionNotDefined", error, NULL, 0);
        handle_err(prog_handler, error);
        return error;
    }
    free(error);
    error = function_run(function, prog_handler, return_val, params, param_count);
    handle_err(prog_handler, error);
    return error;
}

void __find_function(function_set_t *self, funct_node_t *dest, funct_node_t *prev, class_t **param_types, int param_count) {
    funct_node_t *curr = self->first;
    while (curr != NULL) {
        function_t *func = curr->function;
        // Ignore function if parameter count is not the same
        if (func->param_count == param_count) {
            // Loop through parameters and check
            for (int i = 0; i < param_count; i++) {
                // If any parameter is not the same, break
                if (func->param_types[i] != param_types[i]) {
                    break;
                }
                // If it reaches last type, then param types are the same
                if (i = param_count - 1) {
                    dest = curr;
                    return;
                }
            }
        }
        if (prev != NULL) prev = curr;
        curr = curr->next;
    }
    return NULL;
}