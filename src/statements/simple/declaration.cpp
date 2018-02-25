#include <golite/declaration.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Declaration::toGoLite(int indent) {
    std::stringstream ss;
    for(size_t i = 0; i < left_identifiers_.size(); i++) {
        if(i != 0) {
            ss << ", ";
        }
        ss << left_identifiers_[i]->toGoLite(0);
    }
    ss << " := ";
    for(size_t i = 0; i < right_expressions_.size(); i++) {
        if(i != 0) {
            ss << ", ";
        }
        ss << right_expressions_[i]->toGoLite(0);
    }
    return ss.str();
}