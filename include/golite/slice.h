#ifndef GOLITE_SLICE_H
#define GOLITE_SLICE_H

#include <golite/type_decorator.h>

namespace golite {
    class Slice : public TypeDecorator {
    public:
        Slice(golite::TypeComponent* type_component) : TypeDecorator(type_component){}

        /**
         * @see TypeComponent::toGoLite(int)
         */
        std::string toGoLite(int indent);
    };
}

#endif