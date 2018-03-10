#include <golite/function.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>
#include <golite/program.h>

std::string golite::Function::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "func " << identifier_->toGoLite(0)
       << "(" << golite::Pretty::implodeParams(params_, indent) << ") ";
    if(type_component_ != golite::Program::VOID_TYPE->getTypeComponent()) {
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
    identifier_->weedingPass();
    for(FunctionParam* function_param : params_) {
        function_param->weedingPass();
    }
    type_component_->weedingPass();
    block_->weedingPass(check_break, check_continue);
}

void golite::Function::typeCheck() {
    block_->typeCheck();
    if(type_component_ != golite::Program::VOID_TYPE->getTypeComponent() && !block_->hasReturn(this)) {
        golite::Utils::error_message("Function " + identifier_->getName() + " is missing a return statement",
                                     identifier_->getLine());
    }
}

void golite::Function::symbolTablePass(golite::SymbolTable *root) {
    if(root->hasSymbol(this->identifier_->getName(), false)) {
        golite::Utils::error_message("Function name " + identifier_->getName() + " redeclared in this block",
                                     identifier_->getLine()); // TODO: fix me. Amir: looks good to me!
    }

    for(FunctionParam* param : params_) {
        param->symbolTablePass(root);
    }

    if(type_component_ != Program::VOID_TYPE->getTypeComponent()) {
        type_component_->symbolTablePass(root);
    }
    root->putSymbol(this->identifier_->getName(), this);

    this->block_->symbolTablePass(root);
}

std::string golite::Function::toPrettySymbol() {
    std::stringstream ss;
    ss << identifier_->getName() << "[function]" << " = ";
    if(type_component_->isVoid()) {
        ss << "void";
    } else {
        ss << type_component_->toPrettySymbol();
    }
    return ss.str();
}