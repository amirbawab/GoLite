#ifndef GOLITE_STATEMENTS_DECLARABLES_STRUCT_H
#define GOLITE_STATEMENTS_DECLARABLES_STRUCT_H

#include <string>
#include <vector>
#include <golite/declarable.h>
#include <golite/variable_declarable.h>

namespace golite {
    class StructDeclarable : public Declarable {
    public:
        StructDeclarable(std::string name, std::vector<VariableDeclarable*>* vars, StructDeclarable* nested = nullptr): Declarable(name) {
            this->variables_ = vars;
            this->nested_struct_ = nested;
        }

        void setNestedStruct(StructDeclarable* nested) {
            this->nested_struct_ = nested;
        }

        void setName(std::string name) {
            this->name_ = name;
        }
    protected:
        std::vector<VariableDeclarable*>* variables_;
        StructDeclarable* nested_struct_;
    };
}

#endif
