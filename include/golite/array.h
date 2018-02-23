#ifndef GOLITE_ARRAY_H
#define GOLITE_ARRAY_H

#include <golite/type_decorator.h>

namespace golite {
    class Array : public TypeDecorator {
    private:
        int size_;
    public:
        /**
         * Get size
         * @return size
         */
        int getSize() const { return size; }

        /**
         * Set size
         * @param size
         */
        void setSize(int size) { size_ = size; }
    };
}

#endif