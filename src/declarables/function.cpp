#include <golite/function.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>
#include <golite/program.h>
#include <golite/func.h>
#include <iostream>

std::string golite::Function::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "func " << identifier_->toGoLite(0)
       << "(" << golite::Pretty::implodeParams(params_, indent) << ") ";
    if(!type_component_->resolveFunc()->isVoid()) {
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
    block_->checkReturn(this);
    if(!type_component_->resolveFunc()->isVoid() && !block_->isTerminating()) {
        golite::Utils::error_message("Function " + identifier_->toGoLite(0) + " is not terminating",
                                     identifier_->getLine());
    }
}

void golite::Function::symbolTablePass(golite::SymbolTable *root) {

    // Init function can be redeclared
    if(identifier_->getName() == Program::INIT_FUNC_NAME) {
        if(!params_.empty()) {
            golite::Utils::error_message("Init function cannot have parameters", identifier_->getLine());
        }
        if(!type_component_->resolveFunc()->isVoid()) {
            golite::Utils::error_message("Init function must be void", identifier_->getLine());
        }
        type_component_ = new TypeComponent({ new golite::Func(this, Program::UNMAPPED_TYPE->getTypeComponent())});
        root->putInit(this);
        identifier_->setSymbolTable(root);
    } else {
        if(root->hasSymbol(this->identifier_->getName(), false)) {
            golite::Utils::error_message("Function name " + identifier_->toGoLite(0) + " redeclared in this block",
                                         identifier_->getLine());
        }
        if(identifier_->getName() == Program::MAIN_FUNC_NAME) {
            if(!params_.empty()) {
                golite::Utils::error_message("Main function cannot have parameters", identifier_->getLine());
            }
            if(!type_component_->resolveFunc()->isVoid()) {
                golite::Utils::error_message("Main function must be void", identifier_->getLine());
            }
        }
        root->putSymbol(this->identifier_->getName(), this);
        if(!identifier_->isBlank()) {
            identifier_->symbolTablePass(root);
        }
    }

    SymbolTable* function_block_table = new SymbolTable(root, "_func_" + identifier_->getName());
    for(FunctionParam* param : params_) {
        param->getTypeComponent()->symbolTablePass(root);
    }
    for(FunctionParam* param : params_) {
        param->symbolTablePass(function_block_table);
    }

    if(!type_component_->resolveFunc()->isVoid()) {
        type_component_->symbolTablePass(root);
    }

    this->block_->symbolTablePass(function_block_table);
}

std::string golite::Function::toPrettySymbol() {
    std::stringstream ss;
    ss << identifier_->getName() << " [function] = ";
    ss << type_component_->toPrettySymbol();
    return ss.str();
}

std::vector<golite::FunctionParam*> golite::Function::getParamsSeparated() {
    std::vector<FunctionParam*> separated_params;
    for(FunctionParam* param : params_) {
        for(Identifier* identifier : param->getIdentifier()) {
            FunctionParam* p = new FunctionParam();
            p->setIdentifiers({identifier});
            p->setTypeComponent(param->getTypeComponent());
            separated_params.push_back(p);
        }
    }
    return separated_params;
}

int golite::Function::getLine() {
    return identifier_->getLine();
}

std::string golite::Function::toTypeScript(int indent) {
    std::stringstream ss;
    if (!identifier_->isBlank()) {
        ss << golite::Utils::blockComment(
                {
                        "Function " + identifier_->getName() + " was renamed to " + identifier_->toTypeScript(0)
                }, indent, identifier_->getLine()) << std::endl;
        ss << golite::Utils::indent(indent) << "function " << identifier_->toTypeScript(0)
           << "(" << ")"
           << " : " << type_component_->toTypeScript(0) << " {";
        if (!block_->getStatements().empty()) {
            ss << std::endl;
            for (Statement *statement : block_->getStatements()) {
                ss << statement->toTypeScript(indent + 1) << std::endl;
            }
            ss << golite::Utils::indent(indent);
        }
        ss << "}";
    } else {
        ss << golite::Utils::codeNotGenerated(toGoLite(0), indent, getLine());
    }
    ss << std::endl;
    return ss.str();
}