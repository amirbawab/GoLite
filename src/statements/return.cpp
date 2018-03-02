#include <golite/return.h>
#include <golite/utils.h>
#include <sstream>
#include <golite/identifier.h>
#include <golite/primary_expression.h>

std::string golite::Return::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "return";
    if(expression_) {
        ss << " " << expression_->toGoLite(0);
    }
    ss << ";";
    return ss.str();
}

void golite::Return::weedingPass(bool, bool) {
    if(expression_) {
        if(expression_->isBlank()) {
            golite::Utils::error_message("A return statement cannot return a blank identifier", expression_->getLine());
        }
        expression_->weedingPass(false, false);
    }
}

golite::TypeComponent* golite::Return::typeCheck() {
    if(expression_) {
        expression_->typeCheck();
    }
    return nullptr;
}