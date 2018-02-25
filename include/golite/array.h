#ifndef GOLITE_ARRAY_H
#define GOLITE_ARRAY_H

#include <golite/type_decorator.h>
#include <golite/literal.h>

namespace golite {
    class Array : public TypeDecorator {
    private:
        golite::Literal<int>* size_;
    public:
        Array(golite::TypeComponent* type_component, golite::Literal<int>* size) :
                TypeDecorator(type_component), size_(size) {}

        /**
         * Get size
         * @return size
         */
        golite::Literal<int>* getSize() const { return size_; }
    };
}

#endif