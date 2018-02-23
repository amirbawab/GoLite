#include <golite/builtin.h>

golite::Type* const golite::BuiltIn::INT_TYPE = new golite::Type();
golite::Type* const golite::BuiltIn::FLOAT_TYPE = new golite::Type();
golite::Type* const golite::BuiltIn::BOOL_TYPE = new golite::Type();
golite::Type* const golite::BuiltIn::RUNE_TYPE = new golite::Type();
golite::Type* const golite::BuiltIn::STRING_TYPE = new golite::Type();

golite::Function* const golite::BuiltIn::APPEND_FN = new golite::Function();