#ifndef GOLITE_SCOPE_PROGRAM_H
#define GOLITE_SCOPE_PROGRAM_H

#include <golite/statements/declarables/type_declarable.h>
#include <golite/scope/scope.h>
#include <string>

using namespace std;

namespace golite {
    class Program : Scope {
    public:
        ~Program() {}

        static Program* getInstance() {
            static Program* instance(new Program());
            return instance;
        }

        // Delete constructor and operator
        Program(Program const&) = delete;
        void operator=(Program const&) = delete;

        void setPackageName(string package_name);
    private:
        Program();

        string package_name_;
    };
}

#endif