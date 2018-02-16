#include <golite/utils.h>
#include <stdio.h>
#include <stdlib.h>

void go::utils::support_error(char *lex, int line) {
    fprintf(stderr, "GoLite does not support %s at line %d", lex, line);
    exit(EXIT_ERROR);
}
