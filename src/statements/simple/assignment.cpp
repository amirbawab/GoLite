#include <golite/assignment.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>
#include <golite/primary_expression.h>

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
        if(!left_expressions_[i]->isPrimaryExpression()) {
            golite::Utils::error_message("Left element of an assignment cannot be binary or unary",
                                         left_expressions_[i]->getLine());
        }

        if(!left_expressions_[i]->isBlank()) {
            TypeComponent* right_type = right_expressions_[i]->typeCheck();
            TypeComponent* left_type = left_expressions_[i]->typeCheck();
            if(!left_type->isCompatible(right_type)) {
                golite::Utils::error_message("Incompatible " + left_type->toGoLiteMin() + " and "
                                             + right_type->toGoLiteMin(), left_type->getLine());
            }
        } else {
            // Just perform a symbol table pass on right expression
            right_expressions_[i]->typeCheck();
        }
    }
}

void golite::Assignment::symbolTablePass(SymbolTable *root) {
    for(golite::Expression* expr : this->left_expressions_) {
        expr->symbolTablePass(root);
    }

    for(golite::Expression* expr : this->right_expressions_) {
        expr->symbolTablePass(root);
    }
}