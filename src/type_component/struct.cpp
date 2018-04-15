#include <golite/struct.h>
#include <golite/utils.h>
#include <golite/variable.h>
#include <set>
#include <sstream>
#include <golite/ts_helper.h>

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
    std::set<std::string> identifier_names;
    for(StructField* field : fields_) {
        field->symbolTablePass(root);
        for(Identifier* identifier : field->getIdentifiers()) {
            if(!identifier->isBlank()) {
                if(identifier_names.find(identifier->getName()) != identifier_names.end()) {
                    golite::Utils::error_message("Field name " + identifier->getName()
                                                 + " redeclared in this block", identifier->getLine());
                }
                identifier_names.insert(identifier->getName());
            }
        }
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

bool golite::Struct::isComparable() {
    for(StructField* field : fields_) {
        if(!field->getTypeComponent()->isComparable()) {
            return false;
        }
    }
    return true;
}

bool golite::Struct::resolvesToComparable() {
    for(StructField* field : fields_) {
        if(!field->getTypeComponent()->resolvesToComparable()) {
            return false;
        }
    }
    return true;
}

bool golite::Struct::isRecursive(Type *type) {
    for(StructField* field : fields_) {
        if(field->isRecursive(type)) {
            return true;
        }
    }
    return false;
}

std::string golite::Struct::toTypeScriptInitializer(int indent) {
    static long count = 1;
    name_ = "struct_" + std::to_string(count++);
    std::stringstream ss_pre;
    std::stringstream ss_post;
    std::stringstream ss;
    ss_post << golite::Utils::indent(indent) << "class " << name_ << " {" << std::endl;
    if(!fields_.empty()) {
        for(StructField *field : fields_) {
            ss_pre << field->getTypeComponent()->toTypeScriptInitializer(indent);
            ss_post << field->toTypeScript(indent+1);
        }
    }
    ss_post << golite::Utils::indent(indent+1) << "clone = () : " << name_ << " => {" << std::endl
            << golite::Utils::indent(indent+2) << "var obj : " << name_ << " = new " << name_ << "();" << std::endl;
    for(StructField *field : fields_) {
        for(Identifier* identifier : field->getIdentifiers()) {
            if(!identifier->isBlank()) {
                ss_post << golite::Utils::indent(indent+2) << "obj." << identifier->getName() << " = this."
                        << identifier->getName() << golite::TSHelper::cloneByType(field->getTypeComponent())
                        << ";" << std::endl;
            }
        }
    }
    ss_post << golite::Utils::indent(indent+2) << "return obj;" << std::endl
            << golite::Utils::indent(indent+1) << "}" << std::endl;

    ss_post << golite::Utils::indent(indent+1) << "equals = (obj : " << name_ << ") : boolean => {" << std::endl
            << golite::Utils::indent(indent+2) << "return ";
    if(fields_.empty()) {
        ss_post << "true" << std::endl;
    } else {
        size_t k = 0;
        for(size_t i=0; i < fields_.size(); i++) {
            for(Identifier* identifier : fields_[i]->getIdentifiers()) {
                TypeComponent* field_type_component = fields_[i]->getTypeComponent();
                if(k != 0) {
                    ss_post << std::endl << golite::Utils::indent(indent+3) << "   && ";
                }
                if(field_type_component->isSlice() || identifier->isBlank()) {
                    ss_post << "true";
                } else if(golite::TSHelper::isObject(field_type_component)) {
                    ss_post << "this." << identifier->getName()
                            << ".equals(obj." << identifier->getName() << ")";
                } else {
                    ss_post << "this." << identifier->getName() << " === obj." << identifier->getName();
                }
                k++;
            }
        }
        ss_post << ";" << std::endl;
    }
    ss_post << golite::Utils::indent(indent+1) << "}" << std::endl;
    ss_post << golite::Utils::indent(indent) << "};";
    ss << ss_pre.str();
    ss << golite::Utils::blockComment({"Class representing a struct"}, indent, getLine()) << std::endl;
    ss << ss_post.str() << std::endl << std::endl;
    return ss.str();
}

std::string golite::Struct::toTypeScript(int indent) {
    return name_;
}