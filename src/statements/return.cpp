#include <golite/return.h>
#include <golite/utils.h>
#include <sstream>
#include <golite/identifier.h>
#include <golite/primary_expression.h>
#include <golite/function.h>

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
        expression_->weedingPass();
    }
}

void golite::Return::typeCheck() {
    if(expression_) {
        TypeComponent* type_component = expression_->typeCheck();
        if(golite::Function::active_function->getTypeComponent()) {
            if(!golite::Function::active_function->getTypeComponent()->isCompatible(type_component)) {
                golite::Utils::error_message("Return expression is not compatible with the function type",
                                             expression_->getLine());
            }
        } else {
            golite::Utils::error_message(
                    "Return statement cannot contain an expression because the function type is void",
                    expression_->getLine());
        }
    } else {
        if(golite::Function::active_function->getTypeComponent()) {
            golite::Utils::error_message("Function declaration expects a type", getLine());
        }
    }
}