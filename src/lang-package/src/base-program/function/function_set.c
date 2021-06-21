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
#include "function.h"
#include "../../program-handlers/error-handler/error_handler.h"

static void __get_prev_node(prog_hand_t *prog_handler, function_set_t *self, bool *funct_exists,
        funct_node_t **prev_node, class_t **param_types, int param_count);

static void __get_node(prog_hand_t *prog_handler, function_set_t *self, funct_node_t **node,
        class_t **param_types, int param_count);

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

inst_error_t *fset_add_function(prog_hand_t *prog_handler, function_set_t *self, function_t *function) {
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
    error = fset_function_exists(prog_handler, self, &is_found, function->param_types,
                                    function->param_count);
    if (error != NULL) return error;
    if (is_found) {
        return new_error(prog_handler, "ErrFunctionAlreadyExists");
    }

    // Add function to start
    funct_node_t *function_node = (funct_node_t *)malloc(sizeof(funct_node_t));
    function_node->function = function;
    function_node->next = self->first;
    self->first = function_node;

    return NULL;
}

inst_error_t *fset_remove(prog_hand_t *prog_handler, function_set_t *self, 
        class_t **param_types, int param_count) {
    inst_error_t *error;
    if (self == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Attempt to get the function
    funct_node_t *prev, *curr;
    bool funct_exists;
    __get_prev_node(prog_handler, self, &funct_exists, &prev, param_types, param_count);
    if (!funct_exists) {
        return new_error(prog_handler, "ErrFunctionNotDefined");
    }
    // Set current node
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

inst_error_t *fset_get_function(prog_hand_t *prog_handler, function_set_t *self, function_t **dest,
        class_t **param_types, int param_count) {
    inst_error_t *error;
    if (self == NULL || dest == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Attempt to get function node
    funct_node_t *node;
    __get_node(prog_handler, self, &node, param_types, param_count);
    if (node == NULL) {
        return new_error(prog_handler, "ErrFunctionNotDefined");
    }

    // Set Function
    *dest = node->function;
    return NULL;
}

inst_error_t *fset_function_exists(prog_hand_t *prog_handler, function_set_t *self, bool *result,
        class_t **param_types, int param_count) {
    inst_error_t *error;
    if (result == NULL || self == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    __get_prev_node(prog_handler, self, result, NULL, param_types, param_count);
    return NULL;
}

static void __get_prev_node(prog_hand_t *prog_handler, function_set_t *self, bool *funct_exists,
        funct_node_t **prev_node, class_t **param_types, int param_count) {
    funct_node_t *curr = self->first;
    *prev_node = NULL;
    // Loop through available functions
    while(curr != NULL) {
        // Check if the function in the node is equal - If it exists leave prev_node as is
        is_function_equal(prog_handler, funct_exists, curr->function, param_types, param_count);
        if (*funct_exists) {
            return;
        }

        // Iterate through nodes
        if (prev_node != NULL) *prev_node = curr;
        curr = curr->next;
    }
    // Relevant if there are no functions in the function set
    *funct_exists = false;
}

static void __get_node(prog_hand_t *prog_handler, function_set_t *self, funct_node_t **node,
        class_t **param_types, int param_count) {
    bool function_exists;
    funct_node_t *prev_node;
    __get_prev_node(prog_handler, self, &function_exists, &prev_node, param_types, param_count);
    if (function_exists) {
        *node = prev_node != NULL ? prev_node->next : self->first;
    } else {
        *node = NULL;
    }
}