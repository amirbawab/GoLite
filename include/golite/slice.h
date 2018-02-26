#ifndef GOLITE_SLICE_H
#define GOLITE_SLICE_H

#include <golite/type_component.h>

namespace golite {
    class Slice : public TypeComponent {
    public:

        /**
         * @see TypeComponent::toGoLite(int)
         */
        std::string toGoLite(int indent);
    };
}

#endif