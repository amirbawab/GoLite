#ifndef GOLITE_TYPE_DECORATOR_H
#define GOLITE_TYPE_DECORATOR_H

#include <golite/type_component.h>

namespace golite {
    class TypeDecorator : public TypeComponent {
    protected:
        TypeDecorator(TypeComponent* type_component) : type_component_(type_component){}
        TypeComponent* type_component_;
    };
}

#endif