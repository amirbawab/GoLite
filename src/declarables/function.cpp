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
        if(!identifier_->isBlank()) {
            root->putSymbol(this->identifier_->getName(), this);
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
    static long count = 1;
    if (!identifier_->isBlank()) {

        // TypeScript initializer
        ss << type_component_->resolveFunc()->toTypeScriptInitializer(indent);
        for(size_t i=0; i < params_.size(); i++) {
            ss << params_[i]->toTypeScriptInitializer(indent);
        }

        // Generate function code
        std::string func_name;
        if(identifier_->getName() == golite::Program::INIT_FUNC_NAME) {
            func_name = "init_" + std::to_string(count++) + "_";
        }
        func_name += identifier_->toTypeScript(0);
        ss << golite::Utils::blockComment({"Function " + identifier_->getName() + " was renamed to "
                                           + func_name}, indent,
                                          identifier_->getLine()) << std::endl;
        ss << golite::Utils::indent(indent) << "function ";
        ss << func_name << "(";
        for(size_t i=0; i < params_.size(); i++) {
            if(i != 0) {
                ss << ", ";
            }
            ss << params_[i]->toTypeScript(indent);
        }
        ss << ")"
           << " : " << type_component_->resolveFunc()->toTypeScript(0) << " {";
        if (!block_->getStatements().empty()) {
            ss << std::endl;
            for (Statement *statement : block_->getStatements()) {
                ss << statement->toTypeScript(indent + 1) << std::endl;
            }
            ss << golite::Utils::indent(indent);
        }
        ss << "}" << std::endl;
        if(identifier_->getName() == golite::Program::INIT_FUNC_NAME) {
            ss << std::endl << golite::Utils::indent(indent) << "// Call init() function" << std::endl;
            ss << golite::Utils::indent(indent) << func_name << "();" << std::endl;
        }
    } else {
        ss << golite::Utils::codeNotGenerated(toGoLite(0), indent, getLine()) << std::endl;
    }
    return ss.str();
}