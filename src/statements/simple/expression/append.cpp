#include <golite/append.h>
#include <golite/utils.h>
#include <sstream>
#include <golite/identifier.h>

std::string golite::Append::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "append("
       << left_expression_->toGoLite(0) << ", "
       << right_expression_->toGoLite(0) << ")";
    return ss.str();
}

int golite::Append::getLine() {
    return left_expression_->getLine();
}

void golite::Append::weedingPass(bool check_break, bool check_continue) {
    if(left_expression_->isIdentifier()) {
        golite::Identifier* identifier = static_cast<Identifier*>(left_expression_);
        if(identifier->isBlank()) {
            golite::Utils::error_message("Append does not accept left argument to be a blank identifier",
                                         left_expression_->getLine());
        }
    }

    if(right_expression_->isIdentifier()) {
        golite::Identifier* identifier = static_cast<Identifier*>(right_expression_);
        if(identifier->isBlank()) {
            golite::Utils::error_message("Append does not accept right argument to be a blank identifier",
                                         right_expression_->getLine());
        }
    }

    left_expression_->weedingPass(check_break, check_continue);
    right_expression_->weedingPass(check_break, check_continue);
}