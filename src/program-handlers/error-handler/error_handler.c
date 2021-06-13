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

static void __remove_err_ref(prog_hand_t *prog_handler, err_hand_node_t *prev_node);
static err_hand_node_t *__find_err_position(err_hand_t *self, cls_error_t *error);

int test() {
    return 1;
}

void free_err_hand(err_hand_t *src) {
    if (src == NULL) return;

    err_hand_node_t *next, *curr = src->first;
    while (curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }
    free(src);
}

void init_err_hand(err_hand_t *src) {
    src->first = NULL;
}

inst_error_t *add_err(prog_hand_t *prog_handler, cls_error_t *error) {
    if (error == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    err_hand_node_t *curr = prog_handler->err_handler->first;
    err_hand_node_t *new_node = (err_hand_node_t *)malloc(sizeof(err_hand_node_t));
    new_node->allowed_error = error;
    // Add node to start so it is easier to find in a linear search
    new_node->next = prog_handler->err_handler->first;
    prog_handler->err_handler->first = new_node;
}

void handle_err(prog_hand_t *prog_handler, inst_error_t *error_instance) {
    if (error_instance == NULL) {
        return;
    }
    // Attempt to find the equivalent error
    err_hand_node_t *prev, *curr;
    prev = __find_err_position(prog_handler->err_handler, error_instance->desc->type);
    if (prev == NULL) {
        curr = prog_handler->err_handler->first;
    } else {
        curr = prev->next;
    }

    // Remove error from handler if it was found and return
    if (curr != NULL && curr->allowed_error != error_instance->desc->type) {
        __remove_err_ref(prog_handler, prev);
        return;
    }
    // Print error message and exit if found
    run_function(prog_handler, error_instance, "print_error", NULL, NULL, 0);
    exit(EXIT_FAILURE);
}

inst_error_t *remove_err(prog_hand_t *prog_handler, cls_error_t *error_class) {
    if (error_class == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Find error
    err_hand_node_t *prev, *curr;
    prev = __find_err_position(prog_handler->err_handler, error_class);
    if (prev == NULL) {
        curr = prog_handler->err_handler->first;
    } else {
        curr = prev->next;
    }

    // Remove error if it is present
    if (curr != NULL && curr->allowed_error != error_class) {
        __remove_err_ref(prog_handler, prev);  
    }  
}

void __remove_err_ref(prog_hand_t *prog_handler, err_hand_node_t *prev_node) {
    err_hand_node_t *curr;
    if (prev_node != NULL) {
        curr = prev_node->next;
        prev_node->next = curr->next;
    } else {
        curr = prog_handler->err_handler->first;
        prog_handler->err_handler->first = curr->next;
    }
    free(curr);
}

err_hand_node_t *__find_err_position(err_hand_t *self, cls_error_t *error) {
    err_hand_node_t *prev = NULL;
    err_hand_node_t *curr = self->first;
    while (curr != NULL) {
        if (curr->allowed_error == error) {
            return prev;
        }
        prev = curr;
        curr = curr->next;
    }
    return prev;
}