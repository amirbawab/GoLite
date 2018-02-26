#include <golite/struct.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Struct::toGoLite(int indent) {
    std::stringstream ss;
    ss << "struct {";

    if(!fields_.empty()) {
        ss << std::endl;
        for(golite::StructField* field : fields_) {
            ss << field->toGoLite(indent+1) << std::endl;
        }
        ss << golite::Utils::indent(indent);
    }
    ss << "}";
    return ss.str();
}