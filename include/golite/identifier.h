#ifndef GOLITE_IDENTIFIER_H
#define GOLITE_IDENTIFIER_H

#include <string>
#include <golite/primary.h>

namespace golite {
    class Identifier : public Primary {
    private:
        std::string name_;
    public:
        Identifier(std::string name) : name_(name) {}

        /**
         * Get name
         * @return name
         */
        std::string getName() const { return name_; }

        /**
         * Set name
         * @param name
         */
        void setName(std::string name) { name_ = name; }
    };
}

#endif