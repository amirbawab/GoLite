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
         * Get children
         * @return list of children
         */
        std::vector<golite::Primary*> getChildren() { return children_; }

        /**
         * @see Expression::toGoLite(int)
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
         * @see Expression::isBlank()
         */
        bool isBlank();

        /**
         * @see Expression::weedingPass()
         */
        void weedingPass();

        /**
         * @see Expression::typeCheck()
         */
        golite::TypeComponent* typeCheck();

        /**
         * @see Expression::symbolTablePass()
         */
        void symbolTablePass(SymbolTable* root);

        /**
         * @see Expression::isPrimaryExpression()
         */
        bool isPrimaryExpression() { return true; }

        /**
         * @see Expression::isParenthesis()
         */
        bool isParenthesis();
    };
}

#endif