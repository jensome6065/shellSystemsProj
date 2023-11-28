#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include "pipes.h"
#include "err.h"

void pipee(char* in, char* out, char** arr){//pipe, redir, readme, textfile, comments, sigs
    // FILE* temp = fopen("tempfile", "w+");//remember to remove
    FILE* p1;
    FILE* p2;
    p1 = popen(in, "w");
    if (p1==NULL){
        err();
    }                                                                 
    // char line [128];
    // while (fgets(line, sizeof line, p1)) {
    //     write(temp, line, sizeof(line));
    // }
    // sprintf(buffer,"Linux System call");
    p2 = popen(out, "w");
    if (p2==NULL){
        err();
    }      
    dup2(fileno(p2), STDOUT_FILENO);//STDOUT_FILENO, fileno(p2)); 
    execvp(in, arr);
    // fwrite(line,sizeof(char),strlen(line),p2);
    // dup2(temp, STDIN_FILENO); 
    dup2(fileno(p1), STDIN_FILENO);
    //dup2(fileno(p1), STDIN_FILENO);
    execvp(out, arr);
    // pclose(p1);
    // pclose(p2);
    // int stdoutdup = dup(STDOUT_FILENO);
    // execvp(in, arr);
    // execvp(out, arr);
    pclose(p1);
    pclose(p2);
    // dup2(stdoutdup, 1);
}