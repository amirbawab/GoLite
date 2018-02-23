#ifndef GOLITE_EXPRESSIONS_EXPRESSION_H
#define GOLITE_EXPRESSIONS_EXPRESSION_H

namespace golite {
    /**
     * Parent class for all kind of expressions
     * - Primary
     * - Unary
     * - Binary
     * - Append (GoLite extra feature)
     */
    class Expression {
    public:
        virtual ~Expression() = default;
    protected:
        Expression() {};

        Expression(int line_no) { this->line_ = line_no; }
        int line_;
    };
}

#endif