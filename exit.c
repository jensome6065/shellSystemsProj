#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exit.h"
#include "err.h"

void exitCom(int exitstatus) {
    if (exitstatus==0){
        printf("exiting\n");
        exit(0);
    }
}