/*
Class Handler
By Ciaran Gruber

The Class Handler is used to handle classes within the program 

File-specific:
Class Handler - Code File
The code used to provide for the implementation of a Class Handler
*/

#include <string.h>
#include "class_handler.h"

void free_cls_hand(cls_hand_t *src) {
    if (src == NULL) return;

    // Free class nodes
    class_node_t *next, *curr = src->first;
    while (curr != NULL) {
        next = curr->next;
        free_class(curr->class);
        free(next);
        curr = next;
    }
    free(src);
}

void init_cls_hand(cls_hand_t *src) {
    src->first = NULL;
}

inst_error_t *add_class(prog_hand_t *prog_handler, class_t *class) {
    inst_error_t *error;
    if (class == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    class_node_t *curr, *prev = NULL;
    curr = prog_handler->cls_handler->first;
    // Loop through classes until the node if found
    while (curr != NULL) {
        if (!strcmp(class->class_name, curr->class->class_name)) {
            return new_error(prog_handler, "ErrClassAlreadyExists");
        }
        prev = curr;
        curr = curr->next;
    }
    // Create node at end of list
    class_node_t *new_node = (class_node_t *)malloc(sizeof(class_node_t));
    if (new_node == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }
    if (prev != NULL) {
        prev->next = new_node;
    } else {
        prog_handler->cls_handler->first = new_node;
    }
    new_node->class = class;
    new_node->next = NULL;
    return NULL;
}

inst_error_t *get_class(prog_hand_t *prog_handler, class_t **dest, char *class_name) {
    inst_error_t *error;
    if (dest == NULL || class_name == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Attempt to find class
    class_node_t *curr = prog_handler->cls_handler->first;
    while (curr != NULL) {
        int comparison = strcmp(class_name, curr->class->class_name);
        if (!comparison) {
            break;
        }
        curr = curr->next;
    }
    if (curr == NULL) {
        return new_error(prog_handler, "ErrClassNotDefined");
    }

    // Set reference
    *dest = curr->class;
    return NULL;
}