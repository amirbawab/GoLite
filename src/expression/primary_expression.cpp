#include <golite/primary_expression.h>
#include <golite/utils.h>
#include <golite/identifier.h>
#include <sstream>
#include <iostream>
#include <golite/selector.h>
#include <golite/parenthesis.h>
#include <golite/declarable.h>
#include <golite/function.h>
#include <golite/function_call.h>
#include <golite/struct.h>
#include <golite/type.h>
#include <golite/type_reference.h>
#include <golite/cast.h>
#include <golite/func.h>
#include <golite/variable.h>

void golite::PrimaryExpression::addChild(golite::Primary *child) {
    children_.push_back(child);
}

std::string golite::PrimaryExpression::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent);
    for(Expression* primary : children_) {
        ss << primary->toGoLite(0);
    }
    return ss.str();
}

int golite::PrimaryExpression::getLine() {
    if(children_.empty()) {
        throw std::runtime_error("Cannot get line number of an empty primary");
    }
    return children_.front()->getLine();
}

bool golite::PrimaryExpression::isFunctionCall() {
    if(children_.empty()) {
        throw std::runtime_error("Cannot check if primary expression is a function call because children list is empty");
    }
    return children_.back()->isFunctionCall();
}

bool golite::PrimaryExpression::isIdentifier() {
    if(children_.empty()) {
        throw std::runtime_error("Cannot check if primary expression is an identifier because children list is empty");
    }
    if(children_.size() != 1) {
        return false;
    }
    return children_.back()->isIdentifier();
}

bool golite::PrimaryExpression::isLiteral() {
    if(children_.empty()) {
        throw std::runtime_error("Cannot check if primary expression is a literal because children list is empty");
    }
    if(children_.size() != 1) {
        return false;
    }
    return children_.back()->isLiteral();
}

bool golite::PrimaryExpression::isBlank() {
    if(!isIdentifier()) {
        return false;
    }
    return children_.back()->isBlank();
}

void golite::PrimaryExpression::weedingPass() {
    if (children_.empty()) {
        throw std::runtime_error("Cannot perform weeding pass on primary expression because children list is empty");
    }

    if (children_.front()->isBlank() && children_.size() > 1) {
        golite::Utils::error_message("Blank identifier cannot be accessed", children_.front()->getLine());
    }

    for (Primary *primary : children_) {
        primary->weedingPass();
    }
}

golite::TypeComponent* golite::PrimaryExpression::typeCheck() {
    if(children_.empty()) {
        throw std::runtime_error("Cannot perform type checking on a primary expression with an empty list of children");
    }

    // Get the type of the first element
    std::vector<golite::TypeComposite*> type_stack;
    for(size_t i = 0; i < children_.size(); i++) {
        TypeComponent* child_type = children_[i]->typeCheck();

        if(children_[i]->isIdentifier()) {

            // Analyze identifier
            Identifier* identifier = static_cast<Identifier*>(children_[i]);
            if(identifier->getSymbolTableEntry()->isTypeDeclaration()) {
                Type* type = static_cast<Type*>(identifier->getSymbolTableEntry());
                type_stack.push_back(new golite::Cast(children_[i]->getLine(), type));
            } else {
                std::vector<TypeComposite *> type_children = child_type->getChildren();
                type_stack.insert(type_stack.end(), type_children.begin(), type_children.end());
            }

            // Variable is addressable
            Declarable* declarable = identifier->getSymbolTableEntry();
            if(declarable->isDecVariable()) {
                Variable* variable = static_cast<golite::Variable*>(declarable);
                addressable_ = !variable->isConstant();
            }

        } else if(children_[i]->isLiteral()) {
            std::vector<TypeComposite*> type_children = child_type->getChildren();
            type_stack.insert(type_stack.end(), type_children.begin(), type_children.end());
            addressable_ = false;

        } else if(children_[i]->isAppend()) {
            std::vector<TypeComposite*> type_children = child_type->getChildren();
            type_stack.insert(type_stack.end(), type_children.begin(), type_children.end());
            addressable_ = false;

        } else if(children_[i]->isParenthesis()) {
            std::vector<TypeComposite*> type_children = child_type->getChildren();
            type_stack.insert(type_stack.end(), type_children.begin(), type_children.end());
            addressable_ = children_[i]->isAddressable();

        } else if(children_[i]->isSelector()) {
            if(type_stack.empty()) {
                golite::Utils::error_message("Selector target must be a struct type", children_[i]->getLine());
            }

            // Resolve type
            std::vector<TypeComposite*> resolved = type_stack.back()->resolveChildren();
            if(resolved.empty()){
                throw std::runtime_error("Resolve array cannot be empty while evaluating selector");
            }
            if(!resolved.back()->isStruct()) {
                golite::Utils::error_message("Selector target must be a struct type but given "
                                             + type_stack.back()->toGoLiteMin(), children_[i]->getLine());
            }
            type_stack.pop_back();
            type_stack.insert(type_stack.end(), resolved.begin(), resolved.end());

            Selector* selector = static_cast<Selector*>(children_[i]);
            Struct* struct_type = static_cast<Struct*>(type_stack.back());
            StructField* field = struct_type->getField(selector->getIdentifier()->getName());
            if(!field) {
                golite::Utils::error_message("Type " + type_stack.back()->toGoLiteMin() + " does not have member "
                                             + selector->getIdentifier()->toGoLite(0), children_[i]->getLine());
            }

            // Put field type in stack
            type_stack.pop_back();
            std::vector<TypeComposite*> field_type = field->getTypeComponent()->getChildren();
            type_stack.insert(type_stack.end(), field_type.begin(), field_type.end());

            // Note: No need to update addressable as it depends on the previous one

        } else if(children_[i]->isIndex()) {
            if (type_stack.empty()) {
                golite::Utils::error_message("Cannot access index " + children_[i]->toGoLite(0)
                                             + " of a non-list type", children_[i]->getLine());
            }

            // Resolve type
            std::vector<TypeComposite *> resolved = type_stack.back()->resolveChildren();
            type_stack.pop_back();
            type_stack.insert(type_stack.end(), resolved.begin(), resolved.end());
            if (!type_stack.back()->isArray() && !type_stack.back()->isSlice()) {
                golite::Utils::error_message("Cannot access index " + children_[i]->toGoLite(0)
                                             + " of a non-list type", children_[i]->getLine());
            }

            // Slices are addressable
            if(type_stack.back()->isSlice()) {
                addressable_ = true;
            }
            type_stack.pop_back();

            // Note: No need to update addressable for arrays as it depends on the previous one

        } else if(children_[i]->isFunctionCall()) {
            if(type_stack.empty()) {
                throw std::runtime_error("Function call cannot cannot be processed because stack is empty");
            }
            golite::FunctionCall* function_call = static_cast<FunctionCall*>(children_[i]);
            TypeComposite* top = type_stack.back();
            type_stack.pop_back();
            if(top->isCast()) {
                golite::Cast* cast = static_cast<Cast*>(top);
                function_call->checkParams(cast->getType());

                TypeComponent* cast_type_component = cast->getTypeComponent();

                // Type must resolve to a base type
                if(!cast_type_component->resolvesToBaseType()) {
                    golite::Utils::error_message("Conversion type should be a base type but given "
                                                 + cast->getType()->getIdentifier()->toGoLite(0),
                                                 children_[i]->getLine());
                }
                std::vector<TypeComposite*> cast_type_children = cast_type_component->getChildren();
                type_stack.insert(type_stack.end(), cast_type_children.begin(), cast_type_children.end());
            }else if(top->isFunc()) {
                golite::Func* func = static_cast<Func*>(top);
                function_call->checkParams(func->getFunction());
                std::vector<TypeComposite*> func_type = func->getTypeComponent()->getChildren();
                type_stack.insert(type_stack.end(), func_type.begin(), func_type.end());
            } else {
                golite::Utils::error_message("Cannot perform a function call on " + top->toGoLiteMin(),
                                             children_[i]->getLine());
            }
            addressable_ = false;
        } else {
            throw std::runtime_error("Unhandled type check for an unrecognized child type");
        }
    }
    return new TypeComponent(type_stack);
}

