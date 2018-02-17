#include <stdio.h>
#include <stdlib.h>
#include <golite/utils.h>

void golite::Utils::support_error(char *lex, int line) {
    fprintf(stderr, "GoLite does not support %s at line %d", lex, line);
    exit(EXIT_ERROR);
}
