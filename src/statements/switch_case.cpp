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
        TypeComponent *expression_type = expression->typeCheck();
        if(switch_expression_type) {
            if(!switch_expression_type->isCompatible(expression_type)) {
                golite::Utils::error_message("Case statement expects expression of type "
                                             + switch_expression_type->toGoLiteMin() + " but given "
                                             + expression_type->toGoLiteMin(), expression->getLine());
            }
        } else if (!expression_type->isBool()) {
            golite::Utils::error_message("Switch case condition must evaluate to a bool but given "
                                         + expression_type->toGoLiteMin(), expression->getLine());
        }
    }
    block_->typeCheck();
}

void golite::SwitchCase::symbolTablePass(SymbolTable *root) {
    static long count = 1;
    for(golite::Expression* expr : this->expressions_) {
        expr->symbolTablePass(root);
    }

    SymbolTable* block_table = new SymbolTable(root, "_case_" + std::to_string(count++));
    block_->symbolTablePass(block_table);
}

void golite::SwitchCase::checkReturn(Declarable* function) {
    block_->checkReturn(function);
}

bool golite::SwitchCase::isTerminating() {
    if(block_->hasBreak()) {
        golite::Utils::error_message("Switch case with a break statement is not terminating", getLine());
    }

    if(!block_->isTerminating()) {
        golite::Utils::error_message("Switch case is not terminating", getLine());
    }
    return true;
}

std::string golite::SwitchCase::toTypeScript(std::string expressionStr, int indent) {
    std::stringstream ss;
    std::vector<std::string> labels;
    static int count = 1;
    for(Expression* expression : expressions_ ) {
        labels.push_back("case_" + std::to_string(count++));
        ss << golite::Utils::blockComment({"Case function"}, indent, expression->getLine()) << std::endl;
        ss << golite::Utils::indent(indent) << "function " << labels.back() << "() {" << std::endl;
        ss << expression->toTypeScriptInitializer(indent+1);
        ss << golite::Utils::indent(indent+1) << "return " << expression->toTypeScript(0) << ";" << std::endl;
        ss << golite::Utils::indent(indent) << "}" << std::endl << std::endl;
    }
    ss << golite::Utils::indent(indent) << "if (";
    if(!expressions_.empty()) {
        for(size_t i=0; i < expressions_.size(); i++) {
            if(i != 0) {
                ss << " || ";
            }
            if(!expressionStr.empty()) {
                ss << expressionStr << " == ";
            }
            ss << labels[i] << "()";
        }
    } else {
        ss << "true";
    }
    ss << ") {" << std::endl;
    if(!block_->getStatements().empty()) {
        for(Statement* statement : block_->getStatements()) {
            ss << statement->toTypeScript(indent+1) << std::endl;
        }
    }
    ss << golite::Utils::indent(indent+1) << "// Exit switch statement" << std::endl;
    ss << golite::Utils::indent(indent+1) << "break;" << std::endl;
    ss << golite::Utils::indent(indent) << "}" << std::endl;
    return ss.str();
}