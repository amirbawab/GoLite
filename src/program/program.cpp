#include <golite/program.h>
#include <golite/utils.h>
#include <sstream>
#include <golite/function.h>
#include <golite/utils.h>

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
        if(declarable->isFunction()) {
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
        }
    }
}
