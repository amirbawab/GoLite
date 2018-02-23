#ifndef GOLITE_FUNCTION_PARAM_H
#define GOLITE_FUNCTION_PARAM_H

#include <string>
#include <golite/type_declarable.h>

namespace golite {
    class FunctionParam {
    private:
        // Parameter name
        std::string name_;

        // TODO Fix type
        TypeDeclarable* type_;

    public:
        FunctionParam(std::string name) : name_(name) {}

        /**
         * Get parameter name
         * @return name
         */
        std::string getName() const {return name_;}
    };
}

#endif
