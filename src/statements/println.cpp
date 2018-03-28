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
        if(!expression_type->resolvesToBaseType()) {
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

std::string golite::Println::toTypeScript(int indent) {
    std::stringstream ss;
    for(Expression* expression : expressions_) {
        ss << expression->toTypeScriptInitializer(indent);
    }
    ss << golite::Utils::blockComment({"Print line statement"}, indent, getLine()) << std::endl;
    ss << golite::Utils::indent(indent) << "golite_println(";
    for(size_t i=0; i < expressions_.size(); i++) {
        TypeComponent* expr_type_component = expressions_[i]->typeCheck();
        if(i != 0) {
            ss << ", ";
        }
        std::string expr_ts =  expressions_[i]->toTypeScript(0);
        if(expr_type_component->resolvesToFloat64()) {
            ss << "golite_float(" << expr_ts << ")";
        } else {
            ss << expr_ts;
        }
    }
    ss << ");" << std::endl;
    return ss.str();
}