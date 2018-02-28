#ifndef GOLITE_TYPE_COMPOSITE_H
#define GOLITE_TYPE_COMPOSITE_H

#include <string>
#include <vector>

namespace golite {
    class TypeComposite {
    public:

        /**
         * Convert to GoLite code
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
    };
}

#endif