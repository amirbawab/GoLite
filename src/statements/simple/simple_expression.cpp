#include <golite/simple_expression.h>
#include <golite/utils.h>
#include <sstream>
#include <golite/primary_expression.h>
#include <golite/parenthesis.h>
#include <iostream>

int golite::SimpleExpression::getLine() {
    return expression_->getLine();
}

void golite::SimpleExpression::typeCheck() {
    expression_->typeCheck();
}

void golite::SimpleExpression::weedingPass(bool, bool) {
    expression_->weedingPass();
    if(expression_->isParenthesis()) {
        PrimaryExpression* primary_expression = static_cast<PrimaryExpression*>(expression_);
        Parenthesis* parenthesis = static_cast<Parenthesis*>(primary_expression->getChildren().front());
        if(!parenthesis->resolveExpression()->isFunctionCall()) {
            golite::Utils::error_message("Expression statement in parenthesis must be a function all",
                                         expression_->getLine());
        }
    }else if(!expression_->isFunctionCall()) {
        golite::Utils::error_message("Expression statement must be a function call", expression_->getLine());
    }
}

std::string golite::SimpleExpression::toGoLite(int indent) {
    std::stringstream ss;
    ss << expression_->toGoLite(indent) << ";";
    return ss.str();
}

void golite::SimpleExpression::symbolTablePass(SymbolTable *root) {
    this->expression_->symbolTablePass(root);
}
