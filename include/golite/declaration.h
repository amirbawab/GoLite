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
         * Get left identifiers
         * @return left identifiers
         */
        std::vector<Identifier*> getLeftIdentifiers() const { return left_identifiers_;}

        /**
         * Get right expressions
         * @return right expressions
         */
        std::vector<Expression*> getRightExpressions() const { return right_expressions_; }

        /**
         * Get assignment kind
         * @return assignment kind
         */
        KIND getKind() const {return kind_;}

        /**
         * Set assignment kind
         * @param kind
         */
        void setKind(KIND kind) { kind_ = kind; }
    };
}

#endif
