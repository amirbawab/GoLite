#ifndef GOLITE_SIMPLE_EXPRESSION_H
#define GOLITE_SIMPLE_EXPRESSION_H

#include <golite/simple.h>
#include <golite/expression.h>

namespace golite {
    class SimpleExpression : public Simple {
    private:
        Expression* expression_;
    public:
        SimpleExpression(golite::Expression* expression) : expression_(expression) {}

        /**
         * @see Statement::isSimpleExpression()
         */
        bool isSimpleExpression() { return true; }

        /**
         * Get expression
         * @return expression
         */
        Expression* getExpression() const { return expression_; }

        /**
         * @see Statement::getLine()
         */
        int getLine();

        /**
         * @see Statement::toGoLite(int)
         */
        std::string toGoLite(int indent);

        /**
         * @see Statement::weedingPass()
         */
        void weedingPass(bool check_break, bool check_continue);

        /**
         * @see Statement::typeCheck()
         */
        void typeCheck();

        /*
         * @see Statement::symbolTablePass()
         */
        void symbolTablePass(SymbolTable* root);

        /**
         * @see Statement::toTypeScript()
         */
        std::string toTypeScript(int indent);
    };
}
#endif