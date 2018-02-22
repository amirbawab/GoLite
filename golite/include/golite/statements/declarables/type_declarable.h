#ifndef GOLITE_STATEMENTS_DECLARABLES_TYPE_H
#define GOLITE_STATEMENTS_DECLARABLES_TYPE_H

#include <string>

#include <golite/statements/declarables/declarable.h>

namespace golite {
    enum TypeDeclarableKind {
        ARRAY_CUSTOM,
        SLICE_CUSTOM,
        CUSTOM,
        BUILTIN
    };

    class TypeDeclarable : public Declarable {
    public:
        TypeDeclarable(std::string name, TypeDeclarableKind kind = CUSTOM, int dimension = 0): Declarable(name) {
            this->dimension_ = dimension;
            this->kind_ = kind;
        };
    protected:
        int dimension_;
        TypeDeclarableKind kind_;
    };
}

#endif