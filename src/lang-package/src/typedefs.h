/*
Contains all typedefs used within the program. This is required in order to ensure correct
compilation.
By Ciaran Gruber

Typedef File - Header File
*/

#ifndef TYPEDEFS
#define TYPEDEFS

#include <stdlib.h>
#include <stdbool.h>

/* A node in the Variable Description Handler that contains a Variable Description and a link to
the next node */
typedef struct var_desc_hand_node var_desc_hand_node_t;
/* A node in the Error Handler that contains an allowed error and a link to the next node */
typedef struct err_hand_node err_hand_node_t;
/* A node in the Class Handler that contains a class and a link to the next node */
typedef struct class_node class_node_t;
/* A node in the Function Handler that contains a function set and a link to the next node */
typedef struct funct_hand_node funct_hand_node_t;
/* A node in the Static Function Handler that contains a function set and a link to the next node */
typedef struct s_funct_hand_node s_funct_hand_node_t;
/* A node in the Variable Handler that contains a Variable and a link to the next node */
typedef struct var_hand_node var_hand_node_t;

/* A structure containing all the handlers required for the program */
typedef struct gen_prog_hand prog_hand_t;
/* A structure that holds the various features contained in a Static Function */
typedef struct gen_s_function s_function_t;
/* A structure that holds the various features contained in a Static Function Set */
typedef struct gen_s_function_set s_function_set_t;
/* A structure that holds the function sets contained in a Static Function Handler */
typedef struct gen_s_funct_hand s_funct_hand_t;
/* A structure that holds the various features contained in a Function */
typedef struct gen_function function_t;
/* A structure that holds the various features contained in a Function Set */
typedef struct gen_function_set function_set_t;
/* A structure that holds the function sets contained in a Function Handler */
typedef struct gen_funct_hand funct_hand_t;
/* A structure that holds the various features contained in a Class */
typedef struct gen_class class_t;
/* A structure that holds the various features contained in a Variable */
typedef struct gen_var var_t;
/* A structure that holds the various features contained in a Variable Description */
typedef struct gen_var_desc var_desc_t;
/* A structure that holds the classes contained in a Class Handler */
typedef struct gen_class_hand cls_hand_t;
/* A structure that holds the allowed errors contained in a Error Handler */
typedef struct gen_err_hand err_hand_t;
/* A structure that holds the Variables contained in a Variable Handler */
typedef struct gen_var_hand var_hand_t;
/* A structure that holds the Variable Descriptions contained in a Variable Description Handler */
typedef struct gen_var_desc_hand var_desc_hand_t;

/* A type of variable used to represent an Error instance */
typedef var_t inst_error_t;
/* A type of class used to represent an Error class */
typedef class_t cls_error_t;
/* A type of variable used to represent an Object instance */
typedef var_t inst_object_t;
/* A type of class used to represent an Object class */
typedef class_t cls_object_t;

/* A node in the Class Handler that contains a class and a link to the next node */
struct class_node {
    class_t *class;     // The class contained within the node
    class_node_t *next; // The next node in the Class Handler
};

/* A structure that holds the classes contained in a Class Handler */
struct gen_class_hand {
    class_node_t *first; // The first class node in the Class Handler
};

/* A node in the Error Handler that contains an allowed error and a link to the next node */
struct err_hand_node {
    cls_error_t *allowed_error; // The error that is allowed as part of the Error Handler
    err_hand_node_t *next;      // A pointer to the next node in the Error Handler
};

/* A structure that holds the allowed errors contained in a Error Handler */
struct gen_err_hand {
    err_hand_node_t *first; // A pointer to the first node in the Error Handler
};

/* A node in the Function Handler that contains a function set and a link to the next node */
struct funct_hand_node {
    function_set_t *function_set;    // The function set contained within the node
    funct_hand_node_t *next;       // The next node in the Function Handler
};

/* A structure that holds the function sets contained in a Function Handler */
struct gen_funct_hand {
    funct_hand_node_t *first;
};

