/*
Function Handler
By Ciaran Gruber

The Function Handler is used to handle the use of various Function Sets within a class

File-specific:
Function Handler - Code File
The code used to provide for the implementation of a Function Handler
*/

#include <string.h>
#include "function_handler.h"
#include "../error-handler/error_handler.h"
#include "../../base-program/function/function_set.h"

static void __get_node(funct_hand_t *self, funct_hand_node_t **node, char *name);
static void __get_next_node(funct_hand_t *self, funct_hand_node_t *prev, funct_hand_node_t **next,
        bool funct_exists);
static void __get_prev_node(funct_hand_t *self, bool *funct_exists, funct_hand_node_t **prev_node,
        char *name);

void free_funct_hand(funct_hand_t *src) {
    if (src == NULL) return;

    funct_hand_node_t *temp, *curr = src->first;
    while (curr != NULL) {
        free_funct_set(curr->function_set);
        temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(src);
}

inst_error_t *new_fhand(prog_hand_t *prog_handler, funct_hand_t *dest) {
    if (dest == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }
    dest->first = NULL;
}

inst_error_t *fhand_add_function(prog_hand_t *prog_handler, funct_hand_t *self, function_t *function) {
    inst_error_t *error;
    if (self == NULL || function == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Get previous node
    funct_hand_node_t *prev, *curr;
    bool fset_exists;
    __get_prev_node(self, &fset_exists, &prev, function->name);
    // Add function to function set if it exists already
    if (fset_exists) {
        __get_next_node(self, prev, &curr, fset_exists);
        error = fset_add_function(prog_handler, curr->function_set, function);
        return error;
    }

    // Function set doesn't exist exist
    funct_hand_node_t *new_node = (funct_hand_node_t *)malloc(sizeof(funct_hand_node_t));
    // Create function set
    error = new_funct_set(prog_handler, new_node->function_set, function->name);
    if (error != NULL) return error;
    // Add function to function set
    error = fset_add_function(prog_handler, new_node->function_set, function);
    if (error != NULL) return error;

    // Add function set and return no errors
    if (prev == NULL) { // Function set is first
        // Add function set to handler
        new_node->next = self->first;
        self->first = new_node;
        return NULL;
    }
    new_node->next = prev->next;
    prev->next = new_node;
    return NULL;
}

inst_error_t *fhand_remove_function(prog_hand_t *prog_handler, funct_hand_t *self, char *name,
        class_t **param_types, int param_count) {
    inst_error_t *error;
    if (self == NULL || name == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }
    
    // Get function node
    funct_hand_node_t *prev, *curr;
    bool funct_exists;
    __get_prev_node(self, &funct_exists, &prev, name);
    __get_next_node(self, prev, &curr, funct_exists);
    if (curr == NULL) {
        return new_error(prog_handler, "ErrFunctionNotDefined");
    }
    
    // Remove function and return any errors including ErrFunctionNotDefined
    error = fset_remove(prog_handler, curr->function_set, param_types, param_count);
    if (error != NULL) return error;

    // Remove function set if that was the last function
    if (curr->function_set->first == NULL) {
        free_funct_set(curr->function_set);
        if (prev == NULL) { // No previous function sets
            self->first = curr->next;
        } else {
            prev->next = curr->next;
        }
        free(curr);
    }
    return NULL;
}

inst_error_t *fhand_get_function(prog_hand_t *prog_handler, funct_hand_t *self, function_t **dest,
        char *name, class_t **param_types, int param_count) {
    inst_error_t *error;
    if (self == NULL || dest == NULL || name == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Get the function node
    funct_hand_node_t *curr;
    __get_node(self, &curr, name);
    // Throw error if node could not be found
    if (curr == NULL) {
        return new_error(prog_handler, "ErrFunctionNotDefined");
    }
    // Get function from function set
    error = fset_get_function(prog_handler, curr->function_set, dest, param_types, param_count);
    return error;
}

inst_error_t *fhand_function_exists(prog_hand_t *prog_handler, bool *result, funct_hand_t *self,
        char *name, class_t **param_types, int param_count) {
    inst_error_t *error;
    if (result == NULL || self == NULL || name == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Get the current node
    funct_hand_node_t *curr;
    __get_node(self, &curr, name);
    if (curr == NULL) {
        *result = false;
        return NULL;
    }
    // Check function set
    *result = fset_function_exists(prog_handler, curr->function_set, result, param_types, param_count);
    return NULL;
}

static void __get_prev_node(funct_hand_t *self, bool *fset_exists, funct_hand_node_t **prev_node,
        char *name) {
    funct_hand_node_t *curr = self->first;
    *prev_node = NULL;

    // Loop through nodes
    while (curr != NULL) {
        // Check name of node
        int comparison = strcmp(name, curr->function_set->name);
        if (!comparison) { // Function was found
            *fset_exists = true;
            return;
        } else if (comparison < 0) { // Function is not in rest of set by alphabetic rules
            *fset_exists = false;
            return;
        }
        if (prev_node != NULL) *prev_node = curr;
        curr = curr->next;
    }
    *fset_exists = false;
}

static void __get_node(funct_hand_t *self, funct_hand_node_t **node, char *name) {
    // Get previous node
    funct_hand_node_t *prev;
    bool funct_exists;
    __get_prev_node(self, &funct_exists, &prev, name);
    // Get current node
    __get_next_node(self, prev, node, funct_exists);
}

static void __get_next_node(funct_hand_t *self, funct_hand_node_t *prev, funct_hand_node_t **next,
        bool fset_exists) {
    // Set next node to null
    if (!fset_exists) {
        *next = NULL;
        return;
    }
    // Function exists
    if (prev == NULL) {
        *next = self->first;
    } else {
        *next = prev->next;
    }
}