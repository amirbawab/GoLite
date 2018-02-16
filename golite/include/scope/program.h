#ifndef GOLITE_SCOPE_PROGRAM_H
#define GOLITE_SCOPE_PROGRAM_H

#include <scope/scope.h>

namespace Golite::Scope {
    class Program : Scope {
    public:
        static Program& getInstance() {
            static Program instance;
            return instance;
        }

        Program(Program const&) = delete; // do not implement
        void operator=(Program const&) = delete; // do not implement
    private:
        Program();
    };
}

#endif