# Object-Orientated-Library

This library provides object-orientated functionality to C by implementing various common features in other languages

## Features

### Functions

<u>Description</u>

Functions are managed using a function handler which is unique for each individual class. The function handler contains multiple function sets which contain all functions within that class with the same name, however with different parameters. The (Static) Function Set is not designed to be modified by the end user as all interactions should be done primarily through the function handler in the class.

<u>Features</u>

* Functions can be defined as Static or Non-Static. Static Functions do not require an instance in order to be run and can be run once the class has been initialised. Non-Static functions will pass through the instance that calls it as a separate parameter which can be modified, etc.
* Overloading of functions allows for functions to have the same name but different parameters
* Functions may be "inherited" from parent classes thereby allowing child classes to have access to all parent classes
* Functions that are "inherited" may be overridden by adding a function that contains the same unique characteristics to a child class

### Classes

<u>Description</u>

Classes within the program can have multiple features used to identify them and can be added to the program handler for later reference using strings to get the class name. Classes that inherit from a parent class may be used in functions that reference the parent class provided that the data is managed using the Variable Handler. These classes that have managed data may inherit all features of the parent class and therefore can be referenced as normal within functions

<u>Features</u>

* Classes are identified using strings and may be retrieved or stored within the program handler which is used to manage classes
* Instances of the class with Managed data (using the Variable Handler) may have their member fields inherited by child classes and also allow child classes to fit parameters which typically use the parent's class
* Classes may have either Static methods of Non-Static methods. Each are distinct from each other and therefore may be defined with the same unique function features
  * Static methods are run using the class and do not require an instance to be run
  * Non-Static methods pass in the instance that called them as a separate parameter that may be modified
* All Classes inherit Class Variables and Static and Non-Static Functions allowing all child classes to have access to the same set of data. Classes whose parents also have Managed data may inherit Member Fields from those classes and may be used as a parameter that typically requires their parent type.
* Class variables and Member fields are distinct allowing them to have the same identifiers such as name, etc

### Variables

<u>Description</u>

Variables are the primary objects used by end users, holding the relevant member fields and functions relevant for each Class of Variable. Variables contain the data used to classify that variable as well as a description used to describe them via a unique name and class. The type of data a variable can hold depends on whether its data is Managed or Unmanaged and also based upon its class and parent classes

<u>Features</u>

* Variables that are reinitialised will free any allocated memory that was used by the previous variable type
* Variables have a description with a name and type allowing them to be identified using these two descriptors. These descriptors are typically initialised first before the variable itself is initialised
* Variables may have data that can be considered as either Managed or Unmanaged
  * Managed data is managed using the Variable Handler allowing for all child classes to inherit member fields from parent classes
  * Unmanaged data can have data in any format, including using standard C structs but cannot be inherited

### Error-Handling

<u>Description</u>

Errors are handled throughout the program, as all functions excluding those used to free memory (as no errors should be produced) or those used to handle the errors themselves. When an error occurs, the error should be immediately managed by the `handle_err` function. This function will handle the error by either looking through the error handler to see if it has been marked for catchment by an external function or whether to crash the program with a suitable error message.

<u>Features</u>

* Errors may be thrown by using the `new_error` function to automatically throw and handle the error
* Errors that occur throughout the program may be marked to be caught beforehand by a function and will not crash the program. These error instances will be passed back to the original function where they were initially marked assuming error handled is managed appropriately
* Errors have messages which may be used to format the string that is produced when the program crashes
* Error types may be extended by developers who wish to create their own versions of errors

### Handlers

<u>Description</u>

The handlers are the features primarily used by developers wishing to use already existing types to design their own programs. There are six main types of handlers, however the program handler with its associated class and error handlers are those most used by those wishing to develop code from existing type definitions

<u>Handler Types</u>

* Program Handler
  * This is the primary handler for the entire program and contains the class handler and error handler. The program handler should typically be passed into all functions, particularly those with management of errors
* Class Handler
  * This stores the classes used throughout the program and is the main point of reference when getting a class type
  * Classes can be retrieved from the handler based upon their names. Classes within the handler must have unique names
* Error Handler
  * This handles the management of errors within the program. Errors may be added to the error handler in order to mark them for being caught rather than crashing the program
  * Any errors which do not occur should be removed from the handler manually as the Error Handler will continue to allow errors of that type
* Static and Non-Static Function Handlers
  * These hold the functions used within classes however are not referenced by end users or developers
* Variable Description Handler
  * The variable description handler is primarily used in classes to define the member fields for each instance of that class
  * This is a collection of named variables with a type however they do not have data, thereby allowing them to essentially be treated as uninitialised variables
