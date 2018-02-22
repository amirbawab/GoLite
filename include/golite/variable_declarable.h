#ifndef GOLITE_STATEMENTS_DECLARABLES_VARIABLE_H
#define GOLITE_STATEMENTS_DECLARABLES_VARIABLE_H

#include <string>

#include <golite/declarable.h>
#include <golite/type_declarable.h>

namespace golite {
    class VariableDeclarable : public Declarable {
    public:
        VariableDeclarable(std::string name, TypeDeclarable* type) : Declarable(name) {
            this->type_ = type;
        }
    protected:
        TypeDeclarable* type_;
    };
}

#endif
