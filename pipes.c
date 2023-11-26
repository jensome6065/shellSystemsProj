#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "pipes.h"
#include "err.h"

void pipee(char* in, char* out){//or not void? should it return something
    FILE* p1;
    FILE* p2;
    int files[2];
    p1 = popen(in, "r");
    p2 = popen(out, "w");
    if (p1==NULL){
        err();
    }
    else{
        files[0]=fileno(p1);
    }
    if (p2==NULL){
        err();
    }
    else{
        files[0]=fileno(p2);
    }
    pclose(p1);
    pclose(p2);
}