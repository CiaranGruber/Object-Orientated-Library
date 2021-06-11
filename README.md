# Object-Orientated-Library

This library provides object-orientated functionality to C by implementing various common features in other languages

## Features

### Functions
Functions are managed using a function handler which is unique for each individual class. The function handler contains multiple function sets which each contain functions that have the same name but different parameter requirements, therefore acting as function overloading. The Generic Function Set is not designed to be modified by the end user as all interactions should be done through the Function Handler within the class variable.

Functions should be created with the following template:
```C
inst_error_t *function_name(var_t *return_var, var_t **params) {
    ...
}
```
The var_t for the return_var can be of another type if it is known that the function will return a specific type. Additionally, the number of parameters does not need to be specified as the function should know exactly how many parameters to expect. These functions can then be added to a class using the Function Handler within a class or during the process of creating a class.

### Classes
Classes are currently designed such that they have functions and static member fields (of variable type) common to all instances of that class. Classes also allow for inheritance, thereby inheriting the ability to modify class variables and functions from parent classes. Each class has a fixed size due to greater simplification of variables

### Variables
Variables are small structures that contain a pointer to the class they are a part of as well as a void type data which can contain any value. This value can be a standard structure that is used in the class. The size of this structure is what should be used as the class size

### Error-Handling
All functions excluding functions used to free memory for functions, classes, etc, and the error-handling functions themselves return an error instance which will then be handled appropriately by the error handler by either causing the program to print an error statement and exit the program or merely get ignored, thereby allowing for an implementation of try... catch... statements where the developer can choose to allow an error to occur in the program, and after running the function, can detect if any relevant errors were raised

### Type Creation
When creating a type, there are various functions and structures which should be developed with the following template
* A typedef specific to the class to allow for greater distinction when specifying return types in functions
* A structure used to group member fields within instances of the type are created
* A function used to create a class of that type
* A function used to create the structure data specifically; or
* At least one constructor function added to a class that allows for input of parameters to create an instance
In addition, it may be recommended to override the standard functions "compare", "to_string", and "string_len" which are a part of the Object class. 

### General Notes
Direct changes to structures themselves are not necessary and therefore, all use of this program should be done using the functions that are provided by the program to prevent errors from occurring. Furthermore, all classes should be entered to the class handler to prevent issues regarding duplicate classes, etc.

Note that project is not complete in its current state and will be unlikely to work as intended as it is at the moment
