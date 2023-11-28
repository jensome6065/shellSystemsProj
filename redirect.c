#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "redirect.h"
#include "err.h"

void redirect(char* command, char** args) {
    int input = -1; 
    int output = -1;
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "<") == 0) {
            input = open(args[i + 1], O_RDONLY);
            if (input == -1) {
                err();
            }
            dup2(input, STDIN_FILENO);
            close(input);
            args[i] = NULL;
            args[i + 1] = NULL;
        }
        else if (strcmp(args[i], ">") == 0) {
            output = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (output == -1) {
                err();
            }
            dup2(output, STDOUT_FILENO);
            close(output);
            args[i] = NULL;
            args[i + 1] = NULL;
        }
    }
    execvp(command, args);
    err();
}