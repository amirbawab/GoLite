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
        if(left_simple_->isSimpleExpression()) {
            golite::SimpleExpression* simple_expression = static_cast<SimpleExpression*>(left_simple_);
            if(simple_expression->getExpression()->isBlank()) {
                golite::Utils::error_message("For statement pre statement cannot be a blank identifier",
                                             left_simple_->getLine());
            }
        }
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
        if(right_simple_->isSimpleExpression()) {
            golite::SimpleExpression* simple_expression = static_cast<SimpleExpression*>(right_simple_);
            if(simple_expression->getExpression()->isBlank()) {
                golite::Utils::error_message("For statement post statement cannot be a blank identifier",
                                             right_simple_->getLine());
            }
        } else if(right_simple_->isDeclaration()){
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

    if (expression_) {
        TypeComponent *type_component_ = expression_->typeCheck();
        if (!type_component_->isCompatible(golite::Program::BOOL_BUILTIN_TYPE.getTypeComponent())) {
            golite::Utils::error_message("For condition must evaluate to a boolean", expression_->getLine());
        }
    }

    if (right_simple_) {
        right_simple_->typeCheck();
    }
    block_->typeCheck();
}

void golite::For::symbolTablePass(SymbolTable *root) {
    golite::SymbolTable* for_symbol_table = new golite::SymbolTable();
    symbol_table_ = new golite::SymbolTable();
    symbol_table_->addChild(for_symbol_table);
    root->addChild(symbol_table_);

    if(left_simple_) {
        left_simple_->symbolTablePass(symbol_table_);
    }

    if(expression_) {
        expression_->symbolTablePass(symbol_table_);
    }

    if(right_simple_) {
        right_simple_->symbolTablePass(symbol_table_);
    }

    this->block_->symbolTablePass(for_symbol_table);
}