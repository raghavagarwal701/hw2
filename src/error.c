#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

int error_s;
int warning_s;
int dbflag = 1;

void fatal(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    fprintf(stderr, "\nFatal error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");

    va_end(args);
    exit(1);
}

void error(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    fprintf(stderr, "\nError: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");

    va_end(args);
    error_s++;
}

void warning(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    fprintf(stderr, "\nWarning: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");

    va_end(args);
    warning_s++;
}

void debug(char *fmt, ...) {
    if (!dbflag)
        return;

    va_list args;
    va_start(args, fmt);

    fprintf(stderr, "\nDebug: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");

    va_end(args);
}
