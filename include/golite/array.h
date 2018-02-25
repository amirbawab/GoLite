#ifndef GOLITE_ARRAY_H
#define GOLITE_ARRAY_H

#include <golite/type_decorator.h>

namespace golite {
    class Array : public TypeDecorator {
    private:
        int size_;
    public:
        Array(golite::TypeComponent* type_component) : TypeDecorator(type_component) {}

        /**
         * Get size
         * @return size
         */
        int getSize() const { return size_; }

        /**
         * Set size
         * @param size
         */
        void setSize(int size) { size_ = size; }
    };
}

#endif