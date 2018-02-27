#ifndef GOLITE_STRUCT_H
#define GOLITE_STRUCT_H

#include <vector>
#include <golite/type_composite.h>
#include <golite/struct_field.h>

namespace golite {
    class Struct : public TypeComposite {
    private:
        std::vector<StructField*> fields_;
        int line_;
    public:
        Struct(int line) : line_(line) {}

        /**
         * @see TypeComposite::getLine()
         */
        int getLine() { return line_; }

        /**
         * Set fields
         * @param fields
         */
        void setFields(std::vector<StructField*> fields) { fields_ = fields; }

        /**
         * @see TypeComponent::toGoLite(int)
         */
        std::string toGoLite(int indent);
    };
}

#endif
