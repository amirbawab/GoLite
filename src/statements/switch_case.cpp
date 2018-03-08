#include <golite/switch_case.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>
#include <golite/primary_expression.h>
#include <golite/program.h>

std::string golite::SwitchCase::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent);
    if(isDefault()) {
        ss << "default:";
    } else {
        ss << "case " << golite::Pretty::implodeExpressions(expressions_) << ":";
    }
    for(Statement* statement : block_->getStatements()) {
        ss << std::endl << statement->toGoLite(indent+1);
    }
    return ss.str();
}

int golite::SwitchCase::getLine() {
    return block_->getLine();
}

void golite::SwitchCase::weedingPass(bool check_continue) {
    for(Expression* expression : expressions_) {
        if(expression->isBlank()) {
            golite::Utils::error_message("Case expression cannot be a blank identifier", expression->getLine());
        }
        expression->weedingPass();
    }
    block_->weedingPass(false, check_continue);
}

void golite::SwitchCase::typeCheck() {
    for (Expression *expression : expressions_) {
        TypeComponent *type_component = expression->typeCheck();
        if (!type_component->isCompatible(golite::Program::BOOL_BUILTIN_TYPE.getTypeComponent())) {
            golite::Utils::error_message("Switch case condition must evaluate to a boolean", expression->getLine());
        }
    }
    block_->typeCheck();
}

void golite::SwitchCase::symbolTablePass(SymbolTable *root) {
    for(golite::Expression* expr : this->expressions_) {
        expr->symbolTablePass(root);
    }

    SymbolTable* block_symbol_table = new SymbolTable();
    root->addChild(block_symbol_table);
    block_->symbolTablePass(block_symbol_table);
}