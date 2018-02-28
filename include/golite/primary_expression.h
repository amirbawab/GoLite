#ifndef GOLITE_PRIMARY_EXPRESSION_H
#define GOLITE_PRIMARY_EXPRESSION_H

#include <vector>
#include <golite/primary.h>

namespace golite {
    class PrimaryExpression : public Expression {
    private:
        std::vector<golite::Primary*> children_;
    public:

        /**
         * Add child
         * @param child
         */
        void addChild(golite::Primary* child);

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

        /**
         * @see Expression::isIdentifier()
         */
        bool isIdentifier();

        /**
         * @see Statement::weedingPass()
         */
        void weedingPass(bool check_break, bool check_continue);
    };
}

#endif