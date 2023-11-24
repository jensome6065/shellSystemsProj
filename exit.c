#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exit.h"
#include "err.h"

void exitCom(int exitstatus) {
    if (exitstatus==0){
        printf("exiting normally\n");
        exit(0);
    }
    else exit(1);
}