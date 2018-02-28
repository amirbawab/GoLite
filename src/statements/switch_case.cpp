#include <golite/switch_case.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>
#include <golite/primary_expression.h>

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

void golite::SwitchCase::weedingPass(bool check_break, bool check_continue) {
    for(Expression* expression : expressions_) {
        golite::PrimaryExpression* primary_expression = static_cast<PrimaryExpression*>(expression);
        golite::Identifier* identifier = static_cast<Identifier*>(primary_expression->lastChild());
        if(identifier->isBlank()) {
            golite::Utils::error_message("Case expression cannot be a blank identifier",
                                         expression->getLine());
        }
        expression->weedingPass(check_break, check_continue);
    }
    block_->weedingPass(false, check_continue);
}