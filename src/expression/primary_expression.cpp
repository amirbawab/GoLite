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
    // TODO Check if we can resolve inside parenthesis. Refactor required if applied
    // TODO Or maybe create another method called resolvesToIdentifier()
    if(children_.empty()) {
        throw std::runtime_error("Cannot check if primary expression is an identifier because children list is empty");
    }
    if(children_.size() != 1) {
        return false;
    }
    return children_.back()->isIdentifier();
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
    Primary* base_expression = nullptr;
    std::vector<golite::TypeComposite*> type_stack;
    for(size_t i = 0; i < children_.size(); i++) {
        TypeComponent* child_type = children_[i]->typeCheck();

        if(children_[i]->isIdentifier()) {
            std::vector<TypeComposite *> type_children = child_type->getChildren();
            type_stack.insert(type_stack.end(), type_children.begin(), type_children.end());
            base_expression = children_[i];

        } else if(children_[i]->isLiteral()) {
            std::vector<TypeComposite*> type_children = child_type->getChildren();
            type_stack.insert(type_stack.end(), type_children.begin(), type_children.end());
            base_expression = children_[i];

        } else if(children_[i]->isAppend()) {
            std::vector<TypeComposite*> type_children = child_type->getChildren();
            type_stack.insert(type_stack.end(), type_children.begin(), type_children.end());
            base_expression = children_[i];

        } else if(children_[i]->isParenthesis()) {
            std::vector<TypeComposite*> type_children = child_type->getChildren();
            type_stack.insert(type_stack.end(), type_children.begin(), type_children.end());
            base_expression = children_[i];

        } else if(children_[i]->isSelector()) {
            if(type_stack.empty()) {
                golite::Utils::error_message("Selector target must be a struct type", children_[i]->getLine());
            }

            // Resolve type
            std::vector<TypeComposite*> resolved = type_stack.back()->resolveChildren();
            type_stack.pop_back();
            type_stack.insert(type_stack.end(), resolved.begin(), resolved.end());

            if(!type_stack.back()->isStruct()) {
                golite::Utils::error_message("Selector target must be a struct type but given "
                                             + type_stack.back()->toGoLiteMin(), children_[i]->getLine());
            }
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
            base_expression = children_[i];

        } else if(children_[i]->isIndex()) {
            if(base_expression->isIdentifier() || base_expression->isAppend() || base_expression->isParenthesis()
               || base_expression->isSelector()) {
                if(type_stack.empty()) {
                    golite::Utils::error_message("Cannot access index " + children_[i]->toGoLite(0)
                                                 + " of a non-list type", children_[i]->getLine());
                }

                // Resolve type
                std::vector<TypeComposite*> resolved = type_stack.back()->resolveChildren();
                type_stack.pop_back();
                type_stack.insert(type_stack.end(), resolved.begin(), resolved.end());

                if(!type_stack.back()->isArray() && !type_stack.back()->isSlice())  {
                    golite::Utils::error_message("Cannot access index " + children_[i]->toGoLite(0)
                                                 + " of a non-list type", children_[i]->getLine());
                }

                // Consume stack
                type_stack.pop_back();
            } else {
                golite::Utils::error_message("Cannot access index " + children_[i]->toGoLite(0) + " of " + base_expression->toGoLite(0),
                                             children_[i]->getLine());
            }

        } else if(children_[i]->isFunctionCall()) {
            // TODO Type casting
            if(children_[i-1]->isIdentifier() || children_[i-1]->isParenthesis()) {
                Identifier* identifier = nullptr;
                golite::FunctionCall* function_call = static_cast<FunctionCall*>(children_[i]);

                // If parenthesis, then extract its content
                if(children_[i-1]->isParenthesis()) {
                    Parenthesis *parenthesis = static_cast<Parenthesis*>(children_[i-1]);
                    Expression* par_expr = parenthesis->resolveExpression();
                    if(!par_expr->isIdentifier()) {
                        golite::Utils::error_message("Cannot call a non-function parenthesis expression "
                                                     + children_[i-1]->toGoLite(0), children_[i]->getLine());
                    }
                    PrimaryExpression* primary_expression = static_cast<PrimaryExpression*>(par_expr);
                    identifier = static_cast<Identifier*>(primary_expression->getChildren().front());

                } else if(children_[i-1]->isIdentifier()) {
                    identifier = static_cast<Identifier *>(children_[i - 1]);
                } else {
                    throw std::runtime_error("Undefined previous child type");
                }

                // Get entry in symbol table
                Declarable *id_declarable = identifier->getSymbolTableEntry();

                // Should not be a variable
                if (id_declarable->isDecVariable()) {
                    golite::Utils::error_message("Cannot make a function call on variable "
                                                 + identifier->toGoLite(0), children_[i]->getLine());
                } else if(id_declarable->isTypeDeclaration()) {
                    golite::Type* type = static_cast<Type*>(id_declarable);
                    function_call->checkParams(type);
                } else if(id_declarable->isFunction()) {
                    // Perform function call
                    golite::Function* function = static_cast<Function*>(id_declarable);
                    function_call->checkParams(function);
                }

            } else {
                golite::Utils::error_message("Invalid function call", children_[i]->getLine());
            }
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
    for(Primary* child : children_) {
        child->symbolTablePass(root);
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