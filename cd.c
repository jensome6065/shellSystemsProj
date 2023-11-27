#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cd.h"
#include "err.h"

void changedir(char* input) {
    if (input == NULL){
        input = "..";
    }
    if (chdir(input) != 0){
        err();
    }
    chdir(input);
}