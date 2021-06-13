/*
Contains all typedefs used within the program. This is required in order to ensure correct
compilation.
By Ciaran Gruber

Typedef File - Header File
*/

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