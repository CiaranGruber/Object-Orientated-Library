/*
Variable Test Code
By Ciaran Gruber

Used to test the generic variable data

Todo: Restructure code format to present main section as a standalone package
Todo: Add package handler in program handler in order to identify packages that are imported
        - Create new error class for when packages are invalid
Todo: Add functions to get class variables
Todo: Allow for functions to be run with the "super" identifier used to get the parent function
Todo: When freeing member fields, also free their data correctly if they use a variable handler
Todo: Format return variables before running function

When discussing, should I add a locked value to classes that occurs after a package is imported as
it would protect from viruses, etc, or is this not needed?
*/

#include <stdio.h>
#include <string.h>
#include "./lang-package/package-info/pkg_eu_lang.h"

void test_object();

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <test> <test_data>\n",argv[0]);
        printf("\tDo '%s help' for more information\n",argv[0]);
        return 1;
    }

    if (!strcmp(argv[1], "help")) {
        char *commands[] = { "help", "class" };
        printf("Available commands:\n");
        for (int i = 0; i < 2; i++) {
            printf("\t%s\n", commands[i]);
        }
    } else if (!strcmp(argv[1], "variable")) {
        if (argc == 3) {
            if (!strcmp(argv[2], "object")) {
                test_object();
                return 0;
            }
        }
        char *commands[] = { "(No data)", "integer" };
        printf("Available commands:\n");
        for (int i = 0; i < 2; i++) {
            printf("\tvariable %s\n", commands[i]);
        }
    } else {
        printf("Invalid command\n");
        printf("Usage: %s <test> <test_data>\n",argv[0]);
        printf("\tDo '%s help' for more information\n",argv[0]);
        return 1;
    }
    return 0;
}

void test_object() {
    prog_hand_t *program_handler;
    program_handler = new_lang_package();
    import_lang_package(program_handler);
}