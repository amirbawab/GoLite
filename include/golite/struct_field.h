#ifndef GOLITE_STRUCT_FIELD_H
#define GOLITE_STRUCT_FIELD_H

#include <vector>
#include <golite/type_component.h>
#include <golite/identifier.h>

namespace golite {
    class StructField {
    private:
        std::vector<Identifier*> identifiers_;
        TypeComponent* type_component_;
    };
}

#endif
