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
         * Get fields
         * @return fields
         */
        std::vector<StructField*> getFields() { return fields_; }
    };
}

#endif
