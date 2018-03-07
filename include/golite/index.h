#ifndef GOLITE_EXPRESSIONS_INDEX_H
#define GOLITE_EXPRESSIONS_INDEX_H

#include <golite/primary.h>

namespace golite {
    class Index : public Primary {
    private:
        Expression* expression_ = nullptr;
    public:
        Index(Expression* expression) : expression_(expression) {}

        /**
         * Set expression
         * @param expression
         */
        void setExpression(Expression* expression) { expression_ = expression; }

        /**
         * Get expression
         * @return expression
         */
        Expression* getExpression() const { return expression_; }

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
         * @see Statement::symbolTablePass()
         */
        void symbolTablePass(SymbolTable* root);
    };
}

#endif
