#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include "pipes.h"
#include "err.h"

void pipee(char* in, char* out, char** arr){//pipe, redir, readme, textfile, comments, sigs
    FILE* p1;
    FILE* p2;
    int files[2];
    p1 = popen(in, "r");
    if (p1==NULL){
        err();
    }
    else{
        files[0]=fileno(p1);
    }
    int temp = open("tempfile", O_RDWR|O_TRUNC|O_CREAT, 600);
    p2 = popen(out, "w");
    if (p2==NULL){
        err();
    }
    else{
        files[1]=fileno(p2);
    }
    dup2(files[1], STDOUT_FILENO);//or files [1]
    execvp(in, arr);
    dup2(files[0], STDIN_FILENO);
    execvp(out, arr);
    pclose(p1);
    pclose(p2);
}