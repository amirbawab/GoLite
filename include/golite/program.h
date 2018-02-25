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
        Program(){}
        Identifier* package_name_;
        std::vector<Declarable*> declarables_;

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
        void setPackageName(Identifier* package_name) {package_name = package_name;}

        /**
         * Get package name
         * @return package name
         */
        Identifier* getPackageName() const { return package_name_; }

        /**
         * Set declarables
         * @param declarables
         */
        void setDeclarables(std::vector<Declarable*> declarables) { declarables_ = declarables; }

        /**
         * Convert to golite
         * @return golite code
         */
        std::string toGoLite();
    };
}

#endif
