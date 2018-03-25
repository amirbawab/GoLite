#include <golite/binary.h>
#include <golite/utils.h>
#include <sstream>
#include <golite/identifier.h>
#include <golite/primary_expression.h>
#include <iostream>
#include <golite/program.h>

std::string golite::Binary::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "(" << left_operand_->toGoLite(0);
    switch (kind_){
        case MINUS:
            ss << " - ";
            break;
        case PLUS:
            ss << " + ";
            break;
        case MULTIPLY:
            ss << " * ";
            break;
        case DIVIDE:
            ss << " / ";
            break;
        case MODULO:
            ss << " % ";
            break;
        case BIT_AND:
            ss << " & ";
            break;
        case BIT_OR:
            ss << " | ";
            break;
        case BIT_XOR:
            ss << " ^ ";
            break;
        case BIT_CLEAR:
            ss << " &^ ";
            break;
        case LEFT_SHIFT:
            ss << " << ";
            break;
        case RIGHT_SHIFT:
            ss << " >> ";
            break;
        case IS_EQUAL:
            ss << " == ";
            break;
        case IS_NOT_EQUAL:
            ss << " != ";
            break;
        case LESS_THAN:
            ss << " < ";
            break;
        case LESS_THAN_EQUAL:
            ss << " <= ";
            break;
        case GREATER_THAN:
            ss << " > ";
            break;
        case GREATER_THAN_EQUAL:
            ss << " >= ";
            break;
        case AND:
            ss << " && ";
            break;
        case OR:
            ss << " || ";
            break;
    }
    ss << right_operand_->toGoLite(0) << ")";
    return ss.str();
}

int golite::Binary::getLine() {
    return left_operand_->getLine();
}

void golite::Binary::weedingPass() {
    if(left_operand_->isBlank()) {
        golite::Utils::error_message("Left operand in binary expression cannot be a blank identifier",
                                     left_operand_->getLine());
    }

    if(right_operand_->isBlank()) {
        golite::Utils::error_message("Right operand in binary expression cannot be a blank identifier",
                                     right_operand_->getLine());
    }

    left_operand_->weedingPass();
    right_operand_->weedingPass();
}

