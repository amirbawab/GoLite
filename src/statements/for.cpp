#include <golite/for.h>
#include <golite/utils.h>
#include <sstream>
#include <golite/primary_expression.h>
#include <golite/identifier.h>
#include <golite/simple_expression.h>

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
        }
        right_simple_->weedingPass(false, false);
    }
    block_->weedingPass(false, false);
}

golite::TypeComponent* golite::For::typeCheck() {
    if(left_simple_) {
        left_simple_->typeCheck();
    }

    if(expression_) {
        TypeComponent* type_component_ = expression_->typeCheck();
        // TODO Check if it is boolean
    }

    if(right_simple_) {
        right_simple_->typeCheck();
    }
    block_->typeCheck();
    return nullptr;
}