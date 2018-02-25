#include <golite/program.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Program::toGoLite() {
    std::stringstream ss;
    ss << "package " << "identifier" << ";" << std::endl;
    for(Declarable* declarable : declarables_) {
        ss << declarable->toGoLite(0) << std::endl;
    }
    return ss.str();
}