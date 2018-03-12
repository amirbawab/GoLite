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
    std::vector<golite::TypeComposite*> type_composites;
    for(size_t i = 0; i < children_.size(); i++) {
        TypeComponent* child_type = children_[i]->typeCheck();

        if(children_[i]->isIdentifier()) {
            std::vector<TypeComposite *> type_children = child_type->getChildren();
            type_composites.insert(type_composites.end(), type_children.begin(), type_children.end());
            base_expression = children_[i];

        } else if(children_[i]->isLiteral()) {
            std::vector<TypeComposite*> type_children = child_type->getChildren();
            type_composites.insert(type_composites.end(), type_children.begin(), type_children.end());
            base_expression = children_[i];

        } else if(children_[i]->isAppend()) {
            std::vector<TypeComposite*> type_children = child_type->getChildren();
            type_composites.insert(type_composites.end(), type_children.begin(), type_children.end());
            base_expression = children_[i];

        } else if(children_[i]->isParenthesis()) {
            std::vector<TypeComposite*> type_children = child_type->getChildren();
            type_composites.insert(type_composites.end(), type_children.begin(), type_children.end());
            base_expression = children_[i];

        } else if(children_[i]->isSelector()) {
            if(type_composites.empty()) {
                golite::Utils::error_message("Selector target must be a struct type", children_[i]->getLine());
            }

            if(type_composites.back()->isTypeReference()) {
                TypeComposite* back = type_composites.back();
                type_composites.pop_back();
                // TODO Instead of resolveChildren(), check it resolves to "struct". Issue
                std::vector<TypeComposite*> resolved = back->resolveChildren();
                type_composites.insert(type_composites.end(), resolved.begin(), resolved.end());
            }

            if(!type_composites.back()->isStruct()) {
                golite::Utils::error_message("Selector target must be a struct type but given "
                                             + type_composites.back()->toGoLiteMin(), children_[i]->getLine());
            }
            Selector* selector = static_cast<Selector*>(children_[i]);
            Struct* struct_type = static_cast<Struct*>(type_composites.back());
            StructField* field = struct_type->getField(selector->getIdentifier()->getName());
            if(!field) {
                golite::Utils::error_message("Type " + type_composites.back()->toGoLiteMin() + " does not have member "
                                             + selector->getIdentifier()->toGoLite(0), children_[i]->getLine());
            }
            type_composites.pop_back();
            std::vector<TypeComposite*> field_type = field->getTypeComponent()->getChildren();
            type_composites.insert(type_composites.end(), field_type.begin(), field_type.end());
            base_expression = children_[i];

        } else if(children_[i]->isIndex()) {
            if(base_expression->isIdentifier() || base_expression->isAppend() || base_expression->isParenthesis()
               || base_expression->isSelector()) {
                if(type_composites.empty()) {
                    golite::Utils::error_message("Cannot access index " + children_[i]->toGoLite(0)
                                                 + " of a non-list type", children_[i]->getLine());
                }

                if(type_composites.back()->isTypeReference()) {
                    TypeComposite* back = type_composites.back();
                    type_composites.pop_back();
                    std::vector<TypeComposite*> resolved = back->resolveChildren(false);
                    type_composites.insert(type_composites.end(), resolved.begin(), resolved.end());
                }

                if(!type_composites.back()->isArray() && !type_composites.back()->isSlice())  {
                    golite::Utils::error_message("Cannot access index " + children_[i]->toGoLite(0)
                                                 + " of a non-list type", children_[i]->getLine());
                }

                type_composites.pop_back();
            } else {
                golite::Utils::error_message("Cannot access index " + children_[i]->toGoLite(0) + " of " + base_expression->toGoLite(0),
                                             children_[i]->getLine());
            }

        } else if(children_[i]->isFunctionCall()) {
            // TODO Type casting
            if(children_[i-1]->isIdentifier()) {
                Identifier *identifier = static_cast<Identifier *>(children_[i - 1]);
                Declarable *id_declarable = identifier->getSymbolTableEntry();
                if (!id_declarable->isFunction()) {
                    golite::Utils::error_message("Cannot call a non-function identifier " + children_[i-1]->toGoLite(0),
                                                 children_[i]->getLine());
                }
                golite::Function* function = static_cast<Function*>(id_declarable);
                golite::FunctionCall* function_call = static_cast<FunctionCall*>(children_[i]);
                function_call->checkParams(function);
            } else if(children_[i-1]->isParenthesis()) {
                Parenthesis *parenthesis = static_cast<Parenthesis*>(children_[i-1]);
                Expression* par_expr = parenthesis->resolveExpression();
                if(!par_expr->isIdentifier()) {
                    golite::Utils::error_message("Cannot call a non-function parenthesis expression "
                                                 + children_[i-1]->toGoLite(0), children_[i]->getLine());
                }
                PrimaryExpression* primary_expression = static_cast<PrimaryExpression*>(par_expr);
                Identifier* identifier = static_cast<Identifier*>(primary_expression->getChildren().front());
                Declarable *id_declarable = identifier->getSymbolTableEntry();
                if (!id_declarable->isFunction()) {
                    golite::Utils::error_message("Cannot call a non-function parenthesis identifier "
                                                 + identifier->toGoLite(0), children_[i]->getLine());
                }
                golite::Function* function = static_cast<Function*>(id_declarable);
                golite::FunctionCall* function_call = static_cast<FunctionCall*>(children_[i]);
                function_call->checkParams(function);
            } else {
                golite::Utils::error_message("Invalid function call", children_[i]->getLine());
            }
        } else {
            throw std::runtime_error("Unhandled type check for an unrecognized child type");
        }
    }
    return new TypeComponent(type_composites);
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