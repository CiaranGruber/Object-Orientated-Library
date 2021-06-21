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
#include "../error-handler/error_handler.h"
#include "../../base-program/static-function/static_function_set.h"

static void __get_node(s_funct_hand_t *self, s_funct_hand_node_t **node, char *name);
static void __get_next_node(s_funct_hand_t *self, s_funct_hand_node_t *prev, s_funct_hand_node_t **next,
        bool s_funct_exists);
static void __get_prev_node(s_funct_hand_t *self, bool *s_funct_exists, s_funct_hand_node_t **prev_node,
        char *name);

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

inst_error_t *new_sfhand(prog_hand_t *prog_handler, s_funct_hand_t *dest) {
    if (dest == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }
    dest->first = NULL;
}

inst_error_t *sfhand_add_function(prog_hand_t *prog_handler, s_funct_hand_t *self, s_function_t *function) {
    inst_error_t *error;
    if (self == NULL || function == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Get previous node
    s_funct_hand_node_t *prev, *curr;
    bool fset_exists;
    __get_prev_node(self, &fset_exists, &prev, function->name);
    // Add function to function set if it exists already
    if (fset_exists) {
        __get_next_node(self, prev, &curr, fset_exists);
        error = sfset_add_function(prog_handler, curr->function_set, function);
        return error;
    }

    // Function set doesn't exist exist
    s_funct_hand_node_t *new_node = (s_funct_hand_node_t *)malloc(sizeof(s_funct_hand_node_t));
    // Create function set
    error = new_s_funct_set(prog_handler, new_node->function_set, function->name);
    if (error != NULL) return error;
    // Add function to function set
    error = sfset_add_function(prog_handler, new_node->function_set, function);
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

inst_error_t *sfhand_remove_function(prog_hand_t *prog_handler, s_funct_hand_t *self, char *name,
        class_t **param_types, int param_count) {
    inst_error_t *error;
    if (self == NULL || name == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }
    
    // Get function node
    s_funct_hand_node_t *prev, *curr;
    bool s_funct_exists;
    __get_prev_node(self, &s_funct_exists, &prev, name);
    __get_next_node(self, prev, &curr, s_funct_exists);
    if (curr == NULL) {
        return new_error(prog_handler, "ErrFunctionNotDefined");
    }
    
    // Remove function and return any errors including ErrFunctionNotDefined
    error = sfset_remove(prog_handler, curr->function_set, param_types, param_count);
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

inst_error_t *sfhand_get_function(prog_hand_t *prog_handler, s_funct_hand_t *self, s_function_t **dest,
        char *name, class_t **param_types, int param_count) {
    inst_error_t *error;
    if (self == NULL || dest == NULL || name == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Get the function node
    s_funct_hand_node_t *curr;
    __get_node(self, &curr, name);
    // Throw error if node could not be found
    if (curr == NULL) {
        return new_error(prog_handler, "ErrFunctionNotDefined");
    }
    // Get function from function set
    error = sfset_get_function(prog_handler, curr->function_set, dest, param_types, param_count);
    return error;
}

inst_error_t *sfhand_function_exists(prog_hand_t *prog_handler, bool *result, s_funct_hand_t *self,
        char *name, class_t **param_types, int param_count) {
    inst_error_t *error;
    if (result == NULL || self == NULL || name == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Get the current node
    s_funct_hand_node_t *curr;
    __get_node(self, &curr, name);
    if (curr == NULL) {
        *result = false;
        return NULL;
    }
    // Check function set
    *result = sfset_function_exists(prog_handler, curr->function_set, result, param_types, param_count);
    return NULL;
}

static void __get_prev_node(s_funct_hand_t *self, bool *fset_exists, s_funct_hand_node_t **prev_node,
        char *name) {
    s_funct_hand_node_t *curr = self->first;
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

static void __get_node(s_funct_hand_t *self, s_funct_hand_node_t **node, char *name) {
    // Get previous node
    s_funct_hand_node_t *prev;
    bool s_funct_exists;
    __get_prev_node(self, &s_funct_exists, &prev, name);
    // Get current node
    __get_next_node(self, prev, node, s_funct_exists);
}

static void __get_next_node(s_funct_hand_t *self, s_funct_hand_node_t *prev, s_funct_hand_node_t **next,
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