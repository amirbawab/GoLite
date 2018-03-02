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
         * @see Statement::toGoLite(int)
         */
        std::string toGoLite(int indent);

        /**
         * Get line number
         * @return line number
         */
        int getLine();

        /**
         * @see Statement::weedingPass()
         */
        void weedingPass(bool check_break, bool check_continue);

        /**
         * @see Statement::typeCheck()
         */
        golite::TypeComponent* typeCheck();
    };
}

#endif
