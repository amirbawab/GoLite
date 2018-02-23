#ifndef GOLITE_STATEMENTS_DECLARABLES_FUNCTION_H
#define GOLITE_STATEMENTS_DECLARABLES_FUNCTION_H

#include <vector>
#include <string>

#include <golite/declarable.h>
#include <golite/type_declarable.h>
#include <golite/variable_declarable.h>
#include <golite/block.h>
#include <golite/function_param.h>

namespace golite {
    /**
     * Class representing a function declaration on the global scope
     *
     * func main([params]) [type] {[statements]}
     */
    class FunctionDeclarable : public Declarable {
    public:
        FunctionDeclarable(std::string name,
                           TypeDeclarable* return_type,
                           Block* body,
                           std::vector<FunctionParam*>* params) : Declarable(name) {
            this->return_type_ = return_type;
            this->body_ = body;
            this->params_ = params;
        }
    protected:
        // TODO Change type
        TypeDeclarable* return_type_;
        Block* body_;
        std::vector<FunctionParam*>* params_;
    };
}

#endif
