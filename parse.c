#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include "parse.h"

int err() {
    printf("errno: %d \n", errno);
    printf("%s \n", strerror(errno));
    exit(1);
}

void parse(char* line, char** argArray) {
    char* token;
    int i = 0;
    while ((token = strsep(&line, " ")) != NULL) {
        if (*token != '\0') {
            argArray[i++] = token;
        }
    }
    argArray[i] = NULL;
}