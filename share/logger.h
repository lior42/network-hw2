#ifndef LOGGER_H
#define LOGGER_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static inline void logger(const char* message) {
   time_t now;
   time(&now);
   printf("[%s] %s\n", ctime(&now), message);
}
#endif /* LOG_H */
