#ifndef GOLITE_STATEMENTS_DECLARABLES_DECLARABLE_H
#define GOLITE_STATEMENTS_DECLARABLES_DECLARABLE_H

#include <golite/statement.h>
#include <string>

namespace golite {
    /**
     * Parent class of elements that can be created on the global scope (program scope)
     *
     * The following types can are declarable on the global scope:
     * - Types
     * - Variables
     * - Functions
     */
    class Declarable {
    protected:
        Declarable(std::string name) { this->name_ = name; }
        std::string name_;
    };
}

#endif
