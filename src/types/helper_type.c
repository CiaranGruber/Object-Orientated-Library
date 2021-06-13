/*
Type Construction Helper Functions
By Ciaran Gruber

The functions defined are used to help in the process of creating and initialising classes

Parent Class: None

File-specific:
Type Construction Helper Functions - Code File
The code used to provide for the implementation of a String type
*/

#include "helper_type.h"

inst_error_t *init_inst_handler(prog_hand_t *prog_handler, class_t *class) {
    inst_error_t *error;

    // Allocate methods
    funct_hand_t *inst_methods = (funct_hand_t *)malloc(sizeof(funct_hand_t));
    if (inst_methods == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }
    funct_hand_create(prog_handler, inst_methods);

    // Set class methods
    class->inst_methods = inst_methods;

    return NULL;
}

inst_error_t *init_static_handler(prog_hand_t *prog_handler, class_t *class) {
    inst_error_t *error;

    s_funct_hand_t *static_methods = (s_funct_hand_t *)malloc(sizeof(s_funct_hand_t));
    if (static_methods == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }
    s_funct_hand_create(prog_handler, static_methods);
    class->static_methods = static_methods;

    return NULL;
}

inst_error_t *init_class_variables(prog_hand_t *prog_handler, class_t *class) {
    inst_error_t *error;

    var_hand_t *class_vars = (var_hand_t *)malloc(sizeof(var_hand_t));
    if (class_vars == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }
    error = var_hand_create(prog_handler, class_vars);
    if (error != NULL) return error;
    class->class_vars = class_vars;

    return NULL;
}

inst_error_t *init_member_fields(prog_hand_t *prog_handler, class_t *class) {
    inst_error_t *error;

    var_desc_hand_t *member_fields = (var_desc_hand_t *)malloc(sizeof(var_desc_hand_t));
    if (member_fields == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }
    error = var_desc_hand_create(prog_handler, member_fields);
    if (error != NULL) return error;
    class->mem_fields = member_fields;

    return NULL;
}