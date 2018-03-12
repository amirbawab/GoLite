#include <golite/function_call.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>
#include <golite/primary_expression.h>

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
    // TODO Rule 1
    // Rule 2: Type and expr resolve to numeric types
    can_cast = type->getTypeComponent()->resolvesToNumeric() && expression_type->resolvesToNumeric();

    // Rule 3: Type resolves to string type and expr resolves to an integer
    can_cast = type->getTypeComponent()->resolvesToString()
               && (expression_type->resolvesToInt() || expression_type->resolvesToRune());
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