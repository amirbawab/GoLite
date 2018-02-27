#ifndef GOLITE_PRIMARY_EXPRESSION_H
#define GOLITE_PRIMARY_EXPRESSION_H

#include <vector>
#include <golite/expression.h>

namespace golite {
    class PrimaryExpression : public Expression {
    private:
        std::vector<golite::Expression*> children_;
    public:

        /**
         * Add child
         * @param child
         */
        void addChild(golite::Expression* child);

        /**
         * @see Statement::toGoLite(int)
         */
        std::string toGoLite(int indent);

        /**
         * Get line number
         * @return line number
         */
        int getLine();

        /**
         * @see Expression::isFunctionCall()
         */
        bool isFunctionCall();
    };
}

#endif