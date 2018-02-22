#include <golite/statements/declarables/builtin.h>

using namespace golite;

TypeDeclarable* const BuiltIn::INT_TYPE = new TypeDeclarable("int", TypeDeclarableKind::BUILTIN);
TypeDeclarable* const BuiltIn::FLOAT_TYPE = new TypeDeclarable("float64", TypeDeclarableKind::BUILTIN);
TypeDeclarable* const BuiltIn::BOOL_TYPE = new TypeDeclarable("bool", TypeDeclarableKind::BUILTIN);
TypeDeclarable* const BuiltIn::RUNE_TYPE = new TypeDeclarable("rune", TypeDeclarableKind::BUILTIN);
TypeDeclarable* const BuiltIn::STRING_TYPE = new TypeDeclarable("string", TypeDeclarableKind::BUILTIN);

// TODO: edit this function so that the return type + parameters are correct
IdentifierExpression* const BuiltIn::APPEND_FN_ID = new IdentifierExpression("append", 0);
FunctionDeclarable* const BuiltIn::APPEND_FN = new FunctionDeclarable("append", nullptr, nullptr, nullptr);