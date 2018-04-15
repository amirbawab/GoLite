#ifndef GOLITE_PRIMARY_EXPRESSION_H
#define GOLITE_PRIMARY_EXPRESSION_H

#include <vector>
#include <golite/primary.h>

namespace golite {
    class PrimaryExpression : public Expression {
    private:
        std::vector<golite::Primary*> children_;
        bool addressable_ = false;
        std::string name_;
    public:

        /**
         * Add child
         * @param child
         */
        void addChild(golite::Primary* child);

        /**
         * Get children
         * @return list of children
         */
        std::vector<golite::Primary*> getChildren() { return children_; }

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
         * @see Expression::isFunctionCall()
         */
        bool isFunctionCall();

        /**
         * @see Expression::isIdentifier()
         */
        bool isIdentifier();

        /**
         * @see Expression::isAppend()
         */
        bool isAppend();

        /**
         * @see Expression::isBlank()
         */
        bool isBlank();

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
         * @see Expression::isPrimaryExpression()
         */
        bool isPrimaryExpression() { return true; }

        /**
         * @see Expression::isParenthesis()
         */
        bool isParenthesis();

        /**
         * @see Expression::resolveExpression()
         */
        Expression* resolveExpression();

        /**
         * @see Expression::isLiteral()
         */
        bool isLiteral();

        /**
         * @see Expression::isCasting()
         */
        bool isCasting();

        /**
         * @see Expression::isAddressable()
         */
        bool isAddressable() { return addressable_; }

        /**
         * @see Expression::toTypeScript()
         */
        std::string toTypeScript(int indent);

        /**
         * @see Expression::toTypeScriptInitializer()
         */
        std::string toTypeScriptInitializer(int indent);
    };
}

#endif