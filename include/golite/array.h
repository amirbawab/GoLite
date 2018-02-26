#ifndef GOLITE_ARRAY_H
#define GOLITE_ARRAY_H

#include <golite/type_component.h>
#include <golite/literal.h>

namespace golite {
    class Array : public TypeComponent {
    private:
        golite::Literal<int>* size_;
    public:
        Array(golite::Literal<int>* size) : size_(size) {}

        /**
         * Get size
         * @return size
         */
        golite::Literal<int>* getSize() const { return size_; }

        /**
         * @see TypeComponent
         */
        std::string toGoLite(int indent);
    };
}

#endif