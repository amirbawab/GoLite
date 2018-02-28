#include <golite/struct_field.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>

std::string golite::StructField::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << golite::Pretty::implodeIdentifiers(identifiers_);
    ss << " " << type_component_->toGoLite(indent) << ";";
    return ss.str();
}

void golite::StructField::weedingPass(bool check_break, bool check_continue) {
    for(Identifier* identifier : identifiers_) {
        identifier->weedingPass(check_break, check_continue);
    }
    type_component_->weedingPass(check_break, check_continue);
}