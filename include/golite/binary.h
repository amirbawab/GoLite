#ifndef GOLITE_EXPRESSIONS_BINARY_H
#define GOLITE_EXPRESSIONS_BINARY_H

#include <golite/expression.h>

namespace golite {

    /**
     * Class representing a binary expression
     *
     * binary_expression: <expr> <operator> <expr>
     * operator:
     *   +
     *   -
     *   *
     *   /
     *   %
     *   &
     *   |
     *   ^
     *   &^
     *   <<
     *   >>
     *   ==
     *   !=
     *   <
     *   >
     *   <=
     *   >=
     *   &&
     *   ||
     */
    class Binary : public Expression {
    public:

        /**
         * Kind of binary expressions
         */
        enum KIND {
            MINUS,
            PLUS,
            MULTIPLY,
            DIVIDE,
            MODULO,
            BIT_AND,
            BIT_OR,
            BIT_XOR,
            BIT_CLEAR,
            LEFT_SHIFT,
            RIGHT_SHIFT,
            IS_EQUAL,
            IS_NOT_EQUAL,
            LESS_THAN,
            LESS_THAN_EQUAL,
            GREATER_THAN,
            GREATER_THAN_EQUAL,
            AND,
            OR
        };

        /**
         * Binary expression constructor
         * @param lhs
         * @param rhs
         * @param kind
         */
        Binary(Expression* lhs, Expression* rhs, KIND kind) : left_operand_(lhs), right_operand_(rhs), kind_(kind) {}

        /**
         * Get left operand
         * @return left operand
         */
        Expression* getLeftOperand() const {return left_operand_; }

        /**
         * Get right operand
         * @return right operand
         */
        Expression* getRightOperand() const {return right_operand_; }

        /**
         * Get operation kind
         * @return type of the binary operation
         */
        KIND getKind() const { return kind_; }

        /**
         * @see Expression::toGoLite()
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

        /**
         * @see Expression::isBinary()
         */
        bool isBinary() { return true; }

        /**
         * @see Expression::toTypeScript()
         */
        std::string toTypeScript(int indent);

        /**
         * @see Expression::toTypeScriptInitializer()
         */
        std::string toTypeScriptInitializer(int indent);

    private:

        // expression + ...
        Expression* left_operand_ = nullptr;

        // ... + expression
        Expression* right_operand_ = nullptr;

        // Binary expression type
        KIND kind_;

        // Left operand function name
        std::string left_func_name_;

        // Right operand function name
        std::string right_func_name_;
    };
}

#endif
