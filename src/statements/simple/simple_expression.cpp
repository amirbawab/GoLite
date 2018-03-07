#include <golite/simple_expression.h>
#include <golite/utils.h>
#include <sstream>

int golite::SimpleExpression::getLine() {
    return expression_->getLine();
}

void golite::SimpleExpression::typeCheck() {
    expression_->typeCheck();
}

void golite::SimpleExpression::weedingPass(bool check_break, bool check_continue) {
    expression_->weedingPass();
    if(!expression_->isFunctionCall()) {
        golite::Utils::error_message("Expression statement must be a function call", expression_->getLine());
    }
}

std::string golite::SimpleExpression::toGoLite(int indent) {
    std::stringstream ss;
    ss << expression_->toGoLite(indent) << ";";
    return ss.str();
}

void golite::SimpleExpression::symbolTablePass(SymbolTable *root) {
    if(expression_) {
        this->expression_->symbolTablePass(root);
    }
}
