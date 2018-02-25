#include <golite/append.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Append::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "append( "
       << left_expression_->toGoLite(0) << ", "
       << right_expression_->toGoLite(0) << " );";
    return ss.str();
}