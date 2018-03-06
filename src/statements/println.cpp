#include <golite/println.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>
#include <golite/primary_expression.h>
#include <vector>

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
        expression->weedingPass(false, false);
    }
}

void golite::Println::symbolTablePass(SymbolTable *root) {
    // carry the symtable checking over the println expressions
    for(std::vector<golite::Expression*>::iterator itt = this->expressions_.begin();
            itt != this->expressions_.end();
            itt++) {
        (*itt)->symbolTablePass(root);
    }
}