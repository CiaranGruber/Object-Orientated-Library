/*
Package Title: Lang Package
Package Author: Ciaran Gruber

Package Description:
This file contains the code used to import the Language package and also create the program handler
*/

#include "pkg_dev_lang.h"
#include "../src/typedefs.h"
#include "../src/program-handlers/program-handler/program_handler.h"
//#include "../src/types/Boolean"
//#include "../src/types/Char"
#include "../src/types/Error/t_Error.h"
#include "../src/types/Error/main-types/ErrFunctionNotDefined/t_ErrFunctionNotDefined.h"
//#include "../src/types/Error/main-types/ErrOutOfMemory"
//#include "../src/types/Pointer"
#include "../src/types/Object/t_Object.h"
#include "../src/types/Integer/t_Integer.h"

prog_hand_t *new_lang_package() {
    prog_hand_t *program_handler = (prog_hand_t *)malloc(sizeof(prog_hand_t));
    init_prog_hand(program_handler);
    return program_handler;
}

inst_error_t *import_lang_package(prog_hand_t *prog_handler) {
    inst_error_t *error;

    // Add Classes (No error checking due to initial language)
    new_object_cls(prog_handler);
    new_integer_cls(prog_handler);
    new_error_cls(prog_handler);
    new_err_function_not_defined_cls(prog_handler);
}