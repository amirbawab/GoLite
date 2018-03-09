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

void golite::SwitchCase::typeCheck(TypeComponent* switch_expression_type) {
    for (Expression *expression : expressions_) {
        TypeComponent *type_component = expression->typeCheck();
        if(switch_expression_type) {
            if(!switch_expression_type->isCompatible(type_component)) {
                golite::Utils::error_message("Case statement expects expression of type "
                                             + switch_expression_type->toGoLiteMin() + " but given "
                                             + type_component->toGoLiteMin(), expression->getLine());
            }
        } else if (!type_component->isBool()) {
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

bool golite::SwitchCase::hasReturn(Declarable* function) {
    return block_->hasReturn(function);
}