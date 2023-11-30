#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "shell.h"
#include "pipes.h"
#include "err.h"

void pipee(char* comm){
    char* part1;
    char* part2;
    char* copy = strdup(comm);
    char* argarr[30];
    char* argarr2[30];
    part1 = strsep(&comm, "|");
    if (part1[strlen(part1)-1]==' ') part1[strlen(part1)-1] = '\0';
    parse(part1, argarr);
    comm ++;
    part2 = comm;
    int temp = open("tempfile", O_RDWR | O_CREAT | O_TRUNC, 0777);
    if (temp == -1) {
        err();
    }
    int stdoutcopy = dup(STDOUT_FILENO);
    dup2(temp, STDOUT_FILENO);
    pid_t child = fork();
    int status;
    if(child<0) {
        err();
    } else if (child == 0) {
        if (execvp(part1, argarr)==-1) err();
    } 
    pid_t w = wait(&status);
    if(w==-1) err();
    parse(part2, argarr2);
    int i = 0;
    while(argarr2[i]!=NULL){
        i++;
    }
    argarr2[i] = "tempfile";
    argarr2[i+1] = NULL;
    dup2(stdoutcopy, STDOUT_FILENO);    
    pid_t child1 = fork();
    if(child1<0) {
        err();
    } else if (child1 == 0) {
        if (execvp(part2, argarr2)==-1) err();
    } 
    pid_t w1 = wait(&status);
    if(w1==-1) err();
    close(temp);
 }