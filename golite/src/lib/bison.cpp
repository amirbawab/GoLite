#include <golite/utils.h>
#include <golite/bison.h>
#include <iostream>

extern int yylineno;

void yyerror(const char *s) {
    std::cerr << "Error: " << s << " at line " << yylineno << std::endl;
    exit(golite::Utils::EXIT_ERROR);
}
