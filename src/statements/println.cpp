#include <golite/println.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Println::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "println(";
    for(size_t i = 0; i < expressions_.size(); i++) {
        if(i != 0) {
            ss << ", ";
        }
        ss << expressions_[i]->toGoLite(indent);
    }
    ss << ");";
    return ss.str();
}
