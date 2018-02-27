#include <golite/program.h>
#include <golite/utils.h>
#include <sstream>
#include <golite/function.h>
#include <golite/variable.h>

std::string golite::Program::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent)<< "package " << package_name_->toGoLite(0) << ";" << std::endl;
    for(Declarable* declarable : declarables_) {
        ss << std::endl << declarable->toGoLite(indent);
    }
    return ss.str();
}

void golite::Program::weedingPass() {
    // Usage of break and continue
    for(Declarable* declarable : declarables_) {
        if(declarable->isDecVariable()) {
            golite::Variable* variable = static_cast<Variable*>(declarable);

            // Bad equation
            if(variable->badEquation()) {
                golite::Utils::error_message("Number of left and right elements does not match", variable->getLine());
            }

        } else if(declarable->isFunction()) {
            golite::Function* func = static_cast<Function*>(declarable);

            // Bad break
            Break* badBreak = func->getBlock()->badBreak();
            if(badBreak) {
                golite::Utils::error_message("Break statement used outside for loop and switch case",
                                             badBreak->getLine());
            }

            // Bad continue
            Continue* badContinue = func->getBlock()->badContinue();
            if(badContinue) {
                golite::Utils::error_message("Continue statement used outside for loop",
                                             badContinue->getLine());
            }

            // Bad equation
            Statement* badEquation = func->getBlock()->badEquation();
            if(badEquation) {
                golite::Utils::error_message("Number of left and right elements does not match", badEquation->getLine());
            }

            // Bad statement
            Statement* badStatement = func->getBlock()->badStatement();
            if(badStatement) {
                golite::Utils::error_message("Statement must be a function call", badStatement->getLine());
            }

            // Bad declaration
            Declaration* badDeclaration = func->getBlock()->badDeclaration();
            if(badDeclaration) {
                golite::Utils::error_message("Element to the left of the declaration must be identifiers",
                                             badDeclaration->getLine());
            }

            // Bad switch
            Statement* badSwitch = func->getBlock()->badSwitch();
            if(badSwitch) {
                golite::Utils::error_message("Switch statement has more than one default case",
                                             badSwitch->getLine());
            }
        }
    }
}
