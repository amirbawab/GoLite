#include <golite/assignment.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>
#include <golite/primary_expression.h>
#include <golite/variable.h>
#include <iostream>
#include <golite/ts_helper.h>

std::string golite::Assignment::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << golite::Pretty::implodeExpressions(left_expressions_);
    switch (kind_) {
        case EQUAL:
            ss << " = ";
            break;
        case PLUS_EQUAL:
            ss << " += ";
            break;
        case MINUS_EQUAL:
            ss << " -= ";
            break;
        case MULTIPLY_EQUAL:
            ss << " *= ";
            break;
        case DIVIDE_EQUAL:
            ss << " /= ";
            break;
        case MODULO_EQUAL:
            ss << " %= ";
            break;
        case LEFT_SHIFT_EQUAL:
            ss << " <<= ";
            break;
        case RIGHT_SHIFT_EQUAL:
            ss << " >>= ";
            break;
        case BIT_AND_EQUAL:
            ss << " &= ";
            break;
        case BIT_OR_EQUAL:
            ss << " |= ";
            break;
        case BIT_XOR_EQUAL:
            ss << " ^= ";
            break;
        case BIT_CLEAR_EQUAL:
            ss << " &^= ";
            break;
    }

    ss << golite::Pretty::implodeExpressions(right_expressions_);
    return ss.str();
}

int golite::Assignment::getLine() {
    if(left_expressions_.empty()) {
        throw std::runtime_error("Cannot get line of assignment operation with not left expressions");
    }
    return left_expressions_.front()->getLine();
}

void golite::Assignment::weedingPass(bool, bool) {
    if(left_expressions_.size() != right_expressions_.size()) {
        golite::Utils::error_message("Number of left and right elements of assignment does not match", getLine());
    }

    if(left_expressions_.size() > 1 && kind_ != KIND::EQUAL) {
        golite::Utils::error_message("<op>= assignments expect 1 left operand", getLine());
    }

    for(Expression* expression : left_expressions_) {
        if(kind_ != KIND::EQUAL && expression->isBlank()) {
            golite::Utils::error_message("Assignment target may not be the blank identifier", expression->getLine());
        }
        expression->weedingPass();
    }

    for(Expression* expression : right_expressions_) {
        if(expression->isBlank()) {
            golite::Utils::error_message("Assignment value cannot be a blank identifier", expression->getLine());
        }
        expression->weedingPass();
    }
}

void golite::Assignment::typeCheck() {
    if(left_expressions_.size() != right_expressions_.size()) {
        throw std::runtime_error("The number of left and right elements is not equal. Verify weeding pass.");
    }

    for(size_t i=0; i < left_expressions_.size(); i++) {
        Expression* left_operand = left_expressions_[i];
        Expression* right_operand = right_expressions_[i];

        TypeComponent* right_type = right_operand->typeCheck();
        // Ignore case of blank identifier on the left
        if(!left_operand->isBlank()) {

            // Perform type check on the left element
            TypeComponent* left_type = left_operand->typeCheck();
            if(!left_operand->isAddressable()) {
                golite::Utils::error_message("Assignment operand " + left_operand->toGoLite(0) + " is not addressable",
                                             left_operand->getLine());
            }
            switch (kind_) {
                case EQUAL:
                    if(!left_type->isCompatible(right_type)) {
                        golite::Utils::error_message("Incompatible " + left_type->toGoLiteMin() + " and "
                                                     + right_type->toGoLiteMin(), left_type->getLine());
                    }
                    break;

                case PLUS_EQUAL:
                    if(!left_type->resolvesToString() && !left_type->resolvesToNumeric()) {
                        golite::Utils::error_message("Left operand of += must resolve to a string or a numeric but given "
                                                     + left_type->toGoLiteMin(), left_operand->getLine());
                    }
                    if(!right_type->resolvesToString() && !right_type->resolvesToNumeric()) {
                        golite::Utils::error_message("Right operand of += must resolve to a string or a numeric but given "
                                                     + right_type->toGoLiteMin(), right_operand->getLine());
                    }
                    if(!left_type->isCompatible(right_type)) {
                        golite::Utils::error_message("Left and right operands of += must be compatible but given "
                                                     + left_type->toGoLiteMin() + " and " + right_type->toGoLiteMin(),
                                                     left_operand->getLine());
                    }
                    break;

                case MINUS_EQUAL:
                case MULTIPLY_EQUAL:
                case DIVIDE_EQUAL:
                    if(!left_type->resolvesToNumeric()) {
                        golite::Utils::error_message("Left operand of -=, *=, /= must resolve to a numeric but given "
                                                     + left_type->toGoLiteMin(), left_operand->getLine());
                    }
                    if(!right_type->resolvesToNumeric()) {
                        golite::Utils::error_message("Right operand of -=, *=, /= must resolve to a numeric but given "
                                                     + right_type->toGoLiteMin(), right_operand->getLine());
                    }
                    if(!left_type->isCompatible(right_type)) {
                        golite::Utils::error_message("Left and right operands of -=, *=, /= must be compatible but given "
                                                     + left_type->toGoLiteMin() + " and " + right_type->toGoLiteMin(),
                                                     left_operand->getLine());
                    }
                    break;

                case MODULO_EQUAL:
                case BIT_OR_EQUAL:
                case BIT_AND_EQUAL:
                case LEFT_SHIFT_EQUAL:
                case RIGHT_SHIFT_EQUAL:
                case BIT_CLEAR_EQUAL:
                case BIT_XOR_EQUAL:
                    if(!left_type->resolvesToInteger()) {
                        golite::Utils::error_message("Left operand of %=, |=, &=, <<=, >>=, ^&=, ^= must resolve to an integer but given "
                                                     + left_type->toGoLiteMin(), left_operand->getLine());
                    }
                    if(!right_type->resolvesToInteger()) {
                        golite::Utils::error_message("Right operand of %=, |=, &=, <<=, >>=, ^&=, ^= must resolve to an integer but given "
                                                     + right_type->toGoLiteMin(), right_operand->getLine());
                    }
                    if(!left_type->isCompatible(right_type)) {
                        golite::Utils::error_message("Left and right operands of %, |, &, <<. >>, ^&, ^ must be compatible but given "
                                                     + left_type->toGoLiteMin() + " and " + right_type->toGoLiteMin(),
                                                     left_operand->getLine());
                    }
                    break;
                default:
                    throw std::runtime_error("Unhandled <op>= kind");
            }
        }
    }
}

