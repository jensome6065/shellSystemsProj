#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include "parse.h"
#include "funcs.h"
#include "pipes.h"
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
        if (strcmp(carr[j], "exit")==0){
            exitCom(0);
        }
        if (strcmp(carr[j-1], "|")==0){//then use carr[j-2] and carr[j] excluding edg
            if (j-2>=0){
                pipee(carr[j-2], carr[j]);
            }
        }
        if (strcmp(carr[j], "cd")==0){
        }
        pid_t child = fork();
        pid_t w = NULL;
        int status;
        if(child<0){
            err();
        } else if (child == 0){
            execvp(carr[j], argArray);
            pid_t p = getpid();
            w = wait(&status);
        } 
        waitpid(w, &status, 0);
    }
    
    return 0;
}