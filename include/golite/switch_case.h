#ifndef GOLITE_SWITCH_CASE_H
#define GOLITE_SWITCH_CASE_H

#include <vector>
#include <golite/expression.h>

namespace golite {
    class SwitchCase {
    private:
        std::vector<Expression*> expressions_;
        std::vector<Statement*> statements_;
    public:

        /**
         * Check if default case
         * @return true if default case
         */
        bool isDefault() {
            return expressions_.empty();
        }
    };
}

#endif