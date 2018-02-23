#ifndef GOLITE_STATEMENTS_DECLARABLES_DECLARABLE_FACTORY_H
#define GOLITE_STATEMENTS_DECALRABLES_DECLARABLE_FACTORY_H

#include <string>

#include <golite/variable.h>
#include <golite/type.h>
#include <golite/struct.h>

namespace golite {
    class DeclarableFactory {
    public:
        // FIXME change parameters
        static Variable* createVarDecl(/*TODO*/);
        static Type* createTypeDecl(/*TODO*/);
    };
}

#endif
