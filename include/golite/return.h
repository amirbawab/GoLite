#ifndef GOLITE_RETURN_H
#define GOLITE_RETURN_H

#include <golite/expression.h>

namespace golite {
    class Return : public Statement {
    private:
        Expression* expression_ = nullptr;
        int line_;
    public:
        Return(int line) : line_(line) {}

        /**
         * @see Statement::getLine()
         */
        int getLine() { return line_; }

        /**
         * Set expression
         * @param expression
         */
        void setExpression(Expression* expression) { expression_ = expression;}

        /**
         * @see Statement::toGoLite(int)
         */
        std::string toGoLite(int indent);
    };
}

#endif