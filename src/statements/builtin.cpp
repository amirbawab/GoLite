#include <golite/builtin.h>

golite::Type* const golite::BuiltIn::INT_TYPE = new golite::Type(new golite::Identifier("int", -1), nullptr);
golite::Type* const golite::BuiltIn::FLOAT_TYPE = new golite::Type(new golite::Identifier("float", -1), nullptr);
golite::Type* const golite::BuiltIn::BOOL_TYPE = new golite::Type(new golite::Identifier("boolean", -1), nullptr);
golite::Type* const golite::BuiltIn::RUNE_TYPE = new golite::Type(new golite::Identifier("rune", -1), nullptr);
golite::Type* const golite::BuiltIn::STRING_TYPE = new golite::Type(new golite::Identifier("string", -1), nullptr);

golite::Function* const golite::BuiltIn::APPEND_FN = new golite::Function(new golite::Identifier("append", -1));