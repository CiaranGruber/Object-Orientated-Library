/*
Variable Handler
By Ciaran Gruber

The Variable Handler structure is used to handle variables in instances and classes

File-specific:
Variable Handler - Code File
The code used to provide for the implementation of a Variable Handler
*/

#include <string.h>
#include "variable_handler.h"

void free_var_hand(var_hand_t *src) {
    if (src == NULL) return;

    var_hand_node_t *next, *curr = src->first;
    while (curr != NULL) {
        next = curr->next;
        free_var(curr->variable);
        free(curr);
        curr = next;
    }
    free(src);
}

inst_error_t *var_hand_create(prog_hand_t *prog_handler, var_hand_t *src) {
    if (src == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }
    src->first = NULL;
    return NULL;
}

inst_error_t *add_var(prog_hand_t *prog_handler, var_hand_t *self, var_t *variable) {
    inst_error_t *error;

    if (self == NULL || variable == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Return an error if a variable is found
    var_hand_node_t *prev = NULL;
    var_hand_node_t *curr = self->first;
    while (curr != NULL) {
        int comparison = strcmp(variable->desc->name, curr->variable->desc->name);
        if (!comparison) {
            return new_error(prog_handler, "ErrVariableNameTaken");
        } else if (comparison < 0) {
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    // Add variable
    var_hand_node_t *new_node = (var_hand_node_t *)malloc(sizeof(var_hand_node_t));
    new_node->variable = variable;
    if (prev != NULL) {
        prev->next = new_node;
    } else {
        self->first = new_node;
    }
    new_node->next = curr;
    return NULL;
}

inst_error_t *remove_var(prog_hand_t *prog_handler, var_hand_t *self, var_t *variable) {
    inst_error_t *error;
    error = remove_var_by_name(prog_handler, self, variable->desc->name);
    return error;
}

inst_error_t *remove_var_by_name(prog_hand_t *prog_handler, var_hand_t *self, char *name) {
    inst_error_t *error;
    if (self == NULL || name == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Attempt to find the variable
    var_hand_node_t *prev = NULL;
    var_hand_node_t *curr = self->first;
    while (curr != NULL) {
        int comparison = strcmp(name, curr->variable->desc->name);
        if (!comparison) {
            break;
        } else if (comparison < 0) {
            curr = NULL; // Ensure an error is produced
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) {
        return new_error(prog_handler, "ErrVariableNotDefined");
    }

    // Remove the variable
    if (prev != NULL) {
        prev->next = curr->next;
    } else {
        self->first = curr->next;
    }
    free_var(curr->variable);
    free(curr);
    return NULL;
}

inst_error_t *get_var(prog_hand_t *prog_handler, var_hand_t *self, var_t **dest, char *name) {
    inst_error_t *error;
    if (self == NULL || dest == NULL || name == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Attempt to find and point to the variable
    var_hand_node_t *curr = self->first;
    while (curr != NULL) {
        int comparison = strcmp(name, curr->variable->desc->name);
        if (!comparison) {
            *dest = curr->variable;
            return NULL;
        } else if (comparison < 0) {
            break;
        }
        curr = curr->next;
    }
    return new_error(prog_handler, "ErrVariableNotDefined");
}