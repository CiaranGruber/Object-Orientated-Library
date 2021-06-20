/*
Program Handler
By Ciaran Gruber

The Program Handler structure contains the error handling and class handling structures used
throughout the library

File-specific:
Program Handler - Code File
The code used to provide for the implementation of a Program Handler
*/

#include "program_handler.h"
#include "../class-handler/class_handler.h"
#include "../error-handler/error_handler.h"

void free_prog_hand(prog_hand_t *src) {
    if (src == NULL) return;

    free_cls_hand(src->cls_handler);
    free_err_hand(src->err_handler);
    free(src);
}

void init_prog_hand(prog_hand_t *src) {
    src->cls_handler = (cls_hand_t *)malloc(sizeof(cls_hand_t));
    src->err_handler = (err_hand_t *)malloc(sizeof(err_hand_t));
    init_cls_hand(src->cls_handler);
    init_err_hand(src->err_handler);
}