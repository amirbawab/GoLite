#include <iostream>
#include <golite/utils.h>
#include <sstream>

extern bool tokens_flag;

void golite::Utils::support_error(char *lex, int line) {
    std::cerr << "Error: GoLite does not support '" << lex << "' at line " << line << std::endl;
    exit(EXIT_ERROR);
}

void golite::Utils::log_token(const char *lex, const char *val) {
    if(tokens_flag) {
        if(val) {
            std::cout << lex << "(" << val << ")" << std::endl;
        } else {
            std::cout << lex << std::endl;
        }
    }
}

std::string golite::Utils::indent(int val) {
    std::stringstream indent;
    for (size_t i = 0; i < val; i++) {
        indent << std::string(4, ' ');
    }
    return indent.str();
}
