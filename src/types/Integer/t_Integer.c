/*
Integer Type
By Ciaran Gruber

The Integer Class is one of the base variable types that hold data in its own data holding.
Therefore, the integer class would not inherit member fields and data is accessed directly

Parent Class: Object

File-specific:
Integer Type - Code File
The code used to provide for the implementation of an Integer type
*/

#include <string.h>
#include "t_Integer.h"
#include "../helper_type.h"

// Initialisation Functions - Used to initialise the class

static inst_error_t *add_constructor(prog_hand_t *prog_handler, cls_integer_t *int_class,
        funct_hand_t *funct_handler);
static inst_error_t *add_add(prog_hand_t *prog_handler, cls_integer_t *int_class,
        funct_hand_t *funct_handler);
static inst_error_t *add_subtract(prog_hand_t *prog_handler, cls_integer_t *int_class,
        funct_hand_t *funct_handler);
static inst_error_t *add_multiply(prog_hand_t *prog_handler, cls_integer_t *int_class,
        funct_hand_t *funct_handler);
static inst_error_t *add_divide(prog_hand_t *prog_handler, cls_integer_t *int_class,
        funct_hand_t *funct_handler);

// Non-Static Functions

static inst_error_t *constructor(prog_hand_t *prog_handler, inst_integer_t *self,
        var_t *void_return, var_t **void_params);
static inst_error_t *add(prog_hand_t *prog_handler, inst_integer_t *self,
        var_t *void_return, inst_integer_t **params);
static inst_error_t *subtract(prog_hand_t *prog_handler, inst_integer_t *self,
        var_t *void_return, inst_integer_t **params);
static inst_error_t *multiply(prog_hand_t *prog_handler, inst_integer_t *self,
        var_t *void_return, inst_integer_t **params);
static inst_error_t *divide(prog_hand_t *prog_handler, inst_integer_t *self,
        var_t *void_return, inst_integer_t **params);

inst_error_t *new_integer_cls(prog_hand_t *prog_handler) {
    inst_error_t *error;

    // Create class name
    cls_integer_t *class = (cls_integer_t *)malloc(sizeof(cls_integer_t));
    class->class_name = (char *)malloc(strlen(INTEGER_CLASS_NAME));
    if (class->class_name == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }
    strcpy(class->class_name, INTEGER_CLASS_NAME);

    // Set parent class
    cls_object_t *object_class;
    error = get_class(prog_handler, &object_class, OBJECT_CLASS_NAME);
    if (error != NULL) return error;
    class->parent = object_class;

    // Set integer data description
    class->uses_inst_var_handler = false;
    class->size = sizeof(int);

    error = add_class(prog_handler, class);
    return error;
}

inst_error_t *init_integer_cls(prog_hand_t *prog_handler) {
    inst_error_t *error;

    // Handlers
    s_funct_hand_t *static_methods;
    funct_hand_t *inst_methods;
    // Classes
    cls_integer_t *int_class;

    // Get Integer class
    error = get_class(prog_handler, &int_class, INTEGER_CLASS_NAME);
    if (error != NULL) return error;

    // Initialise Static Function Handler
    error = init_static_handler(prog_handler, int_class);
    if (error != NULL) return error;
    static_methods = int_class->static_methods;

    // Initialise Non-Static Function Handler
    error = init_inst_handler(prog_handler, int_class);
    if (error != NULL) return error;
    static_methods = int_class->static_methods;

    // Initialise Class Variable Handler
    error = init_class_variables(prog_handler, int_class);
    if (error != NULL) return error;

    // Initialise Member Field Handler
    int_class->mem_fields = NULL;

    // Add relevant functions
    error = add_constructor(prog_handler, int_class, inst_methods);
    if (error != NULL) return error;
    error = add_add(prog_handler, int_class, inst_methods);
    if (error != NULL) return error;
    error = add_subtract(prog_handler, int_class, inst_methods);
    if (error != NULL) return error;
    error = add_multiply(prog_handler, int_class, inst_methods);
    if (error != NULL) return error;
    error = add_divide(prog_handler, int_class, inst_methods);
    if (error != NULL) return error;
}

static inst_error_t *add_constructor(prog_hand_t *prog_handler, cls_integer_t *int_class,
        funct_hand_t *funct_handler) {
    inst_error_t *error;
    function_t *new_func;
    class_t **param_types;
    int param_count = 0;

    new_func = (function_t *)malloc(sizeof(function_t));
    if (new_func == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }

    param_types = NULL;

    error = new_function(prog_handler, new_func, INTEGER_CLASS_NAME, constructor, int_class, 
                        param_types, param_count);
    if (error != NULL) return error;
    error = add_function(prog_handler, funct_handler, new_func);
    if (error != NULL) return error;
}

static inst_error_t *add_add(prog_hand_t *prog_handler, cls_integer_t *int_class,
        funct_hand_t *funct_handler) {
    inst_error_t *error;
    function_t *new_func;
    class_t **param_types;
    int param_count = 1;
    
    new_func = (function_t *)malloc(sizeof(function_t));
    if (new_func == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }

    param_types = (class_t **)malloc(param_count*sizeof(class_t *));
    if (param_types == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }
    param_types[0] = int_class;

    error = new_function(prog_handler, new_func, "add", add, int_class, 
                            param_types, param_count);
    if (error != NULL) return error;
    error = add_function(prog_handler, funct_handler, new_func);
    if (error != NULL) return error;
}

