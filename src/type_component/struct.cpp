#include <golite/struct.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Struct::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << " struct ";
    for(golite::StructField* field : fields_) {
        ss << field->toGoLite(indent+1);
    }
    return ss.str();
}