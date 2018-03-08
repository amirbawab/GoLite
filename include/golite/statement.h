#ifndef GOLITE_STATEMENTS_STATEMENT_H
#define GOLITE_STATEMENTS_STATEMENT_H

#include <string>
#include <golite/type_component.h>
#include <golite/symbol_table.h>
#include <golite/declarable.h>

namespace golite {

    /**
     * Parent class for all kind of statements
     * - print
     * - println
     * - return
     * - break
     * - continue
     * - simple
     * - block
     * - for
     * - switch
     * - if
     */
    class Statement {
    public:

        /**
         * Convert to GoLite
         * @param indent
         * @return golite code
         */
        virtual std::string toGoLite(int indent) = 0;

        /**
         * Get line number
         * @return line number
         */
        virtual int getLine() = 0;

        /**
         * Perform a weeding pass
         * @param check_break
         * @param check_continue
         */
        virtual void weedingPass(bool check_break, bool check_continue) = 0;

        /**
         * Break statement overrides this function
         * @return true for break statements
         */
        virtual bool isBreak() { return false; }

        /**
         * Continue statement overrides this function
         * @return true for continue statements
         */
        virtual bool isContinue() { return false; }

        /**
         * If statement overrides this function
         * @return true for if statements
         */
        virtual bool isIf() { return false; }

        /**
         * For statement overrides this function
         * @return true for for statements
         */
        virtual bool isFor() { return false; }

        /**
         * Switch statement overrides this function
         * @return true for switch statements
         */
        virtual bool isSwitch() { return false; }

        /**
         * Block statement overrides this function
         * @return true for block statements
         */
        virtual bool isBlock() { return false; }

        /**
         * Assignment statement overrides this function
         * @return true for assignment statements
         */
        virtual bool isAssignment() { return false; }

        /**
         * Declaration statement overrides this function
         * @return true for declaration statements
         */
        virtual bool isDeclaration() { return false; }

        /**
         * Variable statement overrides this function
         * @return true for variable statements
         */
        virtual bool isStatVariable() { return false; }

        /**
         * Simple Expression statement overrides this function
         * @return true for simple expression statements
         */
        virtual bool isSimpleExpression() { return false; }

        /**
         * Perform type checking
         */
        virtual void typeCheck() = 0;

        /**
         * Perform symbol table check
         * @param root
         */
        virtual void symbolTablePass(SymbolTable* root) = 0;

        /**
         * Check if statement is return or will return in all cases
         * @param function
         * @return true if it does
         */
        virtual bool hasReturn(Declarable* function) { return false; }
    };
}

#endif