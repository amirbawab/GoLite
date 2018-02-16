#ifndef GOLITE_STATEMENTS_DECLARABLES_TYPE_H
#define GOLITE_STATEMENTS_DECLARABLES_TYPE_H

#include <statements/declarables/declarable.h>

namespace Golite::Statement::Declarable {
    class TypeDeclarable : Declarable {
    protected:
        int dimension_;
        // TODO: kind
    };
}

#endif