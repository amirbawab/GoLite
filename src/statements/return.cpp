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
    // Type checking is done in hasReturn() method
}

void golite::Return::symbolTablePass(SymbolTable *root) {
    if(expression_) {
        this->expression_->symbolTablePass(root);
    }
}

bool golite::Return::hasReturn(Declarable *function) {
    if(expression_) {
        TypeComponent* type_component = expression_->typeCheck();
        if(!function->getTypeComponent()->isVoid()) {
            if(!function->getTypeComponent()->isCompatible(type_component)) {
                golite::Utils::error_message("Return expression type " + type_component->toGoLiteMin()
                                             + " is not compatible with the function type "
                                             + function->getTypeComponent()->toGoLiteMin(),
                                             expression_->getLine());
            }
        } else {
            golite::Utils::error_message(
                    "Return statement cannot have an expression because the function type is void",
                    expression_->getLine());
        }
    } else if(!function->getTypeComponent()->isVoid()) {
        golite::Utils::error_message("Function declaration expects a type "
                                     + function->getTypeComponent()->toGoLiteMin(), getLine());
    }
    return true;
}