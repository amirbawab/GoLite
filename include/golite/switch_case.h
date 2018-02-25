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

        /**
         * Set expressions
         * @param expressions
         */
        void setExpressions(std::vector<Expression*> expressions) { expressions_ = expressions; }

        /**
         * Set statements
         * @param statements
         */
        void setStatements(std::vector<Statement*> statements) { statements_  = statements; }

        /**
         * Conver to GoLite
         * @param indent
         * @return golite code
         */
        std::string toGoLite(int indent);
    };
}

#endif