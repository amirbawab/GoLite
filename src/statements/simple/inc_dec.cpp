#include <golite/inc_dec.h>
#include <golite/utils.h>
#include <sstream>
#include <golite/identifier.h>

std::string golite::IncDec::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << expression_->toGoLite(0);
    if(isIncrement()) {
        ss << "++";
    } else {
        ss << "--";
    }
    return ss.str();
}

int golite::IncDec::getLine() {
    return expression_->getLine();
}

void golite::IncDec::weedingPass(bool check_break, bool check_continue) {
    if(expression_->isIdentifier()) {
        golite::Identifier* identifier = static_cast<Identifier*>(expression_);
        if(identifier->isBlank()) {
            golite::Utils::error_message("Increment and decrement statement cannot have a blank expression",
                                         expression_->getLine());
        }
    }
    expression_->weedingPass(check_break, check_continue);
}