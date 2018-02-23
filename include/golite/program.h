#ifndef GOLITE_SCOPE_PROGRAM_H
#define GOLITE_SCOPE_PROGRAM_H

#include <golite/type_declarable.h>
#include <golite/block.h>
#include <string>

using namespace std;

namespace golite {

    /**
     * Singleton class
     *
     * Program instance and entry point to the input AST
     */
    class Program : public Block {
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
