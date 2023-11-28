#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include "parse.h"
#include "pipes.h"
#include "cd.h"
#include "exit.h"
#include "redirect.h"
#include "err.h"

int main() {
    while (1) {
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
            char* lcopy = strdup(carr[j]);
            parse(carr[j], argArray);
            if (strcmp(carr[j], "exit")==0){
                exitCom(0);
            }
            if (strcmp(carr[j], "cd")==0){
                changeDir(argArray[1]);
            }
            if (strchr(lcopy, '|') != NULL){
                for (int k = 0; k<strlen(*argArray); k++){
                    if (strcmp(argArray[k-1], "|") ==0 && k-2 >= 0){
                        pipee(argArray[k-2], argArray[k], argArray);
                    }
                }
            }
            else {
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
        }
    }
    return 0;
}