/*
Static Function Handler
By Ciaran Gruber

The Static Function Handler is used to handle the use of various Static Function Sets within a class

File-specific:
Static Function Handler - Code File
The code used to provide for the implementation of a Static Function Handler
*/

#include <string.h>
#include "static_function_handler.h"

void free_s_funct_hand(s_funct_hand_t *src) {
    if (src == NULL) return;

    s_funct_hand_node_t *temp, *curr = src->first;
    while (curr != NULL) {
        free_s_funct_set(curr->function_set);
        temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(src);
}

inst_error_t *s_funct_hand_create(prog_hand_t *prog_handler, s_funct_hand_t *dest) {
    if (dest == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }
    dest->first = NULL;
}

inst_error_t *add_s_function(prog_hand_t *prog_handler, s_funct_hand_t *self, s_function_t *function) {
    inst_error_t *error;
    if (self == NULL || function == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    s_funct_hand_node_t *prev = NULL;
    s_funct_hand_node_t *curr = self->first;
    // Find function
    while (curr != NULL) { // Break if function set doesn't exist
        int comparison = strcmp(function->name, curr->function_set->name);
        if (comparison < 0) { // Function set doesn't exist
            break;
        } else if (!comparison) { // Function set is the same
            // Add function to function set
            error = s_funct_set_add(prog_handler, curr->function_set, function);
            return error;
        }
        prev = curr;
        curr = curr->next;
    }
    // Function set doesn't exist exist
    s_funct_hand_node_t *new_node;
    // Create function set
    error = new_s_funct_set(prog_handler, new_node->function_set, function->name);
    if (error != NULL) return error;
    // Add function to function set
    error = s_funct_set_add(prog_handler, new_node->function_set, function);
    if (error != NULL) return error;

    // Add function set and return no errors
    if (prev == NULL) { // Function set is first
        // Add function set to handler
        new_node->next = self->first;
        self->first = new_node;
        return NULL;
    }
    prev->next = new_node;
    new_node->next = curr;
    return NULL;
}

inst_error_t *remove_s_function(prog_hand_t *prog_handler, s_funct_hand_t *self, s_function_t *function) {
    inst_error_t *error;
    error = remove_s_function_by_name(prog_handler, self, function->name, function->return_type,
                                    function->param_types, function->param_count);
    return error;
}

inst_error_t *remove_s_function_by_name(prog_hand_t *prog_handler, s_funct_hand_t *self, char *name, 
        class_t *return_type, class_t **param_types, int param_count) {
    inst_error_t *error;
    if (self == NULL || name == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }
    
    // Atempt to find function
    s_funct_hand_node_t *prev, *curr;
    bool func_exists;
    s_function_exists(prog_handler, &func_exists, self, name, &prev, param_types, param_count);
    if (!func_exists) {
        return new_error(prog_handler, "ErrFunctionNotDefined");
    }
    if (prev == NULL) {
        curr = self->first;
    } else {
        curr = prev->next;
    }
    
    // Remove function and return any errors
    error = s_funct_set_remove(prog_handler, curr->function_set, param_types, param_count);
    if (error != NULL) return error;

    // Remove function set if that was the last function
    if (curr->function_set->first == NULL) {
        free_s_funct_set(curr->function_set);
        if (prev == NULL) { // No previous function sets
            self->first = curr->next;
        } else {
            prev->next = curr->next;
        }
        free(curr);
    }
    return NULL;
}

inst_error_t *s_funct_hand_run(prog_hand_t *prog_handler, s_funct_hand_t *self, char *name, 
        var_t *return_var, var_t **params, int param_count) {
    inst_error_t *error;
    if (self == NULL || name == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Attempt to find the function
    s_funct_hand_node_t *curr = self->first;
    while (curr != NULL) {
        int comparison = strcmp(name, curr->function_set->name);
        if (!comparison) {
            break;
        }
        curr = curr->next;
    }
    if (curr == NULL) {
        return new_error(prog_handler, "ErrFunctionNotDefined");
    }

    // Run the function and return any errors
    error = s_function_set_run(prog_handler, curr->function_set, return_var, params, param_count);
    return error;
}

inst_error_t *s_function_get_return(prog_hand_t *prog_handler, s_funct_hand_t *self, char *name,
        class_t **return_type, class_t **param_types, int param_count) {
    inst_error_t *error;
    if (self == NULL || name == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Attempt to find the function
    s_funct_hand_node_t *prev, *curr;
    bool func_exists;
    s_function_exists(prog_handler, &func_exists, self, name, &prev, param_types, param_count);
    if (!func_exists) {
        return new_error(prog_handler, "ErrFunctionNotDefined");
    }
    if (prev == NULL) {
        curr = self->first;
    } else {
        curr = prev->next;
    }

    // Get the function type of the function
    error = s_funct_set_get_return(prog_handler, curr->function_set, return_type, param_types,
                                    param_count);
    return error;
}

inst_error_t *s_function_exists(prog_hand_t *prog_handler, bool *result, 
        s_funct_hand_t *self, char *name, s_funct_hand_node_t **prev_node, class_t **param_types,
        int param_count) {
    inst_error_t *error;
    if (result == NULL || self == NULL || name == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Find node
    s_funct_hand_node_t *curr = self->first;
    *prev_node = NULL;
    while (curr != NULL) {
        int comparison = strcmp(name, curr->function_set->name);
        if (!comparison) {
            *result = true;
            return NULL;
        }
        curr = curr->next;
    }

    *result = false;
    return NULL;
}