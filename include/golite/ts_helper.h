#ifndef GOLITE_TS_HELPER_H
#define GOLITE_TS_HELOER_H

#include <golite/type_component.h>

namespace golite {
    class TSHelper{
    public:
        /**
         * Check if type is considered an Object in TypeScript
         * @param type_component
         * @return true if it is
         */
        static bool isObject(TypeComponent* type_component);
    };
}
#endif