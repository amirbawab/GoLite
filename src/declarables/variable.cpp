#include <golite/variable.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Variable::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "var " << "identifiers";
    if(!expressions_.empty()) {
        ss << " = ";
    }
    for(Expression* expression : expressions_) {
        // FIXME implement toGoLite()
//        ss << expression->toGoLite(0);
    }
    return ss.str();
}