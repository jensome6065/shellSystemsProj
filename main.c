#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include "parse.h"
#include "funcs.h"
#include "cd.h"
#include "exit.h"
#include "err.h"

int main() {
    char input[1024];
    char* argArray[64];
    char* check;
    char** carr = NULL;

    printf("enter a command: ");
    fgets(input, sizeof(input), stdin);
    char* ip = &input;
    if (input[strlen(input) - 1] == '\n') {
        input[strlen(input) - 1] = '\0';
    }
    int i = 0;
    while ((check = strsep(&ip, ";"))!=NULL){
        carr = (char**)realloc(carr, (i+1)*sizeof(char*));
        carr[i] = check;
        i++;
    }
    for (int j = 0; j<i; j++){
        parse(carr[j], argArray);
        execvp(carr[j], argArray);
    }
    //account for pipes and semicolons
    // parse(input, argArray);
    // execvp(argArray[0], argArray);
    
    return 0;
}