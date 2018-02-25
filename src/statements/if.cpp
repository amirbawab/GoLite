#include <golite/if.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::If::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "if ";
    if(simple_) {
        ss << simple_->toGoLite(0) << "; ";
    }
    ss << expression_->toGoLite(0) << " {" << std::endl;
    for(Statement* statement : block_->getStatements()) {
        ss << statement->toGoLite(indent+1) << std::endl;
    }
    ss << "}";
    return ss.str();
}