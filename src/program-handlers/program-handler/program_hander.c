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

void free_prog_hand(prog_hand_t *src) {
    free_cls_hand(src->cls_handler);
    free_err_hand(src->err_handler);
    free(src);
}