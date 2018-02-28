#include <golite/program.h>
#include <golite/utils.h>
#include <sstream>
#include <golite/function.h>
#include <golite/variable.h>

std::string golite::Program::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent)<< "package " << package_name_->toGoLite(0) << ";" << std::endl;
    for(Declarable* declarable : declarables_) {
        ss << std::endl << declarable->toGoLite(indent);
    }
    return ss.str();
}

void golite::Program::weedingPass() {
    if(package_name_->isBlank()) {
        golite::Utils::error_message("Package name cannot be a blank identifier", package_name_->getLine());
    }

    for(Declarable* declarable : declarables_) {
        declarable->weedingPass(true, true);
    }
}
