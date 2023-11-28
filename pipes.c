#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include "pipes.h"
#include "err.h"

void pipee(char* in, char* out, char** arr){//pipe, redir, readme, textfile, comments, sigs
    int temp = open("tempfile", O_RDWR|O_CREAT|O_TRUNC, 600);
    FILE* p1;
    FILE* p2;
    p1 = popen(in, "r");
    if (p1==NULL){
        err();
    }                                                                  
    char line [128];
    while (fgets(line, sizeof line, p1)) {
        write(temp, line, sizeof(line));
    }
    p2 = popen(out, "w");
    if (p2==NULL){
        err();
    }      
    dup2(temp, STDIN_FILENO); 
    // dup2(fileno(p1), STDOUT_FILENO);
    // execvp(in, arr);
    // dup2(fileno(p2), STDIN_FILENO);
    // execvp(out, arr);
    // pclose(p1);
    // pclose(p2);
    // int stdoutdup = dup(STDOUT_FILENO);
    // dup2(files[1], STDOUT_FILENO);
    // dup2(files[0], STDIN_FILENO);
    // execvp(in, arr);
    execvp(out, arr);
    pclose(p1);
    pclose(p2);
    // dup2(stdoutdup, 1);
}