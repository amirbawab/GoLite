#include <golite/scope/program.h>

using namespace golite;

Program::Program() {
    // TODO: add the built-in types into the symbol table
}

void Program::setPackageName(string package_name) {
    this->package_name_ = package_name;
}

