#include <golite/simple_expression.h>

int golite::SimpleExpression::getLine() {
    return expression_->getLine();
}

void golite::SimpleExpression::typeCheck() {
    expression_->typeCheck();
}

void golite::SimpleExpression::weedingPass(bool check_break, bool check_continue) {
    expression_->weedingPass();
}

std::string golite::SimpleExpression::toGoLite(int indent) {
    return expression_->toGoLite(indent);
}
