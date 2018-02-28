#include <golite/type.h>
#include <sstream>
#include <golite/utils.h>

std::string golite::Type::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "type " << identifier_->toGoLite(0) << " "
       << type_component_->toGoLite(indent) << ";";
    return ss.str();
}

int golite::Type::getLine() {
    return identifier_->getLine();
}

void golite::Type::weedingPass(bool check_break, bool check_continue) {
    identifier_->weedingPass(check_break, check_continue);
    type_component_->weedingPass(check_break, check_continue);
}