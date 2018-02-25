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
    };
}

#endif