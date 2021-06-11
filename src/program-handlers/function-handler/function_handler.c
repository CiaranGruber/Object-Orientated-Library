/*
Function Handler
By Ciaran Gruber

The Function Handler is used to handle the functions within a class

File-specific:
Error Handler - Code File
The code used to provide for the implementation of a Function Handler
*/

#include <string.h>
#include "function_handler.h"

void free_funct_hand(funct_hand_t *src) {
    funct_set_node_t *temp, *curr = src->first;
    while (curr != NULL) {
        free_funct_set(curr->function_set);
        temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(src);
}

inst_error_t *add_function(prog_hand_t *prog_handler, funct_hand_t *self, function_t *function) {
    inst_error_t *error;
    funct_set_node_t *prev, *curr = self->first;
    while (curr != NULL) {
        int comparison = strcmp(function->name, curr->function_set->name);
        if (comparison < 0) { // Function set doesn't exist
            funct_set_node_t *new_node;
            // Create function set
            error = funct_set_create(prog_handler, new_node->function_set, function->name);
            handle_err(prog_handler, error);
            if (error != NULL) return error;
            // Add function to function set
            error = funct_set_add(prog_handler, new_node->function_set, function);
            handle_err(prog_handler, error);
            if (error != NULL) return error;

            if (prev == NULL) { // Function set is first
                // Add function set to handler
                new_node->next = self->first;
                self->first = new_node;
                return NULL;
            }
            prev->next = new_node;
            new_node->next = curr;
            return NULL;
        } else if (!comparison) { // Function set is the same
            // Add function to function set
            error = funct_set_add(prog_handler, curr->function_set, function);
            handle_err(prog_handler, error);
            return error;
        }
        prev = curr;
        curr = curr->next;
    }
    // Function set does not exist and it reached the end
    funct_set_node_t *new_node;
    // Create function set
    error = funct_set_create(prog_handler, new_node->function_set, function->name);
    handle_err(prog_handler, error);
    if (error != NULL) return error;
    // Add function to function set
    error = funct_set_add(prog_handler, new_node->function_set, function);
    handle_err(prog_handler, error);
    if (error != NULL) return error;
    // Add function set and return no errors
    prev->next = new_node;
    return NULL;
}

inst_error_t *remove_function(prog_hand_t *prog_handler, funct_hand_t *self, function_t *function) {
    remove_function_by_name(prog_handler, self, function->name, function->param_types, 
    function->param_count);
}

inst_error_t *remove_function_by_name(prog_hand_t *prog_handler, funct_hand_t *self, char *name, 
        class_t **param_types, int param_count) {
    inst_error_t *error = (inst_error_t *)malloc(sizeof(inst_error_t));
    
    funct_set_node_t *curr = self->first;
    while (curr != NULL) {
        int comparison = strcmp(name, curr->function_set->name);
        if (!comparison) {
            free(error);
            error = funct_set_remove(prog_handler, curr->function_set, param_types, param_count);
            handle_err(prog_handler, error);
            return error;
        }
    }
    new_instance(prog_handler, "ErrFunctionNotDefined", error, NULL, 0);
    handle_err(prog_handler, error);
    return error;
}

inst_error_t *run_function(prog_hand_t *prog_handler, funct_hand_t *self, char *name, 
        var_t *return_var, var_t **params, int param_count) {
    inst_error_t *error = (inst_error_t *)malloc(sizeof(inst_error_t));

    funct_set_node_t *curr = self->first;
    while (curr != NULL) {
        int comparison = strcmp(name, curr->function_set->name);
        if (!comparison) {
            free(error);
            error = function_set_run(prog_handler, curr->function_set, return_var, params, param_count);
            handle_err(prog_handler, error);
            return error;
        }
    }
    new_instance(prog_handler, "ErrFunctionNotDefined", error, NULL, 0);
    handle_err(prog_handler, error);
    return error;
}