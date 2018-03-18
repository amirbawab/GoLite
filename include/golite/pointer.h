#ifndef GOLITE_POINTER_H
#define GOLITE_POINTER_H

#include <golite/type_component.h>

namespace golite {
    class Pointer : public TypeComposite {
    public:

        /**
         * Get type component
         * @return type component
         */
        virtual TypeComponent* getTypeComponent() = 0;

        /**
         * @see TypeComposite::isPointer()
         */
        bool isPointer() { return true; }
    };
}

#endif