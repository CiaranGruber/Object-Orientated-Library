/*
Variable Description Handler
By Ciaran Gruber

The Variable Description Handler structure is used to handle the Variable Descriptions for classes

File-specific:
Variable Description Handler - Header File
The code used to provide for the implementation of a Variable Description Handler
*/

#include <string.h>
#include "var_desc_handler.h"

void free_var_desc_hand(var_desc_hand_t *src) {
    if (src == NULL) return;

    var_desc_hand_node_t *next, *curr = src->first;
    while (curr != NULL) {
        next = curr->next;
        free_var_desc(curr->var_desc);
        free(curr);
        curr = next;
    }
    free(src);
}

inst_error_t *var_desc_hand_create(prog_hand_t *prog_handler, var_desc_hand_t *src) {
    if (src == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }
    src->first = NULL;
    return NULL;
}

inst_error_t *add_var_desc(prog_hand_t *prog_handler, var_desc_hand_t *self, var_desc_t *var_desc) {
    inst_error_t *error;

    if (self == NULL || var_desc == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    var_desc_hand_node_t *prev = NULL; 
    var_desc_hand_node_t *curr = self->first;
    while (curr != NULL) {
        int comparison = strcmp(var_desc->name, curr->var_desc->name);
        if (!comparison) {
            return new_error(prog_handler, "ErrVariableNameTaken");
        } else if (comparison < 0) {
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    var_desc_hand_node_t *new_node = (var_desc_hand_node_t *)malloc(sizeof(var_desc_hand_node_t));
    new_node->var_desc = var_desc;
    if (prev != NULL) {
        prev->next = new_node;
    } else {
        self->first = new_node;
    }
    new_node->next = curr;
    return NULL;
}

inst_error_t *remove_var_desc(prog_hand_t *prog_handler, var_desc_hand_t *self, 
        var_desc_t *var_desc) {
    inst_error_t *error;
    error = remove_var_desc_by_name(prog_handler, self, var_desc->name);
    return error;
}

inst_error_t *remove_var_desc_by_name(prog_hand_t *prog_handler, var_desc_hand_t *self, 
        char *name) {
    inst_error_t *error;

    if (self == NULL || name == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Attempt to find variable
    var_desc_hand_node_t *prev = NULL;
    var_desc_hand_node_t *curr = self->first;
    while (curr != NULL) {
        int comparison = strcmp(name, curr->var_desc->name);
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
    // Remove variable
    if (prev != NULL) {
        prev->next = curr->next;
    } else {
        self->first = curr->next;
    }
    free_var_desc(curr->var_desc);
    free(curr);
    return NULL;
}

inst_error_t *get_var_desc(prog_hand_t *prog_handler, var_desc_hand_t *self, var_desc_t **dest,
        char *name) {
    inst_error_t *error;

    if (self == NULL || dest == NULL || name == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    var_desc_hand_node_t *curr = self->first;
    while (curr != NULL) {
        int comparison = strcmp(name, curr->var_desc->name);
        if (!comparison) {
            *dest = curr->var_desc;
            return NULL;
        } else if (comparison < 0) {
            break;
        }
        curr = curr->next;
    }
    return new_error(prog_handler, "ErrVariableNotDefined");
}