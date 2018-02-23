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
         * Get arguments
         * @return arguments
         */
        std::vector<Expression*> getArgs() { return args_;}
    };
}

#endif
