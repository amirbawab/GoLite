#include <golite/println.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>
#include <golite/primary_expression.h>
#include <vector>
#include <golite/program.h>

std::string golite::Println::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "println(" << golite::Pretty::implodeExpressions(expressions_) << ");";
    return ss.str();
}

void golite::Println::weedingPass(bool, bool) {
    for(Expression* expression : expressions_) {
        if(expression->isBlank()) {
            golite::Utils::error_message("Function println does not accept blank identifier as arguments",
                                         expression->getLine());
        }
        expression->weedingPass();
    }
}

void golite::Println::typeCheck() {
    for (Expression *expression : expressions_) {
        TypeComponent* expression_type = expression->typeCheck();
        if(!golite::Program::resolvesToBuiltIn(expression_type)) {
            golite::Utils::error_message("Println expects base types, received " + expression_type->toGoLiteMin(),
                                         expression->getLine());
        }
    }
}

void golite::Println::symbolTablePass(SymbolTable *root) {
    for(golite::Expression* expr: this->expressions_) {
        expr->symbolTablePass(root);
    }
}