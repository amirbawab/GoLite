#ifndef GOLITE_SCOPE_PROGRAM_H
#define GOLITE_SCOPE_PROGRAM_H

#include <string>
#include <golite/declarable.h>
#include <golite/identifier.h>

namespace golite {

    /**
     * Singleton class
     *
     * Program instance and entry point to the input AST
     */
    class Program {
    private:
        Identifier* package_name_;
        std::vector<Declarables*> declarables_;

    public:
        static Program* getInstance() {
            static Program* instance(new Program());
            return instance;
        }

        // Delete constructor and operator
        Program(Program const&) = delete;
        void operator=(Program const&) = delete;

        /**
         * Set package name
         * @param package_name
         */
        void setPackageName(string package_name) {package_name = package_name;}

        /**
         * Get package name
         * @return package name
         */
        std::string getPackageName() const { return package_name_; }
    };
}

#endif
