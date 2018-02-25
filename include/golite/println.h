#ifndef GOLITE_PRINTLN_H
#define GOLITE_PRINTLN_H

#include <golite/statement.h>

namespace golite {
    class Println : public Statement {
    private:
        std::vector<golite::Expression*> expressions_;
    public:

        /**
         * Set expressions
         * @param expressions
         */
        void setExpressions(std::vector<golite::Expression*> expressions) { expressions_ = expressions; }
    };
}

#endif