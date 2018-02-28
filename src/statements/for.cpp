#include <golite/for.h>
#include <golite/utils.h>
#include <sstream>

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

void golite::For::weedingPass(bool check_break, bool check_continue) {
    if(left_simple_) {
        left_simple_->weedingPass(check_break, check_continue);
    }
    if(expression_) {
        expression_->weedingPass(check_break, check_continue);
    }
    if(right_simple_) {
        right_simple_->weedingPass(check_break, check_continue);
    }
    block_->weedingPass(false, false);
}