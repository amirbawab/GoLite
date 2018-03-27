#ifndef GOLITE_DECLARABLE_FACTORY_H
#define GOLITE_DECLARABLE_FACTORY_H

#include <string>
#include <golite/type.h>
#include <golite/variable.h>

namespace golite {
    class DeclarableFactory {
    public:
        /**
         * Create built-in type
         * @param id
         * @return type ptr
         */
        static Type* createBuiltInType(std::string id);

        /**
         * Create a constant variable
         * @param id
         * @return var ptr
         */
        static Variable* createConstant(std::string id, TypeComponent* type_component);
    };
}

#endif