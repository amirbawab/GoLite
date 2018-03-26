#include <golite/function_call.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>
#include <golite/primary_expression.h>
#include <golite/ts_helper.h>

std::string golite::FunctionCall::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "(" << golite::Pretty::implodeExpressions(args_) << ")";
    return ss.str();
}

void golite::FunctionCall::weedingPass() {
    for(Expression* expression : args_) {
        if(expression->isBlank()) {
            golite::Utils::error_message("Function call does not accept blank identifier as argument",
                                         expression->getLine());
        }
        expression->weedingPass();
    }
}

golite::TypeComponent* golite::FunctionCall::typeCheck() {
    // Note: Type check for parameters is done in checkParams()
    return nullptr;
}

void golite::FunctionCall::checkParams(Function* function) {
    std::vector<FunctionParam*> params = function->getParamsSeparated();
    if(params.size() != args_.size()) {
        golite::Utils::error_message("Number of arguments in function call " + function->getIdentifier()->getName() + " does not match function definition",
                                     getLine());
    }
    for(size_t i=0; i < params.size(); i++) {
        TypeComponent* arg_type = args_[i]->typeCheck();
        if(!params[i]->getTypeComponent()->isCompatible(arg_type)) {
            golite::Utils::error_message("Parameter at index " + std::to_string(i) + " expects "
                                         + params[i]->getTypeComponent()->toGoLiteMin() + " but given "
                                         + arg_type->toGoLiteMin(), args_[i]->getLine());
        }
    }
}

void golite::FunctionCall::checkParams(golite::Type *type) {
    if(args_.size() != 1) {
        golite::Utils::error_message("Conversion expects 1 argument", getLine());
    }
    Expression* expression = args_.back();
    TypeComponent* expression_type = expression->typeCheck();

    bool can_cast = false;
    // Rule 1: type and expr resolve to identical underlying types
    TypeComponent* type_component = new TypeComponent(type->getTypeComponent()->resolveChildren());
    TypeComponent* expr_component = new TypeComponent(expression_type->resolveChildren());
    can_cast |= type_component->isCompatible(expr_component);

    // Rule 2: Type and expr resolve to numeric types
    can_cast |= type->getTypeComponent()->resolvesToNumeric() && expression_type->resolvesToNumeric();

    // Rule 3: Type resolves to string type and expr resolves to an integer
    can_cast |= type->getTypeComponent()->resolvesToString() && expression_type->resolvesToInteger();
    if(!can_cast) {
        golite::Utils::error_message("Cannot convert " + expression_type->toGoLiteMin()
                                     + " to " + type->getTypeComponent()->toGoLiteMin(), getLine());
    }
}

void golite::FunctionCall::symbolTablePass(SymbolTable *root) {
    for(Expression* arg : args_) {
        arg->symbolTablePass(root);
    }
}

std::string golite::FunctionCall::toTypeScript(int indent) {
    std::stringstream ss;
    ss << "(";
    for(size_t i=0; i < args_.size(); i++) {
        if(i != 0) {
            ss << ", ";
        }
        ss << args_[i]->toTypeScript(0);
        if(golite::TSHelper::isObject(args_[i]->typeCheck())) {
            ss << ".clone()";
        }
    }
    ss << ")";
    return ss.str();
}

std::string golite::FunctionCall::toTypeScriptInitializer(int indent) {
    std::stringstream ss;
    for(Expression* arg : args_) {
        ss << arg->toTypeScriptInitializer(indent);
    }
    return ss.str();
}