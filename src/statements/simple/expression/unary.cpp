#include <golite/unary.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Unary::toGoLite(int indent) {
    std::stringstream ss;
    switch (kind_) {
        case MINUS:
            ss << "-";
            break;
        case NOT:
            ss << "!";
            break;
        case PLUS:
            ss << "+";
            break;
        case XOR:
            ss << "^";
            break;
    }
    ss << operand_->toGoLite(0);
    return ss.str();
}