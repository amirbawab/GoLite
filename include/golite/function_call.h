#ifndef GOLITE_EXPRESSIONS_FUNCTION_CALL_H
#define GOLITE_EXPRESSIONS_FUNCTION_CALL_H

#include <vector>
#include <golite/primary.h>

namespace golite {
    class FunctionCall : public Primary {
    private:
        std::vector<Expression*> args_;

    public:

        /**
         * Set arguments
         * @param args
         */
        void setArgs(std::vector<Expression*> args) { args_ = args; }

        /**
         * @see Statement::toGoLite(int)
         */
        std::string toGoLite(int indent);
    };
}

#endif
