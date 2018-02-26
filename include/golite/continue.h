#ifndef GOLITE_CONTINUE_H
#define GOLITE_CONTINUE_H

#include <golite/statement.h>

namespace golite {
    class Continue : public Statement {
    public:
        /**
         * @see Statement::toGoLite(int)
         */
        std::string toGoLite(int indent);

        /**
         * @see Statement::Continue
         */
        bool isContinue() { return true; }
    };
}

#endif