static inst_error_t *add_subtract(prog_hand_t *prog_handler, cls_integer_t *int_class,
        funct_hand_t *funct_handler) {
    inst_error_t *error;
    function_t *new_func;
    class_t **param_types;
    int param_count = 1;
    
    new_func = (function_t *)malloc(sizeof(function_t));
    if (new_func == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }

    param_types = (class_t **)malloc(param_count*sizeof(class_t *));
    if (param_types == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }
    param_types[0] = int_class;

    error = new_function(prog_handler, new_func, "subtract", subtract, int_class, 
                            param_types, param_count);
    if (error != NULL) return error;
    error = add_function(prog_handler, funct_handler, new_func);
    if (error != NULL) return error;
}

static inst_error_t *add_multiply(prog_hand_t *prog_handler, cls_integer_t *int_class,
        funct_hand_t *funct_handler) {
    inst_error_t *error;
    function_t *new_func;
    class_t **param_types;
    int param_count = 1;
    
    new_func = (function_t *)malloc(sizeof(function_t));
    if (new_func == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }

    param_types = (class_t **)malloc(param_count*sizeof(class_t *));
    if (param_types == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }
    param_types[0] = int_class;

    error = new_function(prog_handler, new_func, "multiply", multiply, int_class, 
                            param_types, param_count);
    if (error != NULL) return error;
    error = add_function(prog_handler, funct_handler, new_func);
    if (error != NULL) return error;
}

static inst_error_t *add_divide(prog_hand_t *prog_handler, cls_integer_t *int_class,
        funct_hand_t *funct_handler) {
    inst_error_t *error;
    function_t *new_func;
    class_t **param_types;
    int param_count = 1;
    
    new_func = (function_t *)malloc(sizeof(function_t));
    if (new_func == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }

    param_types = (class_t **)malloc(param_count*sizeof(class_t *));
    if (param_types == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }
    param_types[0] = int_class;

    error = new_function(prog_handler, new_func, "divide", divide, int_class, 
                            param_types, param_count);
    if (error != NULL) return error;
    error = add_function(prog_handler, funct_handler, new_func);
    if (error != NULL) return error;
}

/*
Type: Non-static

Constructs an integer variable, setting the data value to the default (0)

Parameters: None

Returns:
Integer - The constructed Integer instance
*/
static inst_error_t *constructor(prog_hand_t *prog_handler, inst_integer_t *self,
        var_t *void_return, var_t **void_params) {
    self->data = (void *)0;
}

/*
Type: Non-static

Adds a given Integer onto the Integer instance

Parameters:
1. Integer - The integer to add to the first

Returns: None
*/
static inst_error_t *add(prog_hand_t *prog_handler, inst_integer_t *self,
        var_t *void_return, inst_integer_t **params) {
    inst_error_t *error;
    inst_integer_t *other = params[0];

    // Get integer class
    cls_integer_t *integer_class;
    error = get_class(prog_handler, &integer_class, INTEGER_CLASS_NAME);
    if (error != NULL) return error;

    // Get data
    int self_data, other_data;
    get_data(prog_handler, self, (void **)&self_data);
    get_data(prog_handler, other, (void **)&other_data);

    // Add the two values
    self_data += other_data;

    return NULL;
}

/*
Type: Non-static

Subtracts a given Integer from the Integer instance

Parameters:
1. Integer - The integer to subtract from the first

Returns: None
*/
static inst_error_t *subtract(prog_hand_t *prog_handler, inst_integer_t *self,
        var_t *void_return, inst_integer_t **params) {
    inst_error_t *error;
    inst_integer_t *other = params[0];

    // Get integer class
    cls_integer_t *integer_class;
    error = get_class(prog_handler, &integer_class, INTEGER_CLASS_NAME);
    if (error != NULL) return error;

    // Get data
    int self_data, other_data;
    get_data(prog_handler, self, (void **)&self_data);
    get_data(prog_handler, other, (void **)&other_data);

    // Subtract the two values
    self_data -= other_data;

    return NULL;
}

/*
Type: Non-static

Multiply a given Integer with the Integer instance

Parameters:
1. Integer - The integer to multiply with the first

Returns: None
*/
static inst_error_t *multiply(prog_hand_t *prog_handler, inst_integer_t *self,
        var_t *void_return, inst_integer_t **params) {
    inst_error_t *error;
    inst_integer_t *other = params[0];

    // Get integer class
    cls_integer_t *integer_class;
    error = get_class(prog_handler, &integer_class, INTEGER_CLASS_NAME);
    if (error != NULL) return error;

    // Get data
    int self_data, other_data;
    get_data(prog_handler, self, (void **)&self_data);
    get_data(prog_handler, other, (void **)&other_data);

    // Multiply the two values
    self_data *= other_data;

    return NULL;
}

/*
Type: Non-static

Divides the Integer instance with another integer instance

Parameters:
1. Integer - The integer that the instance will be divided by

Returns: None
*/
static inst_error_t *divide(prog_hand_t *prog_handler, inst_integer_t *self,
        var_t *void_return, inst_integer_t **params) {
    inst_error_t *error;
    inst_integer_t *other = params[0];

    // Get integer class
    cls_integer_t *integer_class;
    error = get_class(prog_handler, &integer_class, INTEGER_CLASS_NAME);
    if (error != NULL) return error;

    // Get data
    int self_data, other_data;
    get_data(prog_handler, self, (void **)&self_data);
    get_data(prog_handler, other, (void **)&other_data);

    // Divide the two values
    self_data /= other_data;

    return NULL;
}