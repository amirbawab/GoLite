#ifndef GOLITE_EXPRESSIONS_EXPRESSION_H
#define GOLITE_EXPRESSIONS_EXPRESSION_H

#include <string>
#include <golite/type_component.h>
#include <golite/symbol_table.h>

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

        /**
         * Check if expression is a primary expression
         * @return true if it is
         */
        virtual bool isPrimaryExpression() { return false; }

        /**
         * Check if expression is a binary expression
         * @return true if it is
         */
        virtual bool isBinary() { return false; }

        /**
         * Check if expression is a unary expression
         * @return true if it is
         */
        virtual bool isUnary() { return false; }

        /**
         * Check if expression is a function call
         * @return true if it is
         */
        virtual bool isFunctionCall() { return false; }

        /**
         * Check if expression is a type casting
         * @return true if it is
         */
        virtual bool isTypeCasting() { return false; }

        /**
         * Check if expression is an identifier
         * @return true if it is
         */
        virtual bool isIdentifier() { return false; }

        /**
         * Check if expression is a blank identifier
         * @return true if it is
         */
        virtual bool isBlank() { return false; }

        /**
         * Check if expression is a parenthesis
         * @return true if it is
         */
        virtual bool isParenthesis() { return false; }

        /**
         * Get line number
         * @return line number
         */
        virtual int getLine() = 0;

        /**
         * Perform type checking
         * @return type component ptr
         */
        virtual TypeComponent* typeCheck() = 0;

        /**
         * Perform weeding pass
         */
        virtual void weedingPass() = 0;

        /**
         * Generate GoLite code
         * @param indent
         * @return golite code
         */
        virtual std::string toGoLite(int indent) = 0;

        /**
         * Perform symbol table check
         * @param root
         */
        virtual void symbolTablePass(SymbolTable* root) = 0;

        /**
         * Resolve expression in parenthesis
         * @return a non-parenthesis expression
         */
        virtual Expression* resolveExpression() { return this; };

        /**
         * Check if exprssion is a literal
         * @return true if it is
         */
        virtual bool isLiteral() { return false; }
    };
}

#endif