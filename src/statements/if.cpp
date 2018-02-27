#include <golite/if.h>
#include <golite/utils.h>
#include <sstream>
#include <iostream>

std::string golite::If::toGoLite(int indent) {
    std::stringstream ss;

    // If statement
    ss << golite::Utils::indent(indent) << "if ";
    if(simple_) {
        ss << simple_->toGoLite(0) << "; ";
    }
    ss << expression_->toGoLite(0) << " {";

    // Statement body
    if(!block_->getStatements().empty()) {
        ss << std::endl;
        for(Statement* statement : block_->getStatements()) {
            ss << statement->toGoLite(indent+1) << std::endl;
        }
        ss << golite::Utils::indent(indent);
    }
    ss << "}";

    // Else if statements
    for(If* else_if : else_if_) {

        ss << " else if ";
        if(else_if->simple_) {
            ss << else_if->simple_->toGoLite(0) << "; ";
        }
        ss << else_if->expression_->toGoLite(0) << " {";

        // Statement body
        if(!else_if->block_->getStatements().empty()) {
            ss << std::endl;
            for(Statement* statement : else_if->block_->getStatements()) {
                ss << statement->toGoLite(indent+1) << std::endl;
            }
            ss << golite::Utils::indent(indent);
        }
        ss << "}";
    }

    // Else statement
    if(else_) {
        ss << " else {";
        if(!else_->getStatements().empty()) {
            ss << std::endl;
            for(Statement* statement : else_->getStatements()) {
                ss << statement->toGoLite(indent+1) << std::endl;
            }
            ss << golite::Utils::indent(indent);
        }
        ss << "}";
    }

    return ss.str();
}