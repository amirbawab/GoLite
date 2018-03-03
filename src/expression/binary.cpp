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
    TypeComponent* left = left_operand_->typeCheck();
    TypeComponent* right = right_operand_->typeCheck();
    switch (kind_) {
        case KIND::OR:
        case KIND::AND:
            if(!left->isCompatible(Program::BOOL_BUILTIN_TYPE.getTypeComponent())) {
                golite::Utils::error_message("Left operand of && an || must be a boolean" , left_operand_->getLine());
            }

            if(!right->isCompatible(Program::BOOL_BUILTIN_TYPE.getTypeComponent())) {
                golite::Utils::error_message("Right operand of && an || must be a boolean" , right_operand_->getLine());
            }
            return golite::Program::BOOL_BUILTIN_TYPE.getTypeComponent();

        case KIND::IS_EQUAL:
        case KIND::IS_NOT_EQUAL:
            if(!left->isCompatible(right)) {
                golite::Utils::error_message("Left and right operand of == and != must be compatible",
                                             left_operand_->getLine());
            }
            return golite::Program::BOOL_BUILTIN_TYPE.getTypeComponent();

        case KIND::LESS_THAN:
        case KIND::LESS_THAN_EQUAL:
        case KIND::GREATER_THAN:
        case KIND::GREATER_THAN_EQUAL:
            return nullptr;

        case KIND::PLUS:
        case KIND::MINUS:
        case KIND::MULTIPLY:
        case KIND::DIVIDE:
        case KIND::MODULO:
        case KIND::BIT_AND:
        case KIND::BIT_OR:
        case KIND::LEFT_SHIFT:
        case KIND::RIGHT_SHIFT:
        case KIND::BIT_CLEAR:
        case KIND::BIT_XOR:
            return nullptr;
    }
    throw std::runtime_error("Unrecognized binary expression kind");
}

