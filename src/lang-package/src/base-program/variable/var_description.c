/*
Variable Description
By Ciaran Gruber

The Variable Description is used to describe an the key parts of an uninitialised variable that can
be used when constructing an instance

File-specific:
Variable Description - Code File
The code used to provide for the implementation of a Variable
*/

#include <string.h>
#include "var_description.h"
#include "../../program-handlers/class-handler/class_handler.h"
#include "../../program-handlers/error-handler/error_handler.h"

void free_var_desc(var_desc_t *src) {
    if (src == NULL) return;

    free(src->name);
    free(src);
}

inst_error_t *new_var_desc(prog_hand_t *prog_handler, var_desc_t *dest) {
    if (dest == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    dest->initialised = false;
    dest->name = NULL;
    dest->type = NULL;
    return NULL;
}

inst_error_t *init_var_desc(prog_hand_t *prog_handler, var_desc_t *dest, char *type, char *name) {
    inst_error_t *error;
    if (dest == NULL || type == NULL || name == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Free any existing memory
    if (dest->initialised) {
        free(dest->name);
    }

    // Get class
    error = get_class(prog_handler, &(dest->type), type);
    if (error != NULL) return error;

    // Copy name
    dest->name = (char *)malloc(strlen(name)*sizeof(char));
    if (dest->name == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }
    strcpy(dest->name, name);

    // Set initialisation value
    dest->initialised = true;

    return NULL;
}