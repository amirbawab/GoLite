#ifndef GOLITE_DECLARATION_H
#define GOLITE_DECLARATION_H

#include <vector>
#include <golite/identifier.h>

namespace golite {
    class Declaration : public Simple {
    private:
        std::vector<Identifier*> left_identifiers_;
        std::vector<Expression*> right_expressions_;
    public:

        /**
         * Set identifiers
         * @param identifiers
         */
        void setIdentifiers(std::vector<Identifier*> identifiers) { left_identifiers_ = identifiers; }

        /**
         * Set expresions
         * @param expressions
         */
        void setExpressions(std::vector<Expression*> expressions) { right_expressions_ = expressions; }
    };
}

#endif
