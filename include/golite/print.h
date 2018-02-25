#ifndef GOLITE_PRINT_H
#define GOLITE_PRINT_H

#include <golite/statement.h>
#include <golite/expression.h>
#include <vector>

namespace golite {
    class Print : public Statement {
    private:
        std::vector<golite::Expression*> expressions_;
    public:

        /**
         * Set expressions
         * @param expressions
         */
        void setExpressions(std::vector<golite::Expression*> expressions) { expressions_ = expressions; }

        /**
         * @see Statement::toGoLite(int)
         */
        std::string toGoLite(int indent);
    };
}

#endif