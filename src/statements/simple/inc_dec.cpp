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

    // Resolve non-parenthesis expression
    if(!expression_->isAddressable()) {
        golite::Utils::error_message("Increment/decrement statement expects an addressable operand but given" +
                                             expression_->toGoLite(0), expression_->getLine());
    }
    if(!expression_type->resolvesToNumeric()) {
        golite::Utils::error_message("Increment/decrement statement must resolve to a numeric but given "
                                     + expression_type->toGoLiteMin(), expression_->getLine());
    }
}

void golite::IncDec::symbolTablePass(SymbolTable *root) {
    this->expression_->symbolTablePass(root);
}

std::string golite::IncDec::toTypeScript(int indent) {
    std::stringstream ss;
    ss << golite::Utils::blockComment({(isIncrement() ? "Increment statement" : "Decrement statement")},
                                      indent, getLine()) << std::endl
       << golite::Utils::indent(indent) << expression_->toTypeScript(0);
    if(isIncrement()) {
        ss << "++";
    } else {
        ss << "--";
    }
    return ss.str();
}