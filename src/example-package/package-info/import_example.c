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

    // Add Custom Var
    error = new_custom_var_cls(prog_handler);
    if (err_is_equal(error, "ErrClassAlreadyExists")) 
        add_err(prog_handler, "ErrClassAlreadyExists");
    else if (error != NULL) return error;
    // Add Custom Var 2
    error = new_custom_var_2_cls(prog_handler);
    if (err_is_equal(error, "ErrClassAlreadyExists")) 
        add_err(prog_handler, "ErrClassAlreadyExists");
    else if (error != NULL) return error;

    // Initialise Classes
    error = init_custom_var_cls(prog_handler);
    if (error != NULL) return error;
    error = init_custom_var_2_cls(prog_handler);
    if (error != NULL) return error;
}