#include <golite/print.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>
#include <golite/primary_expression.h>
#include <golite/program.h>

std::string golite::Print::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "print(" << golite::Pretty::implodeExpressions(expressions_) << ");";
    return ss.str();
}

void golite::Print::weedingPass(bool, bool) {
    for(Expression* expression : expressions_) {
        if(expression->isBlank()) {
            golite::Utils::error_message("Function print does not accept blank identifier as arguments",
                                         expression->getLine());
        }
        expression->weedingPass();
    }
}

void golite::Print::typeCheck() {
    for (Expression *expression : expressions_) {
        TypeComponent* expression_type = expression->typeCheck();
        if(expression_type != Program::INT_BUILTIN_TYPE->getTypeComponent()
           && expression_type != Program::FLOAT64_BUILTIN_TYPE->getTypeComponent()
           && expression_type != Program::BOOL_BUILTIN_TYPE->getTypeComponent()
           && expression_type != Program::STRING_BUILTIN_TYPE->getTypeComponent()
           && expression_type != Program::RUNE_BUILTIN_TYPE->getTypeComponent()) {
            golite::Utils::error_message("Print expects base types, received " + expression_type->toGoLite(0), expression->getLine());
        }
    }
}

void golite::Print::symbolTablePass(SymbolTable *root) {
    for(golite::Expression* expr: this->expressions_) {
        expr->symbolTablePass(root);
    }
}