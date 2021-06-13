/*
Variable Test Code
By Ciaran Gruber

Used to test the generic variable data
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./program-handlers/program-handler/program_handler.h"
#include "./types/Object/t_Object.h"
#include "./types/Integer/t_Integer.h"

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
    prog_hand_t *program_handler = (prog_hand_t *)malloc(sizeof(prog_hand_t));
    init_prog_hand(program_handler);
    new_object_cls(program_handler);
    new_integer_cls(program_handler);
    // new_err_function_not_defined_cls(program_handler);
    // Below is example of producing an error (will currently loop due to missing error classes)
    new_integer_cls(program_handler);
    init_integer_cls(program_handler);
}