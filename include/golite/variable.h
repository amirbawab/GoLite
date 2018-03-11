#ifndef GOLITE_STATEMENTS_VARIABLE_H
#define GOLITE_STATEMENTS_VARIABLE_H

#include <vector>
#include <string>
#include <golite/declarable.h>
#include <golite/identifier.h>
#include <golite/type.h>

namespace golite {
    /**
     * Variable declaration as a statement or a global declaration
     * var id ...
     */
    class Variable : public Declarable, public Statement {
    private:
        std::vector<Identifier*> identifiers_;
        std::vector<Expression*> expressions_;
    public:

        /**
         * Set identifiers
         * @param identifiers
         */
        void setIdentifiers(std::vector<Identifier*> identifiers) { identifiers_ = identifiers; }

        long indexOfIdentifier(std::string id);

        void replaceExpression(int index, Expression* expr);

        /**
         * Set expresions
         * @param expressions
         */
        void setExpressions(std::vector<Expression*> expressions) { expressions_ = expressions; }

        /**
         * @see Declarable::toGoLite(int)
         */
        std::string toGoLite(int indent);

        /**
         * @see Declarable::isDecVariable()
         */
        bool isDecVariable() { return true; }

        /**
         * @see Statement::isStatVariable()
         */
        bool isStatVariable() { return true; }

        /**
         * @see Statement::getLine()
         */
        int getLine();

        /**
         * @see Statement::weedingPass()
         */
        void weedingPass(bool check_break, bool check_continue);

        /**
         * @see Statement::typeCheck()
         */
        void typeCheck();

        /*
         * @see Declarable::symbolTablePass()
         */
        void symbolTablePass(SymbolTable* root);

        /**
         * @see Declarable::toPrettySymbol()
         */
        std::string toPrettySymbol();

        /**
         * Get identifiers
         * @return identifiers
         */
        std::vector<golite::Identifier*> getIdentifiers() { return identifiers_; }
    };
}

#endif
