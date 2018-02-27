#ifndef GOLITE_DECLARATION_H
#define GOLITE_DECLARATION_H

#include <vector>
#include <golite/identifier.h>

namespace golite {
    class Declaration : public Simple {
    private:
        std::vector<golite::Expression*> left_identifiers_;
        std::vector<golite::Expression*> right_expressions_;
    public:

        /**
         * @see Statement::getLine()
         */
        int getLine();

        /**
         * Set identifiers
         * @param identifiers
         */
        void setIdentifiers(std::vector<golite::Expression*> identifiers);

        /**
         * Set expresions
         * @param expressions
         */
        void setExpressions(std::vector<Expression*> expressions) { right_expressions_ = expressions; }

        /**
         * @see Statement::toGoLite(int)
         */
        std::string toGoLite(int indent);

        /**
         * @see Statement::isDeclaration()
         */
        bool isDeclaration() { return true; }

        /**
         * Bad equation
         * @return true if it is
         */
        bool badEquation();
    };
}

#endif
