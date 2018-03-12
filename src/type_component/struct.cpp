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

std::string golite::Struct::toGoLiteMin() {
    std::stringstream ss;
    ss << "struct {";
    if(!fields_.empty()) {
        for(golite::StructField* field : fields_) {
            ss << " " << field->toGoLiteMin();
        }
    }
    ss << " }";
    return ss.str();

}

void golite::Struct::weedingPass() {
    for(StructField* field : fields_) {
        field->weedingPass();
    }
}

void golite::Struct::symbolTablePass(SymbolTable *root) {
    SymbolTable* symbol_table = new golite::SymbolTable(root);
    for(StructField* field : fields_) {
        field->symbolTablePass(symbol_table);
    }
}

bool golite::Struct::isCompatible(TypeComposite *type_composite) {
    if(!type_composite->isStruct()) {
        return false;
    }
    Struct* struct_type = static_cast<Struct*>(type_composite);
    // Store fields in a vector to handles case like:
    // struct {a, b int; } == struct { a int; b int; }
    std::vector<golite::Identifier*> identifiers1, identifiers2;
    std::vector<golite::TypeComponent*> types1, types2;

    for(StructField* struct_field : fields_) {
        std::vector<golite::Identifier*> struct_identifiers = struct_field->getIdentifiers();
        identifiers1.insert(identifiers1.end(), struct_identifiers.begin(), struct_identifiers.end());
        types1.insert(types1.end(), struct_identifiers.size(), struct_field->getTypeComponent());
    }
    for(StructField* struct_field : struct_type->fields_) {
        std::vector<golite::Identifier*> struct_identifiers = struct_field->getIdentifiers();
        identifiers2.insert(identifiers2.end(), struct_identifiers.begin(), struct_identifiers.end());
        types2.insert(types2.end(), struct_identifiers.size(), struct_field->getTypeComponent());
    }

    // If number elements does not match, already it's no the same type
    if(identifiers1.size() != identifiers2.size()) {
        return false;
    }
    for(size_t i=0; i < identifiers1.size(); i++) {
        if(identifiers1[i]->getName() != identifiers2[i]->getName() || !types1[i]->isCompatible(types2[i])) {
            return false;
        }
    }
    return true;
}

std::string golite::Struct::toPrettySymbol() {
    return toGoLiteMin();
}

std::vector<golite::TypeComposite*> golite::Struct::resolveChildren() {
    return {this};
}

golite::StructField * golite::Struct::getField(std::string name) {
    for(StructField* field : fields_) {
        for(Identifier* identifier : field->getIdentifiers()) {
            if(identifier->getName() == name) {
                return field;
            }
        }
    }
    return nullptr;
}
