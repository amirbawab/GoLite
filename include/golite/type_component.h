#ifndef GOLITE_TYPE_COMPONENT_H
#define GOLITE_TYPE_COMPONENT_H

#include <string>

namespace golite {
    class TypeComponent {
    public:
        virtual std::string toGoLite(int indent) = 0;
    };
}

#endif