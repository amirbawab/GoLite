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
    class Function : public Declarable {
    private:
        Identifier *identifier_ = nullptr;
        Block *block_ = nullptr;
        std::vector<FunctionParam *> params_;
    public:
        Function(Identifier *identifier) : identifier_(identifier) {}

        /**
         * Get identifier
         * @return identifier
         */
        Identifier *getIdentifier() const { return identifier_; }

        /**
         * Set function params
         * @param params
         */
        void setParams(std::vector<FunctionParam *> params) { params_ = params; }

        /**
         * Set block
         * @param block
         */
        void setBlock(Block *block) { block_ = block; }

        /**
         * Get block
         * @return block
         */
        Block *getBlock() const { return block_; }

        /**
         * @see Declarable::isFunction()
         */
        bool isFunction() { return true; }

        /**
         * @see Declarable::toGoLite(int)
         */
        std::string toGoLite(int indent);

        /**
         * @see Declarable::weedingPass()
         */
        void weedingPass(bool check_break, bool check_continue);

        /**
         * @see Declarable::typeCheck()
         */
        void typeCheck();

        /*
         * @see Declarable::symbolTablePass
         */
        void symbolTablePass(SymbolTable *root);

        /**
         * @see Declarable::toPrettySymbol()
         */
        std::string toPrettySymbol();

        /**
         * Get function parameters
         * @return params
         */
        std::vector<golite::FunctionParam *> getParams() { return params_; }

        /**
         * Get function parameters
         * @return params
         */
        std::vector<golite::FunctionParam *> getParamsSeparated();
    };
}

#endif
