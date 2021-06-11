/*
Error Handler
By Ciaran Gruber

The Error Handler structure is used to handle errors within the program

File-specific:
Error Handler - Code File
The code used to provide for the implementation of a Error Handler
*/

#include <string.h>
#include "error_handler.h"

void free_err_hand(err_hand_t *src) {
    err_hand_node_t *next, *curr = src->first;
    while (curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }
    free(src);
}

void add_err(err_hand_t *self, cls_error_t *error) {
    err_hand_node_t *prev, *curr = self->first;
    while (curr != NULL) {
        if (curr->allowed_error == error) {
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    err_hand_node_t *new_node = (err_hand_node_t *)malloc(sizeof(err_hand_node_t));
    new_node->allowed_error = error;
    new_node->next = curr;
    prev->next = new_node;
}

void handle_err(prog_hand_t *prog_handler, inst_error_t *error_instance) {
    if (error_instance == NULL) {
        return;
    }
    err_hand_node_t *curr = prog_handler->err_handler->first;
    while (curr != NULL) {
        error_data_t *error_data = (error_data_t *)error_instance->data;
        if (curr->allowed_error == error_data->type) {
            return;
        }
    }
    var_run_func(prog_handler, error_instance, "print_error", NULL, NULL, 0);
    exit(EXIT_FAILURE);
}

void del_err(prog_hand_t *prog_handler, inst_error_t *error_instance) {
    err_hand_node_t *prev, *node;
    __find_err_position(prog_handler->err_handler, prev, error_instance->type);
    node = prev == NULL ? prog_handler->err_handler->first : prev->next;
    // Ignore if instance class is not handled
    if (node->allowed_error != error_instance->type) {
        return;
    }
    prev->next = node->next;
    free(node);
}

void __find_err_position(err_hand_t *self, cls_error_t *prev, cls_error_t *error) {
    err_hand_node_t *curr = self->first;
    while (curr != NULL) {
        if (curr->allowed_error == error) {
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    prev = NULL;
}