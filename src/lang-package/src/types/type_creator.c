/*
Type Construction Helper Functions
By Ciaran Gruber

The functions defined are used to help in the process of creating and initialising classes

Parent Class: None

File-specific:
Type Construction Helper Functions - Code File
The code used to provide for the implementation of a String type
*/

#include <string.h>
#include "type_creator.h"
#include "../../src/program-handlers/program-handler/program_handler.h"
#include "../../src/program-handlers/error-handler/error_handler.h"
#include "../../src/program-handlers/class-handler/class_handler.h"
#include "../../src/program-handlers/function-handler/function_handler.h"
#include "../../src/program-handlers/static-function-handler/static_function_handler.h"
#include "../../src/program-handlers/variable-description-handler/var_desc_handler.h"
#include "../../src/program-handlers/variable-handler/variable_handler.h"

static inst_error_t *init_inst_handler(prog_hand_t *prog_handler, class_t *class);
static inst_error_t *init_static_handler(prog_hand_t *prog_handler, class_t *class);
static inst_error_t *init_class_variables(prog_hand_t *prog_handler, class_t *class);
static inst_error_t *init_member_fields(prog_hand_t *prog_handler, class_t *class);

// The data used in an managed variable and all child classes excluding base classes
typedef struct {
    var_hand_t *variable_handler;
} managed_data_t;

inst_error_t *new_class(prog_hand_t *prog_handler, char *class_name, char *parent_class,
        bool managed_data, size_t size) {
    inst_error_t *error;
    if (class_name == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }
    class_t *class = (class_t *)malloc(sizeof(class_t));

    // Create class name
    class->class_name = (char *)malloc(strlen(class_name));
    if (class->class_name == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }
    strcpy(class->class_name, class_name);

    // Set parent class
    if (parent_class == NULL) {
        class->parent = NULL;
    } else {
        error = get_class(prog_handler, &(class->parent), parent_class);
        if (error!= NULL) return error;
    }

    // Set integer data description
    class->has_managed_data = managed_data;
    if (managed_data) {
        class->size = sizeof(managed_data_t);
    } else {
        class->size = size;
    }

    error = add_class(prog_handler, class);
    return error;
}

