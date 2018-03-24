#include <iostream>
#include <golite/utils.h>
#include <sstream>

extern bool tokens_flag;

void golite::Utils::support_error(char *lex, int line) {
    std::stringstream ss;
    ss << "GoLite does not support '" << lex << "'";
    error_message(ss.str().c_str(), line);
}

void golite::Utils::error_message(std::basic_string<char, std::char_traits<char>, std::allocator<char>> msg, int line) {
    std::cerr << "Error: " << msg << " at line " << line << std::endl;
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

std::string golite::Utils::blockComment(std::vector<std::string> lines, int indent, int line) {
    if(line >= 0) {
        lines.push_back("Line " + std::to_string(line) + " in original code");
    }
    std::stringstream ss;
    ss << golite::Utils::indent(indent)<< "/**" << std::endl;
    for(std::string line : lines) {
        ss << golite::Utils::indent(indent) << " * " << line << std::endl;
    }
    ss << golite::Utils::indent(indent)<< " */";
    return ss.str();
}

std::string golite::Utils::codeNotGenerated(std::string code, int indent, int line) {
    return golite::Utils::blockComment({"CODE NOT GENERATED", "\n" + code}, indent, line);
}