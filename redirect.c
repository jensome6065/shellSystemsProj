#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"
#include "redirect.h"
#include "err.h"

void redirect(char* command, char** args) {
    int input = -1; 
    int output = -1;
    int stdincopy = dup(STDIN_FILENO);
    int stdoutcopy = dup(STDOUT_FILENO);
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "<") == 0) {
            FILE* file = fopen(args[i + 1], "r");
            if (file == NULL) {
                err();
            }

            char buffer[1024];
            if (fgets(buffer, sizeof(buffer), file) != NULL) {
                rewind(file);
                input = fileno(file);
                dup2(input, STDIN_FILENO);
                args[i] = NULL;
                args[i + 1] = NULL;
            }
            else {
                fclose(file);
                exitCom();
            }
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
    
    if (execvp(command, args) == -1) {
        err();
    }
    dup2(stdincopy, STDIN_FILENO);
    dup2(stdoutcopy, STDOUT_FILENO);
}