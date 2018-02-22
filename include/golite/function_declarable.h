#ifndef GOLITE_STATEMENTS_DECLARABLES_FUNCTION_H
#define GOLITE_STATEMENTS_DECLARABLES_FUNCTION_H

#include <vector>
#include <string>

#include <golite/statements/declarables/declarable.h>
#include <golite/statements/declarables/type_declarable.h>
#include <golite/statements/declarables/variable_declarable.h>
#include <golite/scope/scope.h>

namespace golite {
    class FunctionDeclarable : public Declarable {
    public:
        FunctionDeclarable(std::string name,
                           TypeDeclarable* return_type,
                           Scope* body,
                           std::vector<VariableDeclarable*>* params) : Declarable(name) {
            this->return_type_ = return_type;
            this->body_ = body;
            this->params_ = params;
        }
    protected:
        TypeDeclarable* return_type_;
        Scope* body_;
        std::vector<VariableDeclarable*>* params_;
    };
}

#endif