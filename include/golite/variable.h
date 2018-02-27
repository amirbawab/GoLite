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
        TypeComponent* type_component_ = nullptr;
        std::vector<Expression*> expressions_;
    public:

        /**
         * Set identifiers
         * @param identifiers
         */
        void setIdentifiers(std::vector<Identifier*> identifiers) { identifiers_ = identifiers; }

        /**
         * Set type component
         * @param type_component
         */
        void setTypeComponent(TypeComponent* type_component) { type_component_ = type_component; }

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
         * @see Declarable::isVariable()
         */
        bool isVariable() { return true; }

        /**
         * Bad equation
         * @return true if it is
         */
        bool badEquation();

        /**
         * @see Statement::getLine()
         */
        int getLine();
    };
}

#endif
