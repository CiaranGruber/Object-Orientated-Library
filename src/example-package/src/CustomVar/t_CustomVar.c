/*
<Custom Var> Type
By <Author>

<Type Description>

Parent Class: <Parent Class>

File-specific:
<Custom Var> Type - Code File
The code used to provide for the implementation of a <Custom Var> type
*/

#include <stdlib.h>
#include "t_CustomVar.h"

inst_error_t *new_custom_var_cls(prog_hand_t *prog_handler) {
    inst_error_t *error;

    error = new_class(prog_handler, CUSTOM_VAR_CLS_NAME, NULL, true, 0);
    return error;
}

inst_error_t *init_custom_var_cls(prog_hand_t *prog_handler) {
    inst_error_t *error;

    // Classes
    cls_object_t *object_class;
    cls_integer_t *int_class;
    cls_custom_var_t *custom_var_class;

    // Get Object class
    error = get_class(prog_handler, &object_class, OBJECT_CLS_NAME);
    if (error != NULL) return error;

    // Get Integer class
    error = get_class(prog_handler, &int_class, INTEGER_CLS_NAME);
    if (error != NULL) return error;

    // Get Custom Var class
    error = get_class(prog_handler, &custom_var_class, CUSTOM_VAR_CLS_NAME);
    if (error != NULL) return error;

    // Initialise class
    error = init_class(prog_handler, custom_var_class);
    if (error != NULL) return error;

    // Add functions

}

static inst_error_t *static_func(prog_hand_t *prog_handler, inst_integer_t *self,
        var_t *void_return, var_t **void_params)