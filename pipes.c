#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "parse.h"
#include "pipes.h"
#include "err.h"

void pipee(char* comm){//pipe, redir, readme, textfile, comments, sigs
    char* part1;
    char* part2;
    char* copy = strdup(comm);
    char* argarr[30];
    part1 = strsep(&comm, "|");
    if (part1[strlen(part1)-1]==' ') part1[strlen(part1)-1] = '\0';
    parse(part1, argarr);
    comm ++;
    part2 = comm;
    int temp = open("tempfile", O_RDWR | O_CREAT | O_TRUNC, 0777);//rem to remove
    if (temp == -1) {
        err();
    }
    int stdoutcopy = dup(STDOUT_FILENO);
    dup2(temp, STDOUT_FILENO);
    pid_t child = fork();
    //pid_t w = 0;
    int status;
    if(child<0) {
        err();
    } else if (child == 0) {//program that sleeps and outputs text
        if (execvp(part1, argarr)==-1) err();
        // else w=getpid();
        // w = wait(&status);
        // if(w==-1) err();
    } 
    //waitpid(child, &status, 0);
    parse(part2, argarr);
    dup2(stdoutcopy, STDOUT_FILENO);    
    int stdincopy = dup(STDIN_FILENO);
    dup2(temp, STDIN_FILENO);
    child = fork();
    if(child<0) {
        err();
    } else if (child == 0) {
        if (execvp(part2, argarr)==-1) err();
        // else w=getpid();
        // w = wait(&status);
        // if(w==-1) err();
    } 
    // waitpid(child, &status, 0); 
    // pid_t w = wait(&status);
    // if(w==-1) err();
    dup2(stdincopy, STDIN_FILENO);
    close(temp);
 }