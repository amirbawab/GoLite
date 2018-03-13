#include <golite/switch.h>
#include <golite/utils.h>
#include <sstream>
#include <golite/declaration.h>
#include <golite/primary_expression.h>
#include <golite/simple_expression.h>

std::string golite::Switch::toGoLite(int indent) {
    std::stringstream ss;

    // Switch statement
    ss << golite::Utils::indent(indent) << "switch";
    if(simple_) {
        ss << " " << simple_->toGoLite(0) << ";";
    }
    if(expression_) {
        ss << " " << expression_->toGoLite(0);
    }
    ss << " {";

    // Cases
    if(!cases_.empty()) {
        ss << std::endl;
        for(SwitchCase* switch_case : cases_) {
            ss << switch_case->toGoLite(indent+1) << std::endl;
        }
        ss << golite::Utils::indent(indent);
    }
    ss << "}";
    return ss.str();
}

void golite::Switch::weedingPass(bool, bool check_continue) {
    if(simple_) {
        simple_->weedingPass(false, false);
    }

    if(expression_) {
        if(expression_->isBlank()) {
            golite::Utils::error_message("Switch statement expression cannot be a blank identifier",
                                         expression_->getLine());
        }
        expression_->weedingPass();
    }

    bool has_default = false;
    for(SwitchCase* switch_case : cases_) {
        if(switch_case->isDefault()) {
            if(has_default) {
                golite::Utils::error_message("Switch statement has more than one default case",
                                             switch_case->getLine());
            }
            has_default = true;
        }
        switch_case->weedingPass(check_continue);
    }
}

void golite::Switch::typeCheck() {
    if (simple_) {
        simple_->typeCheck();
    }

    TypeComponent* expression_type = nullptr;
    if (expression_) {
        expression_type = expression_->typeCheck();
    }

    for (SwitchCase *switch_case : cases_) {
        switch_case->typeCheck(expression_type);
    }
}

void golite::Switch::symbolTablePass(golite::SymbolTable *root) {
    SymbolTable* switch_outer_table = new SymbolTable(root);

    if(this->simple_) {
        this->simple_->symbolTablePass(switch_outer_table);
    }

    if(this->expression_) {
        this->expression_->symbolTablePass(switch_outer_table);
    }

    for(golite::SwitchCase* switch_case : this->cases_) {
        switch_case->symbolTablePass(switch_outer_table);
    }
}

bool golite::Switch::hasReturn(Declarable* function) {
    bool has_default = false;
    bool has_return = true;
    for(SwitchCase* switch_case : cases_) {
        has_return &= switch_case->hasReturn(function);
        has_default |= switch_case->isDefault();
    }
    return has_default && has_return;
}