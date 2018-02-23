#ifndef GOLITE_IDENTIFIER_H
#define GOLITE_IDENTIFIER_H

#include <golite/primary.h>

namespace golite {
    class Identifier : public Primary {
    private:
        std::string name_;
    public:

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