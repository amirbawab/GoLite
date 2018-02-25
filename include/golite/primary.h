#ifndef GOLITE_PRIMARY_H
#define GOLITE_PRIMARY_H

#include <vector>
#include <golite/expression.h>

namespace golite {
    class Primary : public Expression {
    private:
        std::vector<golite::Expression*> children_;
    public:

        /**
         * Add child
         * @param child
         */
        void addChild(golite::Expression* child);
    };
}

#endif