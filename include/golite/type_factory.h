#ifndef GOLITE_TYPE_FACTORY_H
#define GOLITE_TYPE_FACTORY_H

#include <string>
#include <golite/type.h>

namespace golite {
    class TypeFactory {
    public:
        static Type* createBuiltInType(std::string id);
    };
}

#endif