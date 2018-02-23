#ifndef GOLITE_LITERAL_H
#define GOLITE_LITERAL_H

#include <golite/primary.h>

namespace golite {
    template <class T>
    class Literal : public Primary {
    private:
        T value_;
    };
}

#endif