* Variable Handler
  * This is used to handle a collection of identifiable variables based upon their names such as managing instance variables in instances and class variables in Classes

### Package Creation

<u>Description</u>

Developers who wish to create their own package containing multiple types that may be used by end-users may do so by providing header files that may be used as so called 'packages' that may be imported.

<u>Features</u>

* Easy importing of packages allows for easy use by end-users after a package has been made
* Structured manner of packages allows for dependencies to be specified by packages
* Creation of types is unrestricted however, it is recommended that all types ultimately inherit from Object and preferably use the existing Variable Handler to manage member fields to allow for inheritance of child classes
* Development of types may rely on features from other classes that have not been initialised yet (however they must be present within the class handler)
* Common functions allow for simpler development of classes
* Methods and Class Variables from parent classes do not need to be created due to automatic inheritance however methods may be overwritten

# Instructions for Use

The instructions for use describe how you can use existing types that are developed.

## Setting Up The Environment

In order to include packages into the program, a header file containing the relevant decorative type definitions, relevant function prototypes and an import function should be included in the project. When using packages, it is recommended to create a dedicated package folder in which all packages and their required dependencies are placed into. From there, the 

<u>Commands</u>

* `import_package_name` - This function is the typical function name that is used to import a package by creating the new classes and initialising relevant classes

## Functions

Functions within the program provide a way of describing a type of function within a function set that describes the parameters, return types and names.

<u>Unique Identifiers</u>

Multiple definitions of similar functions may exist provided that the function interpreter can differentiate them based upon a set of unique factors. When running a function, various aspects described below must be specified in order to identify the function:

* Function Names
* Parameters

Additionally, Static and Non-Static functions are distinct from each other, allowing two functions within a class to have the same function names and parameters however differing by Static vs Non-Static.

<u>Commands</u>

* `run_function` - Used to run a Non-Static Function for an instance
* `run_super_function` - Used to run a Non-Static Function for an instance using the definition from a parent class
* `run_s_function` - Used to run a Static Function
* `run_super_s_function` - Used to run a Static Function for an instance using the definition from a parent class
* `get_return_type` - Used to get the return type of a function
* `get_super_return_type` - Used to get the return type of a function as defined by a parent class
* `get_s_return_type` - Used to get the return type of a static function
* `get_super_s_return_type` - Used to get the return type of a static function as defined by a parent class

## Classes

Classes are initialised automatically when importing a package and are typically referenced primarily when creating new instances. For the end-user, this is their primary use as well as to get a class variable.

<u>Commands</u>

* `get_class` - Used to get the class from the class handler, not necessary for most things throughout the program
* `get_class_var` - Used to get the class variable from a class
* `get_parent` - Used to get the parent class of a specified class

## Variables

Variables must undergo two methods of initialisation in order to be ready for use. When a variable has memory allocated for it, the variable must be first reset by having all it's initial values set to default. Once this has been done, the description of the variable must be next initialised followed by the variable itself. By initialising the description first, it allows for the classification of the name and type that the variable will use when initialising itself. Both the description and variable itself can be reinitialised, or set back to default by simply calling their respective functions. Note that if the variable class is changed by reinitialising the description, the variable must also be reinitialised in order to function correctly.

<u>Commands</u>

* `free_var` - Used to free the memory associated with a variable without checking references elsewhere in the program
* `new_var` - Used to reset the values of a variable and automatically allocate memory for the variable description
* `set_var_desc` - Used to set the description of a variable by its name and class to be used when initialising the variable itself
* `init_var` - The primary method used to initialise a new variable by running the relevant constructor to construct the variable
* `init_var_exact` - An alternate way to initialise variables with unmanaged data. This is an unchecked function and will *copy* the data passed in directly into the variable and should be used carefully to prevent data corruption.
* `get_member_field` - Used to get a pointer to the specified member field from variables with managed data
* `get_data` - Used to get a pointer to the data within a variable with unmanaged data
* `get_type` - Used to get the variable's type
* `get_var_name` - Used to get the variable's name by copying the variable's name to a new character array. Note memory allocation is done automatically for this.

## Error Handling

The program allows for the correct handling of errors for most functions used throughout the program and can be a useful way to test for functions that fail for a variety of reasons. Errors that are not added to the error handler will crash the program and print a message about what caused the error to occur in the first place. Errors that aren't handled have the ability to show a message that should describe the method that they were thrown in and the parent function

<u>Commands</u>