void golite::PrimaryExpression::symbolTablePass(SymbolTable *root) {
    if(children_.empty()) {
        throw std::runtime_error("Cannot perform symbol table pass on a primary expression with an empty list of children");
    }
    for(size_t i=0; i < children_.size(); i++) {
        children_[i]->symbolTablePass(root);
    }
}

bool golite::PrimaryExpression::isParenthesis() {
    if(children_.empty()) {
        throw std::runtime_error("Cannot check if primary expression is a parenthesis because children list is empty");
    }
    if(children_.size() != 1) {
        return false;
    }
    return children_.back()->isParenthesis();
}

golite::Expression* golite::PrimaryExpression::resolveExpression() {
    if(isParenthesis()) {
        return children_.front()->resolveExpression();
    }
    return this;
}

bool golite::PrimaryExpression::isCasting() {
    if(!children_.empty()) {
        return children_.front()->isCasting();
    }
    return false;
}

std::string golite::PrimaryExpression::toTypeScript(int indent) {
    std::stringstream ss;
    if(name_.empty()) {
        if(isBlank()) {
            name_ = children_.back()->toTypeScript(0);
            ss << name_;
        } else if(isCasting()) {
            TypeComponent* cast_type_component = typeCheck();
            FunctionCall* function_call = static_cast<FunctionCall*>(children_.back());
            TypeComponent* expr_type_component = function_call->getArgs().back()->typeCheck();
            ss << "<" << cast_type_component->toTypeScript(0) << ">";
            if(cast_type_component->resolvesToString() && expr_type_component->resolvesToInteger()) {
                ss << "String.fromCharCode(" << children_.back()->toTypeScript(0) << ")";
            } else if(cast_type_component->resolvesToInteger() && expr_type_component->resolvesToFloat64()) {
                ss << "Math.floor(" << children_.back()->toTypeScript(0) << ")";
            } else {
                ss << children_.back()->toTypeScript(0);
            }
        } else {
            for(size_t i = 0; i < children_.size(); i++) {
                ss << children_[i]->toTypeScript(0);
            }
        }
    } else {
        ss << name_;
    }
    return ss.str();
}

std::string golite::PrimaryExpression::toTypeScriptInitializer(int indent) {
    static long count = 1;
    std::stringstream ss;
    if(children_.empty()) {
        throw std::runtime_error("Cannot generate code initializer for primary expression because children list isempty");
    }

    // Initialize nested expressions
    for(Primary* child : children_) {
        ss << child->toTypeScriptInitializer(indent);
    }

    // Promote function calls
    TypeComponent* first_child = children_.front()->typeCheck();
    if(first_child->isFunc()) {

        // Assign them to unique variables
        name_ = "expr_" + std::to_string(count++);
        TypeComponent* type_component = typeCheck();
        ss << type_component->toTypeScriptInitializer(indent);
        ss << golite::Utils::blockComment({"Promoted expression"}, indent, getLine()) << std::endl;
        ss << golite::Utils::indent(indent) << "var " << name_ << " : "
           << type_component->toTypeScript(0) << " = ";
        for(Primary* child : children_) {
            ss << child->toTypeScript(0);
        }
        ss << ";" << std::endl << std::endl;
    }
    return ss.str();
}