/* A node in the Static Function Handler that contains a function set and a link to the next node */
struct s_funct_hand_node {
    s_function_set_t *function_set;    // The function set contained within the node
    s_funct_hand_node_t *next;       // The next node in the Static Function Handler
};

/* A structure that holds the function sets contained in a Static Function Handler */
struct gen_s_funct_hand {
    s_funct_hand_node_t *first;
};

/* A node in the Variable Handler that contains a variable and a link to the next node */
struct var_hand_node {
    var_t *variable;       // The Variable contained within the node
    var_hand_node_t *next; // The next node in the Variable Handler
};

/* A structure that holds the Variables contained in a Variable Handler */
struct gen_var_hand {
    var_hand_node_t *first; // The first node in the Variable Handler
};

/* A node in the Variable Description Handler that contains a Variable Description and a link to
the next node */
struct var_desc_hand_node {
    var_desc_t *var_desc;       // The Variable Description contained within the node
    var_desc_hand_node_t *next; // The next node in the Variable Description Handler
};

/* A structure that holds the Variable Descriptions contained in a Variable Description Handler */
struct gen_var_desc_hand {
    var_desc_hand_node_t *first; // The first node in the Variable Handler
};

/* A structure that holds the various features contained in a Class */
struct gen_class {
    char *class_name;             // A string representing the type
    /*
    A boolean value representing whether an instance of the class has instance variables or
    unstructured data

    Note:
    Most class will set this to true. Variables who inherit only from Object and do not represent
    their data as a variable handler should be the only ones that have this set to 'true'.
    Furthermore, classes who do not have their data managed with a variable handler may not be used
    as a parameter in functions as the variable may not have the members fields called for in a
    function
    */
    bool has_managed_data;
    size_t size;                    // An integer representing the size of the variable
    class_t *parent;                // The parent Class which this class inherits from
    s_funct_hand_t *static_methods; // The function handler for the class
    funct_hand_t *inst_methods;     // The method handler for instances of the class
    var_hand_t *class_vars;         // The variables shared by all members of the class
    var_desc_hand_t *mem_fields;    // The member fields in instances of this class
};

/* A structure that holds the various features contained in a Variable */
struct gen_var {
    var_desc_t *desc; // The description of the variable with key features within the variable
    void *data;       // The data in bytes used to represent the variable
    bool initialised; // Whether the data has been initialised or not
};

/* A structure that holds the various features contained in a Variable */
struct gen_var_desc {
    class_t *type;    // A reference to the type used to represent a variable
    char *name;       // The name that is unique to the variable within its scope
    bool initialised; // A boolean representing whether the variable has been initialised yet
};

/* A structure that holds the various features contained in a Function */
struct gen_function {
    char *name;            // The name of the Function
    /* 
    A pointer to the related function that is run

    Parameters:
    prog_hand_t *: The program handler that holds the class and error handlers
    var_t *: The variable that is being modified by the function
    var_t *: The variable that the function returns
    var_t **: The parameters that the function uses - Number of parameters is constant
    */
    inst_error_t *(*function)(prog_hand_t *, var_t *, var_t *, var_t **);
    class_t *return_type;  // The return type of the function
    class_t **param_types; // The functions used for each of the parameters
    int param_count;       // The number of parameters in the Function
};

/* A structure that holds the various features contained in a Static Function */
struct gen_s_function {
    char *name;            // The name of the Static Function
    /* 
    A pointer to the related function that is run

    Parameters:
    prog_hand_t *: The program handler that holds the class and error handlers
    var_t *: The variable that the function returns
    var_t **: The parameters that the function uses - Number of parameters is constant
    */
    inst_error_t *(*function)(prog_hand_t *, var_t *, var_t **); 
    class_t *return_type;  // The return type of the function
    class_t **param_types; // The functions used for each of the parameters
    int param_count;       // The number of parameters in the Static Function
};

#endif