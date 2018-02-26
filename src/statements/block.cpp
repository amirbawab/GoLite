#include <golite/block.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Block::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "{";
    if(!statements_.empty()) {
        ss << std::endl;
        for(Statement* statement : statements_) {
            ss << statement->toGoLite(indent+1) << std::endl;
        }
        ss << golite::Utils::indent(indent);
    }
    ss << "}";
    return ss.str();
}