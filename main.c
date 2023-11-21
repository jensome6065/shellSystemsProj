#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include "parse.h"
#include "funcs.h"

int main() {
    char input[1024];
    char* argArray[64];

    printf("enter a command: ");
    fgets(input, sizeof(input), stdin);

    if (input[strlen(input) - 1] == '\n') {
        input[strlen(input) - 1] = '\0';
    }
    
    parse(input, argArray);
    printf("parsed: \n");
    for (int i = 0; argArray[i] != NULL; i++) {
        printf("%s \n", argArray[i]);
    }
    
    return 0;
}