void golite::Assignment::symbolTablePass(SymbolTable *root) {
    for(golite::Expression* expr : this->left_expressions_) {
        if(!expr->isBlank()) {
            expr->symbolTablePass(root);
        }
    }

    for(golite::Expression* expr : this->right_expressions_) {
        expr->symbolTablePass(root);
    }
}

std::string golite::Assignment::toTypeScript(int indent) {
    std::stringstream ss_ids;
    std::stringstream ss_exprs;
    std::stringstream ss;

    // Init expressions from left to right
    for(size_t i=0; i < left_expressions_.size(); i++) {
        ss << left_expressions_[i]->toTypeScriptInitializer(indent);
    }
    for(size_t i=0; i < left_expressions_.size(); i++) {
        ss << right_expressions_[i]->toTypeScriptInitializer(indent);
    }

    ss << golite::Utils::blockComment({"Assignment group of size " + std::to_string(left_expressions_.size())},
                                      indent, getLine()) << std::endl;
    ss_ids << golite::Utils::indent(indent);
    if(left_expressions_.size() > 1) {
        ss_ids << "[";
        ss_exprs << "[";
    }
    for(size_t i=0; i < left_expressions_.size(); i++) {
        if(i != 0) {
            ss_ids << ", ";
            ss_exprs << ", ";
        }
        ss_ids << left_expressions_[i]->toTypeScript(0);
        ss_exprs << right_expressions_[i]->toTypeScript(0)
                 << golite::TSHelper::cloneObject(right_expressions_[i]->typeCheck());
    }
    if(left_expressions_.size() > 1) {
        ss_ids << "]";
        ss_exprs << "]";
    }
    ss << ss_ids.str();

    switch (kind_) {
        case EQUAL:
            ss << " = ";
            break;
        case PLUS_EQUAL:
            ss << " += ";
            break;
        case MINUS_EQUAL:
            ss << " -= ";
            break;
        case MULTIPLY_EQUAL:
            ss << " *= ";
            break;
        case DIVIDE_EQUAL:
            ss << " /= ";
            break;
        case MODULO_EQUAL:
            ss << " %= ";
            break;
        case LEFT_SHIFT_EQUAL:
            ss << " <<= ";
            break;
        case RIGHT_SHIFT_EQUAL:
            ss << " >>= ";
            break;
        case BIT_AND_EQUAL:
            ss << " &= ";
            break;
        case BIT_OR_EQUAL:
            ss << " |= ";
            break;
        case BIT_XOR_EQUAL:
            ss << " ^= ";
            break;
        case BIT_CLEAR_EQUAL:
            ss << " &= ";
    }
    if(kind_ == KIND::BIT_CLEAR_EQUAL) {
        ss  << "~(" << ss_exprs.str() << ")";
    } else {
        ss << ss_exprs.str();
    }
    ss << ";" << std::endl;
    return ss.str();
}