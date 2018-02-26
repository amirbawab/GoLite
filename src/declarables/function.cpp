#include <golite/function.h>
#include <golite/utils.h>
#include <sstream>
#include <iostream>

std::string golite::Function::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "func " << identifier_->toGoLite(0)
       << "(";
    for(size_t i = 0; i < params_.size(); i++) {
        if(i != 0) {
            ss << ", ";
        }
        ss << params_[i]->toGoLite(0);
    }
    ss << ") ";
    if(type_component_) {
        ss << type_component_->toGoLite(0) << " ";
    }
    ss << "{" << std::endl;
    for(Statement* statement : block_->getStatements()) {
        ss << statement->toGoLite(indent+1) << std::endl;
    }
    ss << "}";
    return ss.str();
}
