/*
Package Title: <Title> - <Context>
Package Author: <Author>

Package Description:
<Description>
*/

#ifndef PKG_PACKAGE_TITLE
#define PKG_PACKAGE_TITLE

// Package Dependencies
#include "../dependencies/pkg_dev_lang.h"

/* A type of variable used to represent a <Custom Var> instance */
typedef inst_object_t inst_custom_var_t;
/* A type of class used to represent a <Custom Var> class */
typedef class_t cls_error_t;

/*
Imports the Language package by creating and initialising each of the classes within the program

prog_handler: The program handler that the package is importing into

Errors:
    ErrOutOfMemory: Thrown if there is not enough memory to import the package
*/
inst_error_t *import_package_title(prog_hand_t *prog_handler);

#endif