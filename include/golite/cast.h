#ifndef GOLITE_CAST_H
#define GOLITE_CAST_H

#include <golite/primary.h>
#include <golite/type.h>

namespace golite {
    class Cast : public Primary {
        Type* type_;
        Expression* expression_;
    };
}

#endif