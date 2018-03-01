#include <golite/function.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>

std::string golite::Function::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "func " << identifier_->toGoLite(0)
       << "(" << golite::Pretty::implodeParams(params_, indent) << ") ";
    if(type_component_) {
        ss << type_component_->toGoLite(indent) << " ";
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

void golite::Function::weedingPass(bool check_break, bool check_continue) {
    identifier_->weedingPass(check_break, check_continue);

    for(FunctionParam* function_param : params_) {
        function_param->weedingPass(check_break, check_continue);
    }

    if(type_component_) {
        type_component_->weedingPass();
    }

    block_->weedingPass(check_break, check_continue);
}
