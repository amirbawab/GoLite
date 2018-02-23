#ifndef GOLITE_STATEMENTS_DECLARABLES_TYPE_H
#define GOLITE_STATEMENTS_DECLARABLES_TYPE_H

#include <string>
#include <golite/declarable.h>
#include <golite/statement.h>
#include <golite/type_component.h>

namespace golite {
    class Type : public Declarable, public Statement {
    private:
        std::string name_;
        TypeComponent* type_component_;
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

        /**
         * Get tyep component
         * @return type component
         */
        TypeComponent* getTypeComponent() const { return type_component_; }

        /**
         * Set type component
         * @param type_component
         */
        void setTypeComponent(TypeComponent* type_component) { type_component_ = type_component; }
    };
}

#endif
