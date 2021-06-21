/*
Package Title: <Title> - <Context>
Package Author: <Author>

Package Description:
<Description>
*/

#include "pkg_eu_example.h"
#include "../src/CustomVar/t_CustomVar.h"
#include "../src/CustomVar2/t_CustomVar2.h"

inst_error_t *import_lang_package(prog_hand_t *prog_handler) {
    inst_error_t *error;

    add_err(prog_handler, "ErrClassAlreadyExists");

    // Add Classes
    bool cls_already_exists;
    class_exists(prog_handler, &cls_already_exists, NULL, CUSTOM_VAR_CLS_NAME);

    // Initialise Classes
    error = init_custom_var_cls(prog_handler);
    if (error != NULL) return error;
    error = init_custom_var_2_cls(prog_handler);
    if (error != NULL) return error;
}