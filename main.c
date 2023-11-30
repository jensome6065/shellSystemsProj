#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include "shell.h"
#include "pipes.h"
#include "redirect.h"
#include "err.h"

int main() {
    while (1) {
        char input[1024];
        char* argArray[64];
        char* check;
        char** carr = NULL;

        printf("command: ");
        fflush(stdout);
        fgets(input, sizeof(input), stdin);
        char* ip = input;
        printf("%s", input);

        if (input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0';
        }

        int i = 0;
        while ((check = strsep(&ip, ";"))!=NULL) {
            carr = (char**)realloc(carr, (i+1)*sizeof(char*));
            carr[i] = check;
            i++;
        }

        for (int j = 0; j<i; j++) {
            char* lcopy = strdup(carr[j]);
            parse(carr[j], argArray);
            if (strcmp(carr[j], "exit")==0) {
                exitCom();
                break;
            }
            else if (strcmp(carr[j], "cd")==0) {
                changeDir(argArray[1]);
            }
            else if (strchr(lcopy, '|') != NULL){
                // for (int k = 0; k<strlen(*argArray)+1; k++){
                //     if (strcmp(argArray[k-1], "|") ==0 && k-2 >= 0){
                //         pipee(argArray[k-2], argArray[k], argArray);
                //     }
                // }
                pipee(lcopy);
            }
            else if (strchr(lcopy, '<') != NULL || strchr(lcopy, '>') != NULL) {
                redirect(argArray[0], argArray);
            }
            else {
                pid_t child = fork();
                int status;
                if(child<0) {
                    err();
                } else if (child == 0) {
                    execvp(carr[j], argArray);
                    pid_t p = getpid();  
                } 
                waitpid(child, &status, 0);
            }
        }
    }
    return 0;
}