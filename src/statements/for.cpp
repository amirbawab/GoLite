#include <golite/for.h>
#include <golite/utils.h>
#include <sstream>
#include <golite/primary_expression.h>
#include <golite/identifier.h>
#include <golite/simple_expression.h>
#include <golite/program.h>

std::string golite::For::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "for ";
    if(left_simple_ || right_simple_) {
        if(left_simple_) {
            ss << left_simple_->toGoLite(0);
        }
        ss << "; ";

        if(expression_) {
            ss << expression_->toGoLite(0);
        }
        ss << "; ";

        if(right_simple_) {
            ss << right_simple_->toGoLite(0) << " ";
        }
    } else if(expression_) {
        ss << expression_->toGoLite(0) << " ";
    }
    ss << "{";
    if(!block_->getStatements().empty()) {
        ss << std::endl;
        for(Statement* statement : block_->getStatements()) {
            ss << statement->toGoLite(indent+1) << std::endl;
        }
        ss << golite::Utils::indent(indent);
    }
    ss << "}";
    return ss.str();
}

void golite::For::weedingPass(bool, bool) {
    if(left_simple_) {
        left_simple_->weedingPass(false, false);
    }

    if(expression_) {
        if(expression_->isBlank()) {
            golite::Utils::error_message("For statement expression cannot be a blank identifier",
                                         expression_->getLine());
        }
        expression_->weedingPass();
    }

    if(right_simple_) {
        if(right_simple_->isDeclaration()){
            golite::Utils::error_message("Right simple statement cannot be a short declaration",
                                         right_simple_->getLine());
        }
        right_simple_->weedingPass(false, false);
    }
    block_->weedingPass(false, false);
}

void golite::For::typeCheck() {
    if (left_simple_) {
        left_simple_->typeCheck();
    }

    if(expression_) {
        TypeComponent *type_component_ = expression_->typeCheck();
        if (!type_component_->resolvesToBool()) {
            golite::Utils::error_message("For condition must evaluate to bool but given "
                                         + type_component_->toGoLiteMin(), expression_->getLine());
        }
    }

    if (right_simple_) {
        right_simple_->typeCheck();
    }
    block_->typeCheck();
}

void golite::For::symbolTablePass(SymbolTable *root) {
    static long count = 1;
    std::string for_name_prefix = "_for_" + std::to_string(count++);
    SymbolTable* for_outer_table = new SymbolTable(root, for_name_prefix + "_o");
    if(left_simple_) {
        left_simple_->symbolTablePass(for_outer_table);
    }

    if(expression_) {
        expression_->symbolTablePass(for_outer_table);
    }

    if(right_simple_) {
        right_simple_->symbolTablePass(for_outer_table);
    }

    SymbolTable* for_inner_table = new SymbolTable(for_outer_table, for_name_prefix + "_i");
    this->block_->symbolTablePass(for_inner_table);
}

void golite::For::checkReturn(Declarable* function) {
    block_->checkReturn(function);
}

bool golite::For::hasBreak() {
    return block_->hasBreak();
}

bool golite::For::isTerminating() {
    if(expression_) {
        golite::Utils::error_message("For loop with a condition is not terminating", getLine());
    }

    if(hasBreak()) {
        golite::Utils::error_message("For loop with a break statement is not terminating", getLine());
    }
    return true;
}

std::string golite::For::toTypeScript(int indent) {
    static long count = 1;
    std::stringstream ss;
    std::string while_counter = "while_" + std::to_string(count);
    if(left_simple_ && !left_simple_->isEmpty()) {
        ss << left_simple_->toTypeScript(indent) << std::endl;
    }
    ss << golite::Utils::blockComment({"For statement"}, indent, getLine()) << std::endl;
    ss << golite::Utils::indent(indent) << "var " << while_counter << " : number = 0;" << std::endl;
    ss << golite::Utils::indent(indent) << "while (";
    if(expression_) {
        ss << expression_->toTypeScript(0);
    } else {
        ss << "true";
    }
    ss << ") {";
    if(right_simple_ && !right_simple_->isEmpty()) {
        ss << std::endl << golite::Utils::indent(indent+1) << "if (" << while_counter << " != 0) {" << std::endl;
        ss << right_simple_->toTypeScript(indent+2) << std::endl;
        ss << golite::Utils::indent(indent+1) << "}" << std::endl;
        ss << golite::Utils::indent(indent+1) << "++" << while_counter << std::endl;
    }
    if(!block_->getStatements().empty()) {
        ss << std::endl;
        for(Statement* statement : block_->getStatements()) {
            ss << statement->toTypeScript(indent+1) << std::endl;
        }
    }
    ss << "}";
    return ss.str();
}