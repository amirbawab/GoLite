#include <golite/builtin.h>

golite::Type* const golite::BuiltIn::INT_TYPE = new golite::Type(new golite::Identifier("int"), nullptr);
golite::Type* const golite::BuiltIn::FLOAT_TYPE = new golite::Type(new golite::Identifier("float"), nullptr);
golite::Type* const golite::BuiltIn::BOOL_TYPE = new golite::Type(new golite::Identifier("boolean"), nullptr);
golite::Type* const golite::BuiltIn::RUNE_TYPE = new golite::Type(new golite::Identifier("rune"), nullptr);
golite::Type* const golite::BuiltIn::STRING_TYPE = new golite::Type(new golite::Identifier("string"), nullptr);

golite::Function* const golite::BuiltIn::APPEND_FN = new golite::Function(new golite::Identifier("append"));