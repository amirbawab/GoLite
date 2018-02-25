#ifndef GOLITE_STRUCT_H
#define GOLITE_STRUCT_H

#include <vector>
#include <golite/type_component.h>
#include <golite/struct_field.h>

namespace golite {
    class Struct : public TypeComponent {
    private:
        std::vector<StructField*> fields_;
    public:

        /**
         * Set fields
         * @param fields
         */
        void setFields(std::vector<StructField*> fields) { fields_ = fields; }
    };
}

#endif
