/*
Error Type
By Ciaran Gruber

The Error type provides the base type for all Error types

File-specific:
Error type - Header File
The structures used to determine the standard error class
*/

#ifndef ERROR_CODES
#define ERROR_CODES

#include "../../base-program/generic-variable/variable.h"
#include "../../base-program/generic-class/class.h"
#include "../../base-program/generic-function/function.h"

typedef var_t inst_error_t;
typedef class_t cls_error_t;

/* A structure useds to represent the data used in an error variable */
typedef struct {
    cls_error_t *type;           // The type that is used to represent the error
    char *message;               // The message that is created by the error
    function_t *parent_function; // The parent function from which the error was produced
    inst_error_t *parent_error;  // The error that caused this error to be produced
} error_data_t;

int new_error_cls(cls_error_t *dest);

int new_error_inst(inst_error_t *dest, cls_error_t *base_class);

#endif