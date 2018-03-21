#include <golite/unary.h>
#include <golite/utils.h>
#include <sstream>
#include <golite/identifier.h>
#include <golite/primary_expression.h>

std::string golite::Unary::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "(";
    switch (kind_) {
        case MINUS:
            ss << "-";
            break;
        case NOT:
            ss << "!";
            break;
        case PLUS:
            ss << "+";
            break;
        case XOR:
            ss << "^";
            break;
    }
    ss << operand_->toGoLite(0) << ")";
    return ss.str();
}

int golite::Unary::getLine() {
    return operand_->getLine();
}

void golite::Unary::weedingPass() {
    if(operand_->isBlank()) {
        golite::Utils::error_message("Unary operand cannot be a blank identifier", operand_->getLine());
    }
    operand_->weedingPass();
}

golite::TypeComponent* golite::Unary::typeCheck() {
    TypeComponent *operand_type = operand_->typeCheck();
    switch (kind_) {
        case PLUS:
        case MINUS:
            if(!operand_type->resolvesToNumeric()) {
                golite::Utils::error_message("Unary operation + and - expects an operand that resolves to a numeric "
                                                     "expression but given " + operand_type->toGoLiteMin(), getLine());
            }
            break;
        case NOT:
            if(!operand_type->resolvesToBool()) {
                golite::Utils::error_message("Unary operation ! expects an operand that resolves to a boolean "
                                                     "expression but given " + operand_type->toGoLiteMin(), getLine());
            }
            break;
        case XOR:
            if(!operand_type->resolvesToInteger()) {
                golite::Utils::error_message("Unary operation ^ expects an operand that resolves to an int or a rune "
                                                     "expression but given " + operand_type->toGoLiteMin(), getLine());
            }
            break;
    }
    return operand_type;
}

void golite::Unary::symbolTablePass(SymbolTable *root) {
    this->operand_->symbolTablePass(root);
}

std::string golite::Unary::toTypeScript(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "(";
    switch (kind_) {
        case MINUS:
            ss << "-";
            break;
        case NOT:
            ss << "!";
            break;
        case PLUS:
            ss << "+";
            break;
        case XOR:
            ss << "^";
            break;
    }
    ss << operand_->toTypeScript(0) << ")";
    return ss.str();
}
