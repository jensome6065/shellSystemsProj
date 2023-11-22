#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cd.h"
#include "err.h"

void chDir(char* input) {
    char oldDir[1024];

    if (getcwd(oldDir, sizeof(oldDir)) == NULL) {
        err();
    }

    if (strcmp(input, "cd") == 0 || strcmp(input, "cd ") == 0) {
        fprintf(stderr, "cd: missing argument \n");
        err();
    } 
    else {
        if (strcmp(input, "-") == 0) {
            char* prevDir = getenv("oldDir");
            if (prevDir != NULL) {
                if (chdir(prevDir) != 0) {
                    err();
                }
                if (setenv("oldDir", oldDir, 1) != 0) {
                    err();
                }
            } 
            else {
                fprintf(stderr, "cd: oldDir not set \n");
                err();
            }
        } 
        else if (chdir(input) != 0) {
            if (input[0] == '~') {
                char* home = getenv("HOME");
                if (home != NULL) {
                    char path[1024];
                    snprintf(path, sizeof(path), "%s/%s", home, input + 1);
                    if (chdir(path) != 0) {
                        err();
                    }
                } 
                else {
                    fprintf(stderr, "cd: unable to determine home directory\n");
                    err();
                }
            } 
            else if (input[0] == '/') { 
                if (chdir(input) != 0) {
                    err();
                }
            } 
            else { 
                char cwd[1024];
                if (getcwd(cwd, sizeof(cwd)) != NULL) {
                    char path[1024];
                    snprintf(path, sizeof(path), "%s/%s", cwd, input);
                    if (chdir(path) != 0) {
                        err();
                    }
                } 
                else {
                    err();
                }
            }
            if (setenv("oldDir", oldDir, 1) != 0) {
                err();
            }
        }
    }
}