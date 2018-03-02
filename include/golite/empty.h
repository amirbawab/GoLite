#ifndef GOLITE_EMPTY_H
#define GOLITE_EMPTY_H

#include <golite/simple.h>

namespace golite {
    class Empty : public Simple {
    public:

        /**
         * @see Statement::toGoLite(int)
         */
        std::string toGoLite(int indent);

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
    };
}

#endif