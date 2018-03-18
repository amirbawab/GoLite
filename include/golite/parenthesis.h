#ifndef GOLITE_EXPRESSIONS_PARENTHESIS_H
#define GOLITE_EXPRESSIONS_PARENTHESIS_H

#include <golite/primary.h>

namespace golite {
    class Parenthesis : public Primary {
    private:
        Expression* expression_ = nullptr;
    public:
        Parenthesis(Expression* expression) : expression_(expression) {}

        /**
         * Get expression
         * @return expression
         */
        Expression* getExpression() const { return expression_; }

        /**
         * Get non-parenthesis expression
         * @return expression
         */
        Expression* resolveExpression();

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
         * @see Expression::isParenthesis()
         */
        bool isParenthesis() { return true; }

        /**
         * @see Expression::isCasting()
         */
        bool isCasting();
    };
}

#endif
