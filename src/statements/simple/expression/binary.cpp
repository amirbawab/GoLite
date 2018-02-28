#include <golite/binary.h>
#include <golite/utils.h>
#include <sstream>
#include <golite/identifier.h>

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

void golite::Binary::weedingPass(bool check_break, bool check_continue) {
    if(left_operand_->isIdentifier()) {
        golite::Identifier* identifier = static_cast<Identifier*>(left_operand_);
        if(identifier->isBlank()) {
            golite::Utils::error_message("Left operand in binary expression cannot be a blank identifier",
                                         left_operand_->getLine());
        }
    }

    if(right_operand_->isIdentifier()) {
        golite::Identifier* identifier = static_cast<Identifier*>(right_operand_);
        if(identifier->isBlank()) {
            golite::Utils::error_message("Right operand in binary expression cannot be a blank identifier",
                                         right_operand_->getLine());
        }
    }

    left_operand_->weedingPass(check_break, check_continue);
    right_operand_->weedingPass(check_break, check_continue);
}