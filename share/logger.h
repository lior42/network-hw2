#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Some nice logging function
static inline void logger(const char *message) {
    time_t now;
    time(&now);
    char *tmp = ctime(&now);
    tmp[strlen(tmp) - 1] = 0;

    printf("[%s]\t %s\n", tmp, message);
}
