#ifndef GOLITE_INC_DEC_H
#define GOLITE_INC_DEC_H

#include <golite/simple.h>
#include <golite/expression.h>

namespace golite {
    class IncDec : public Simple {
    private:

        // Expression to increment or decrement
        Expression* expression_;

        // Increment flag
        bool is_increment_ = true;
    public:
        IncDec(Expression* expression, bool is_increment) :
                expression_(expression), is_increment_(is_increment){}

        /**
         * Check if the statement is increment
         * @return true if increment, false if decrement
         */
        bool isIncrement() const { return is_increment_; }

        /**
         * Get expression
         * @return expression
         */
        Expression* getExpression() const { return expression_; }

        /**
         * @see Statement::toGoLite(int)
         */
        std::string toGoLite(int indent);
    };
}

#endif