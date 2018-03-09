#include <golite/inc_dec.h>
#include <golite/utils.h>
#include <sstream>
#include <golite/identifier.h>
#include <golite/primary_expression.h>

std::string golite::IncDec::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << expression_->toGoLite(0);
    if(isIncrement()) {
        ss << "++";
    } else {
        ss << "--";
    }
    return ss.str();
}

int golite::IncDec::getLine() {
    return expression_->getLine();
}

void golite::IncDec::weedingPass(bool, bool) {
    if(expression_->isBlank()) {
        golite::Utils::error_message("Increment and decrement statement cannot have a blank expression",
                                     expression_->getLine());
    }
    expression_->weedingPass();
}

void golite::IncDec::typeCheck() {
    TypeComponent* expression_type = expression_->typeCheck();
    // TODO Verify it's an identifier
    if(!expression_type->isInt()) {
        golite::Utils::error_message("Increment and decrement statement expect an integer expression but given "
                                     + expression_type->toGoLiteMin(), expression_->getLine());
    }
}

void golite::IncDec::symbolTablePass(SymbolTable *root) {
    this->expression_->symbolTablePass(root);
}