* `add_err` - Used to mark an error class to prevent crashing the program
* `remove_err` - Used to unmark an error. This should be used if a different error was produced
* `compare_err` - Used to compare the produced error from the expected error

<u>Correct Error Handling</u>

Correct error handling can add some additional lines, however it allows for the detection of errors at any level within the stack. The example below shows an example where `function()` is a type of function that supports error handling.

```c
// Example where an error is not expected to occur
inst_error_t *func() {
    ... // Code beforehand
    error = function();
    if (error != NULL) return error;
    ... // Rest of code
    return NULL; // Indicate that function completed successfully
}

// Example where an error is expected to occur
inst_error_t *func2() {
    ... // Code beforehand
    error = add_err(prog_handler, "ErrorName");
    if (error != NULL) return error;
    error = function();
    if (err_is_equal(error, "ErrorName")) {
        ... // Code when error occurs
    } else if (error != NULL) {
        remove_err(prog_handler, "ErrorName");
        return error;
    } else {
        
    }
    ... // Rest of code
    return NULL; // Indicate that function completed successfully
}
```

# Package Creation

Packages may be created by developers who wish to create their own types and allow for the easy implementation of their packages into the program handler

## Setting Up a Package

In order to create a package that can be imported, various sections must be maintained. Different contexts for a package may be used by creating multiple header files used for different contexts. Note that it may be helpful to develop independent packages to prevent type clashes depending on the contexts

## Type Creation

When creating types, only two main files are required, being the header file containing information about the type as well as function prototypes used to create and initialise the type class. When naming files, the header and C file should be named '_t\_<typename>.h_'  and '_t\_<typename>.c_' where '_<typename>_' is replaced with the name of the type. Template files may be seen in the '_example-package_' folder.

### Classes

Classes are the main containers used to hold all the features when creating a type. The class files are used to hold all information about a type as well as the functions used to create and initialise the type. The structure used in the example package should be followed when creating classes. In addition to the End User commands, there are a set of developer commands, primarily used to add classes to the program handler. When creating classes/adding them to the class handler, a check should first be done to see if the class already exists, and if so, to not recreate it.

_Note: Classes that use Unmanaged data should override the 'reset_data' non-static function provided by the Object class by default. Other classes will automatically use the Object implementation unless overridden_

<u>Commands</u>

* `new_class` - Used to create a new class with the specified details and add it to the program handler automatically
* `class_exists` - Used to test if the class already exists within the class handler
* `init_class` - Initialises the member fields handler, class variable handler, function and static function handler

### Functions

When developing specific functions that the function type points to, the exact number of parameters does not need to be specified as the function should know exactly how many parameters to expect. These functions can then be added to a class using the Class's function handler or during the process of creating a class. The structure used when creating functions that are to be referenced can be seen in '_t_CustomVar.c_' in the 'example-package' folder.

<u>Commands</u>

* `new_function` - Used to create a new function that can be added to a class

* `new_s_function` - Used to create a new static function that can be added to a class
* `add_function` - Used to add a function to a class
* `remove_function` - Used to remove a function from the class
* `remove_function_by_name` - Used to remove a function using its property descriptors from the class
* `add_s_function` - Used to add a static function to a class
* `remove_s_function` - Used to remove a function from the class
* `remove_s_function_by_name` - Used to remove a function using its property descriptors from the class

### Member Variables

The member variables are the variables that are used within an individual and can be added to classes with relative ease.

<u>Commands</u>

* `add_member_field` - Used to add a member field to a class
* `remove_member_field` - Used to remove a member field from a class

### Class Variables

The class variables are shared by all members of the class and can be added similar to member variables however the entire variable is added. This allows for the initial state for class variables to be determined prior to a class being added

<u>Commands</u>

* `add_class_var` - Used to add a class variable to the class
* `remove_class_var` - Used to remove the given class variable from the class

### Error Handling

Correct error handling is essential when creating all functions used in relation for type development as this allows for proper handling of errors throughout the problem and ensures that no issues go unresolved by the program. An example of proper error handling procedure may be seen in _Instructions for Use → Error Handling_. In addition, when a new error should be raised, the function should use a similar format to the example code below

```c
if (variable == NULL) {
    return new_error(prog_handler, <error_name>, <params>, <param_count>)
}
```

<u>Commands</u>

* `new_error` - Used to throw an error within the program. Will create and handle an error and then return a value that should be returned by the function that threw the error

# General Notes

Only the package files specified within package info should be included within the environment as specified by Instructions for Use.

Note that the project is not complete in its current state and will be unlikely to work as intended as it is at the moment
