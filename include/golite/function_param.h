#ifndef GOLITE_FUNCTION_PARAM_H
#define GOLITE_FUNCTION_PARAM_H

#include <string>
#include <vector>
#include <golite/type_component.h>

namespace golite {
    class FunctionParam {
    private:
        std::vector<std::string> names_;
        TypeComponent* type_component_;
    };
}

#endif
