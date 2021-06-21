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

static void __get_prev_node(prog_hand_t *prog_handler, s_function_set_t *self, bool *funct_exists,
        s_funct_node_t **prev_node, class_t **param_types, int param_count);

static void __get_node(prog_hand_t *prog_handler, s_function_set_t *self, s_funct_node_t **node,
        class_t **param_types, int param_count);

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

inst_error_t *sfset_add_function(prog_hand_t *prog_handler, s_function_set_t *self, s_function_t *function) {
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
    bool is_found;
    error = sfset_function_exists(prog_handler, self, &is_found, function->param_types,
                                    function->param_count);
    if (error != NULL) return error;
    if (is_found) {
        return new_error(prog_handler, "ErrFunctionAlreadyExists");
    }

    // Add function to start
    s_funct_node_t *function_node = (s_funct_node_t *)malloc(sizeof(s_funct_node_t));
    function_node->function = function;
    function_node->next = self->first;
    self->first = function_node;

    return NULL;
}

inst_error_t *sfset_remove(prog_hand_t *prog_handler, s_function_set_t *self, 
        class_t **param_types, int param_count) {
    inst_error_t *error;
    if (self == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Attempt to get the function
    s_funct_node_t *prev, *curr;
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
        free_s_function(curr->function);
        free(curr);
    }

    return NULL;
}

inst_error_t *sfset_get_function(prog_hand_t *prog_handler, s_function_set_t *self, s_function_t **dest,
        class_t **param_types, int param_count) {
    inst_error_t *error;
    if (self == NULL || dest == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Attempt to get function node
    s_funct_node_t *node;
    __get_node(prog_handler, self, &node, param_types, param_count);
    if (node == NULL) {
        return new_error(prog_handler, "ErrFunctionNotDefined");
    }

    // Set Function
    *dest = node->function;
    return NULL;
}

inst_error_t *sfset_function_exists(prog_hand_t *prog_handler, s_function_set_t *self, bool *result,
        class_t **param_types, int param_count) {
    inst_error_t *error;
    if (result == NULL || self == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    __get_prev_node(prog_handler, self, result, NULL, param_types, param_count);
    return NULL;
}

static void __get_prev_node(prog_hand_t *prog_handler, s_function_set_t *self, bool *funct_exists,
        s_funct_node_t **prev_node, class_t **param_types, int param_count) {
    s_funct_node_t *curr = self->first;
    *prev_node = NULL;
    // Loop through available functions
    while(curr != NULL) {
        // Check if the function in the node is equal - If it exists leave prev_node as is
        is_s_function_equal(prog_handler, funct_exists, curr->function, param_types, param_count);
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

static void __get_node(prog_hand_t *prog_handler, s_function_set_t *self, s_funct_node_t **node,
        class_t **param_types, int param_count) {
    bool function_exists;
    s_funct_node_t *prev_node;
    __get_prev_node(prog_handler, self, &function_exists, &prev_node, param_types, param_count);
    if (function_exists) {
        *node = prev_node != NULL ? prev_node->next : self->first;
    } else {
        *node = NULL;
    }
}