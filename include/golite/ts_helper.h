#ifndef GOLITE_TS_HELPER_H
#define GOLITE_TS_HELOER_H

#include <golite/type_component.h>

namespace golite {
    class TSHelper{
    private:
        static std::string clone_func_name_;
    public:
        /**
         * Check if type is considered an Object in TypeScript
         * @param type_component
         * @return true if it is
         */
        static bool isObject(TypeComponent* type_component);

        /**
         * Clone objects
         * @param type_component
         * @return clone objects
         */
        static std::string cloneObject(TypeComponent* type_component);

        /**
         * Generate code for print function
         * @param indent
         * @return code
         */
        static std::string codePrint(int indent);

        /**
         * Generate code for prnitln function
         * @param indent
         * @return code
         */
        static std::string codePrintln(int indent);

        /**
         * Generate code for constants
         * @param indent
         * @return code
         */
        static std::string codeConstants(int indent);

        /**
         * Generate code for Array interface
         * @param indent
         * @return code
         */
        static std::string codeArrayInterface(int indent);

        /**
         * Generate code for float point printer
         * @param indent
         * @return code
         */
        static std::string codeFloat(int indent);

        /**
         * Generate code for Slice class
         * @param indent
         * @return code
         */
        static std::string codeSlice(int indent);

        /**
         * Clone function call
         * @return code
         */
        static std::string getCloneCall();
    };
}
#endif