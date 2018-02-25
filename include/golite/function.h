#ifndef GOLITE_STATEMENTS_FUNCTION_H
#define GOLITE_STATEMENTS_FUNCTION_H

#include <vector>
#include <string>

#include <golite/declarable.h>
#include <golite/type_component.h>
#include <golite/block.h>
#include <golite/function_param.h>
#include <golite/identifier.h>

namespace golite {
    /**
     * Class representing a function declaration on the global scope
     *
     * func main([params]) [type] {[statements]}
     */
    class Function : public Declarable, public Statement {
    private:
        Identifier* identifier_;
        TypeComponent* type_component_;
        Block* block_;
        std::vector<FunctionParam*> params_;
    public:
        Function(Identifier* identifier) : identifier_(identifier){}

        /**
         * Set function params
         * @param params
         */
        void setParams(std::vector<FunctionParam*> params) { params_ = params; }

        /**
         * Set block
         * @param block
         */
        void setBlock(Block* block) { block_ = block; }

        /**
         * Set type component
         * @param type_component
         */
        void setTypeComponent(golite::TypeComponent* type_component) { type_component_ = type_component; }
    };
}

#endif
