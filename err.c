#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "err.h"

int err() {
    printf("errno: %d \n", errno);
    printf("%s \n", strerror(errno));
    exit(1);
}