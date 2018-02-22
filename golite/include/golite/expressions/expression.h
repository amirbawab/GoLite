#ifndef GOLITE_EXPRESSIONS_EXPRESSION_H
#define GOLITE_EXPRESSIONS_EXPRESSION_H

namespace golite {
    class Expression {
    public:
        virtual ~Expression() = default;
    protected:
        explicit Expression() {};

        explicit Expression(int line_no) { this->line_ = line_no; }
        int line_;
    };
}

#endif