inst_error_t *init_class(prog_hand_t *prog_handler, class_t *class) {
    inst_error_t *error;
    if (class == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Initialise Static Function Handler
    error = init_static_handler(prog_handler, class);
    if (error != NULL) return error;

    // Initialise Non-Static Function Handler
    error = init_inst_handler(prog_handler, class);
    if (error != NULL) return error;

    // Initialise Class Variable Handler
    error = init_class_variables(prog_handler, class);
    if (error != NULL) return error;

    // Initialise Member Field Handler
    if (class->has_managed_data) {
        error = init_member_fields(prog_handler, class);
        if (error != NULL) return error;
    } else {
        class->mem_fields = NULL;
    }

    return NULL;
}

inst_error_t *add_function(prog_hand_t *prog_handler, class_t *class, function_t *function) {
    inst_error_t *error;
    if (class == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    error = fhand_add_function(prog_handler, class->inst_methods, function);
    return error;
}

inst_error_t *remove_function(prog_hand_t *prog_handler, class_t *class, function_t *function) {
    inst_error_t *error;
    if (class == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    error = fhand_remove_function(prog_handler, class->inst_methods, function->name, 
                                    function->param_types, function->param_count);
    return error;
}

inst_error_t *remove_function_by_name(prog_hand_t *prog_handler, class_t *class, char *name,
        class_t **param_types, int param_count) {
    inst_error_t *error;
    if (class == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    error = fhand_remove_function(prog_handler, class->inst_methods, name, param_types,
                                            param_count);
    return error;
}

inst_error_t *add_s_function(prog_hand_t *prog_handler, class_t *class, s_function_t *function) {
    inst_error_t *error;
    if (class == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    error = sfhand_add_function(prog_handler, class->static_methods, function);
    return error;
}

inst_error_t *remove_s_function(prog_hand_t *prog_handler, class_t *class, s_function_t *function) {
    inst_error_t *error;
    if (class == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    error = sfhand_remove_function(prog_handler, class->static_methods, function->name,
                                    function->param_types, function->param_count);
    return error;
}

inst_error_t *remove_s_function_by_name(prog_hand_t *prog_handler, class_t *class, char *name,
        class_t **param_types, int param_count) {
    inst_error_t *error;
    if (class == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    error = sfhand_remove_function(prog_handler, class->static_methods, name, param_types,
                                        param_count);
    return error;
}

inst_error_t *add_member_field(prog_hand_t *prog_handler, class_t *class, char *name,
        class_t *type) {
    inst_error_t *error;
    if (class == NULL || name == NULL || type == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Create member field
    var_desc_t *new_field = (var_desc_t *)malloc(sizeof(var_desc_t));
    if (new_field == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }
    new_field->name = (char *)malloc(strlen(name)*sizeof(char));
    if (new_field->name == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }
    strcpy(new_field->name, name);
    new_field->type = type;

    // Add member field
    error = add_var_desc(prog_handler, class->mem_fields, new_field);
    return error;
}

inst_error_t *remove_member_field(prog_hand_t *prog_handler, class_t *class, char *name) {
    inst_error_t *error;
    if (class == NULL || name == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    error = remove_var_desc_by_name(prog_handler, class->mem_fields, name);
}

inst_error_t *add_class_var(prog_hand_t *prog_handler, class_t *class, var_t *class_var) {
    inst_error_t *error;
    if (class == NULL || class_var == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    // Add class variable
    error = add_var(prog_handler, class->class_vars, class_var);
    return error;
}

inst_error_t *remove_class_var(prog_hand_t *prog_handler, class_t *class, char *name) {
    inst_error_t *error;
    if (class == NULL || name == NULL) {
        return new_error(prog_handler, "ErrInvalidParameters");
    }

    error = remove_var_by_name(prog_handler, class->class_vars, name);
}

/*
Initialises the Non-Static Function Handler for a given Class

*prog_handler: The program handler that contains the class and error handlers
*class: The class that the Non-Static Function Handler will be initialised for

Errors:
    ErrOutOfMemory: Thrown if there is not enough memory to create the Function Handler
*/
static inst_error_t *init_inst_handler(prog_hand_t *prog_handler, class_t *class) {
    inst_error_t *error;

    // Allocate methods
    funct_hand_t *inst_methods = (funct_hand_t *)malloc(sizeof(funct_hand_t));
    if (inst_methods == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }
    new_fhand(prog_handler, inst_methods);

    // Set class methods
    class->inst_methods = inst_methods;

    return NULL;
}

/*
Initialises the Static Function Handler for a given Class

*prog_handler: The program handler that contains the class and error handlers
*class: The class that the Static Function Handler will be initialised for

Errors:
    ErrOutOfMemory: Thrown if there is not enough memory to create the Function Handler
*/
static inst_error_t *init_static_handler(prog_hand_t *prog_handler, class_t *class) {
    inst_error_t *error;

    s_funct_hand_t *static_methods = (s_funct_hand_t *)malloc(sizeof(s_funct_hand_t));
    if (static_methods == NULL) {
        return new_error(prog_handler, "ErrOutOfMemory");
    }
    new_sfhand(prog_handler, static_methods);
    class->static_methods = static_methods;

    return NULL;
}

/*
Initialises the Variable Handler used for handling class variables for a given Class

*prog_handler: The program handler that contains the class and error handlers
*class: The class that the Variable Handler will be initialised for

Errors:
    ErrOutOfMemory: Thrown if there is not enough memory to create the Function Handler
*/
static inst_error_t *init_class_variables(prog_hand_t *prog_handler, class_t *class) {
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

/*
Initialises the Variable Description Handler used for handling member fields for a given Class

*prog_handler: The program handler that contains the class and error handlers
*class: The class that the Variable Description Handler will be initialised for

Errors:
    ErrOutOfMemory: Thrown if there is not enough memory to create the Function Handler
*/
static inst_error_t *init_member_fields(prog_hand_t *prog_handler, class_t *class) {
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