golite::TypeComponent* golite::Binary::typeCheck() {
    TypeComponent* left_type = left_operand_->typeCheck();
    TypeComponent* right_type = right_operand_->typeCheck();
    switch (kind_) {
        case KIND::OR:
        case KIND::AND:
            if(!left_type->resolvesToBool()) {
                golite::Utils::error_message("Left operand of && and || must be a boolean but given "
                                             + left_type->toGoLiteMin() , left_operand_->getLine());
            }
            if(!right_type->resolvesToBool()) {
                golite::Utils::error_message("Right operand of && and || must be a boolean but given "
                                             + right_type->toGoLiteMin() , right_operand_->getLine());
            }
            if(!left_type->isCompatible(right_type)) {
                golite::Utils::error_message("Left and right operands of && and || must be compatible but given "
                                             + left_type->toGoLiteMin() + " and " + right_type->toGoLiteMin(),
                                             left_operand_->getLine());
            }
            return left_type;

        case KIND::IS_EQUAL:
        case KIND::IS_NOT_EQUAL:
            if(!left_type->resolvesToComparable()) {
                golite::Utils::error_message("Left operand of == and != must resolve to a comparable but given "
                                             + left_type->toGoLiteMin(), left_operand_->getLine());
            }
            if(!right_type->resolvesToComparable()) {
                golite::Utils::error_message("Right operand of == and != must resolve to a comparable but given "
                                             + right_type->toGoLiteMin(), right_operand_->getLine());
            }
            if(!left_type->isCompatible(right_type)) {
                golite::Utils::error_message("Left and right operand of == and != must be compatible but given "
                                             + left_type->toGoLiteMin() + " and " + right_type->toGoLiteMin(),
                                             left_operand_->getLine());
            }
            return Program::BOOL_BUILTIN_TYPE->getTypeComponent();

        case KIND::LESS_THAN:
        case KIND::LESS_THAN_EQUAL:
        case KIND::GREATER_THAN:
        case KIND::GREATER_THAN_EQUAL:
            if(!left_type->resolvesToOrdered()) {
                golite::Utils::error_message("Left operand operand of <, >, <=, >= must resolve to an ordered but given "
                                             + left_type->toGoLiteMin(), left_operand_->getLine());
            }
            if(!right_type->resolvesToOrdered()) {
                golite::Utils::error_message("Right operand operand of <, >, <=, >= must resolve to an ordered but given "
                                             + right_type->toGoLiteMin(), right_operand_->getLine());
            }
            if(!left_type->isCompatible(right_type)) {
                golite::Utils::error_message("Left and right operands of <, >, <=, >= must be compatible but given "
                                             + left_type->toGoLiteMin() + " and " + right_type->toGoLiteMin(),
                                             left_operand_->getLine());
            }
            return Program::BOOL_BUILTIN_TYPE->getTypeComponent();

        case KIND::PLUS:
            if(!left_type->resolvesToString() && !left_type->resolvesToNumeric()) {
                golite::Utils::error_message("Left operand of + must resolve to a string or a numeric but given "
                                             + left_type->toGoLiteMin(), left_operand_->getLine());
            }
            if(!right_type->resolvesToString() && !right_type->resolvesToNumeric()) {
                golite::Utils::error_message("Right operand of + must resolve to a string or a numeric but given "
                                             + right_type->toGoLiteMin(), right_operand_->getLine());
            }
            if(!left_type->isCompatible(right_type)) {
                golite::Utils::error_message("Left and right operands of + must be compatible but given "
                                             + left_type->toGoLiteMin() + " and " + right_type->toGoLiteMin(),
                                             left_operand_->getLine());
            }
            return left_type;

        case KIND::MINUS:
        case KIND::MULTIPLY:
        case KIND::DIVIDE:
            if(!left_type->resolvesToNumeric()) {
                golite::Utils::error_message("Left operand of -, *, / must resolve to a numeric but given "
                                             + left_type->toGoLiteMin(), left_operand_->getLine());
            }
            if(!right_type->resolvesToNumeric()) {
                golite::Utils::error_message("Right operand of -, *, / must resolve to a numeric but given "
                                             + right_type->toGoLiteMin(), right_operand_->getLine());
            }
            if(!left_type->isCompatible(right_type)) {
                golite::Utils::error_message("Left and right operands of -, *, / must be compatible but given "
                                             + left_type->toGoLiteMin() + " and " + right_type->toGoLiteMin(),
                                             left_operand_->getLine());
            }
            return left_type;

        case KIND::MODULO:
        case KIND::BIT_OR:
        case KIND::BIT_AND:
        case KIND::LEFT_SHIFT:
        case KIND::RIGHT_SHIFT:
        case KIND::BIT_CLEAR:
        case KIND::BIT_XOR:
            if(!left_type->resolvesToInteger()) {
                golite::Utils::error_message("Left operand of %, |, &, <<, >>, ^&, ^ must resolve to an integer but given "
                                             + left_type->toGoLiteMin(), left_operand_->getLine());
            }
            if(!right_type->resolvesToInteger()) {
                golite::Utils::error_message("Right operand of %, |, &, <<, >>, ^&, ^ must resolve to an integer but given "
                                             + right_type->toGoLiteMin(), right_operand_->getLine());
            }
            if(!left_type->isCompatible(right_type)) {
                golite::Utils::error_message("Left and right operands of %, |, &, <<. >>, ^&, ^ must be compatible but given "
                                             + left_type->toGoLiteMin() + " and " + right_type->toGoLiteMin(),
                                             left_operand_->getLine());
            }
            return left_type;
    }
    throw std::runtime_error("Unrecognized binary expression kind");
}

void golite::Binary::symbolTablePass(SymbolTable *root) {
    this->left_operand_->symbolTablePass(root);
    this->right_operand_->symbolTablePass(root);
}

std::string golite::Binary::toTypeScript(int indent) {
    std::stringstream ss;
    ss << "(" << left_operand_->toTypeScript(0);
    switch (kind_){
        case MINUS:
            ss << " - ";
            break;
        case PLUS:
            ss << " + ";
            break;
        case MULTIPLY:
            ss << " * ";
            break;
        case DIVIDE:
            ss << " / ";
            break;
        case MODULO:
            ss << " % ";
            break;
        case BIT_AND:
            ss << " & ";
            break;
        case BIT_OR:
            ss << " | ";
            break;
        case BIT_XOR:
            ss << " ^ ";
            break;
        case BIT_CLEAR:
            ss << " &^ ";  // TODO
            break;
        case LEFT_SHIFT:
            ss << " << ";
            break;
        case RIGHT_SHIFT:
            ss << " >> ";
            break;
        case IS_EQUAL:
            ss << " == ";
            break;
        case IS_NOT_EQUAL:
            ss << " != ";
            break;
        case LESS_THAN:
            ss << " < ";
            break;
        case LESS_THAN_EQUAL:
            ss << " <= ";
            break;
        case GREATER_THAN:
            ss << " > ";
            break;
        case GREATER_THAN_EQUAL:
            ss << " >= ";
            break;
        case AND:
            ss << " && ";
            break;
        case OR:
            ss << " || ";
            break;
    }
    ss << right_operand_->toTypeScript(0) << ")";
    return ss.str();
}

std::string golite::Binary::toTypeScriptInitializer(int indent) {
    std::stringstream ss;
    ss << left_operand_->toTypeScriptInitializer(indent)
       << right_operand_->toTypeScriptInitializer(indent);
    return ss.str();
}