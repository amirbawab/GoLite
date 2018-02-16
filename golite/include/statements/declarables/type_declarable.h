#ifndef GOLITE_STATEMENTS_DECLARABLES_TYPE_H
#define GOLITE_STATEMENTS_DECLARABLES_TYPE_H

#include <statements/declarables/declarable.h>

namespace Golite::Statement::Declarable {
    enum TypeDeclarableKind {
        ARRAY,
        SLICE,
        CUSTOM,
        BUILTIN
    };

    class TypeDeclarable : Declarable {
    protected:
        int dimension_;
        TypeDeclarableKind kind_;
    };
}

#endif