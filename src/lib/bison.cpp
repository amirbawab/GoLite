#include <golite/utils.h>
#include <golite/bison.h>
#include <stdio.h>
#include <stdlib.h>

extern int yylineno;

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s at line %d\n", s, yylineno);
    exit(go::utils::EXIT_ERROR);
}
