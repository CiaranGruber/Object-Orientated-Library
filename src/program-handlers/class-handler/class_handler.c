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
    class_node_t *next, *curr = src->first;
    while (curr != NULL) {
        next = curr->next;
        free_class(curr->class);
        free(next);
        curr = next;
    }
    free(src);
}

inst_error_t *add_class(prog_hand_t *prog_handler, class_t *class) {
    inst_error_t *error = (inst_error_t *)malloc(sizeof(inst_error_t));

    if (class == NULL) {
        free(error);
        return NULL;
    }
    class_node_t *curr, *prev;
    curr = prog_handler->cls_handler->first;
    while (curr != NULL) {
        int comparison = strcmp(curr->class->class_name, class->class_name);
        if (!comparison) {
            new_instance(prog_handler, "ErrClassAlreadyExists", error, NULL, 0);
            handle_err(prog_handler, error);
            return error;
        }
        if (comparison < 0) {
            class_node_t *new_node = (class_node_t *)malloc(sizeof(class_node_t));
            if (new_node == NULL) {
                new_instance(prog_handler, "ErrOutOfMemory", error, NULL, 0);
                handle_err(prog_handler, error);
                return error;
            }
            new_node->class = class;
            prev->next = new_node;
            new_node->next = curr;
            free(error);
            return NULL;
        }
        prev = curr;
        curr = curr->next;
    }
    class_node_t *new_node = (class_node_t *)malloc(sizeof(class_node_t));
    if (new_node == NULL) {
        new_instance(prog_handler, "ErrOutOfMemory", error, NULL, 0);
        handle_err(prog_handler, error);
        return error;
    }
    new_node->class = class;
    prev->next = new_node;
    free(error);
    return NULL;
}

inst_error_t *get_class(prog_hand_t *prog_handler, class_t **dest, char *class_name) {
    inst_error_t *error = (inst_error_t *)malloc(sizeof(inst_error_t));

    if (class_name == NULL || *dest == NULL) {
        new_instance(prog_handler, "ErrInvalidParameters", error, NULL, 0);
        handle_err(prog_handler, error);
        return error;
    }
    class_node_t *curr = prog_handler->cls_handler->first;
    while (curr != NULL) {
        int comparison = strcmp(class_name, curr->class->class_name);
        if (!comparison) {
            *dest = curr->class;
            free(error);
            return NULL;
        }
    }
    new_instance(prog_handler, "ErrClassNotDefined", error, NULL, 0);
    handle_err(prog_handler, error);
    return error;
}