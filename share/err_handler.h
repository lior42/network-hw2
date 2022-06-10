#pragma once

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef ERRS_ON_STDERR
#define HW2_SHARE_ERR_OUTPUT stdout
#else
#define HW2_SHARE_ERR_OUTPUT stderr
#endif

static inline void validate_or_die(bool cond, const char *fail_message, ...) {
    if (!cond) {
        va_list ap;
        va_start(ap, fail_message);
        vfprintf(HW2_SHARE_ERR_OUTPUT, fail_message, ap);
        va_end(ap);
        fprintf(HW2_SHARE_ERR_OUTPUT, "\n");
        exit(EXIT_FAILURE);
    }
}

#undef HW2_SHARE_ERR_OUTPUT