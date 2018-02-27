#include <golite/block.h>
#include <golite/utils.h>
#include <golite/if.h>
#include <sstream>
#include <golite/switch.h>
#include <golite/assignment.h>
#include <golite/declaration.h>
#include <golite/variable.h>

std::string golite::Block::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "{";
    if(!statements_.empty()) {
        ss << std::endl;
        for(Statement* statement : statements_) {
            ss << statement->toGoLite(indent+1) << std::endl;
        }
        ss << golite::Utils::indent(indent);
    }
    ss << "}";
    return ss.str();
}

golite::Break* golite::Block::badBreak() {
    for(Statement* statement : statements_) {
        golite::Break* bad = nullptr;
        if(statement->isIf()) {
            golite::If* if_stmt = static_cast<If*>(statement);
            bad = if_stmt->getBlock()->badBreak();
        } else if(statement->isBlock()) {
            golite::Block* block_stmt = static_cast<Block*>(statement);
            bad = block_stmt->badBreak();
        } else if(statement->isBreak()) {
            bad = static_cast<Break*>(statement);
        }
        if(bad) return bad;
    }
    return nullptr;
}

golite::Continue* golite::Block::badContinue() {
    for(Statement* statement : statements_) {
        golite::Continue* bad = nullptr;
        if(statement->isIf()) {
            golite::If* if_stmt = static_cast<If*>(statement);
            bad = if_stmt->getBlock()->badContinue();
        } else if(statement->isBlock()) {
            golite::Block* block_stmt = static_cast<Block*>(statement);
            bad = block_stmt->badContinue();
        } else if(statement->isSwitch()) {
            golite::Switch* switch_stmt = static_cast<Switch*>(statement);
            bad = switch_stmt->badContinue();
        } else if(statement->isContinue()) {
            bad = static_cast<Continue*>(statement);
        }
        if(bad) return bad;
    }
    return nullptr;
}

golite::Statement* golite::Block::badEquation() {
    for(Statement* statement : statements_) {
        Statement* bad = nullptr;
        if(statement->isAssignment()) {
            golite::Assignment* assignment = static_cast<Assignment*>(statement);
            if(assignment->badEquation()) {
                bad = assignment;
            }
        } else if(statement->isDeclaration()) {
            golite::Declaration* declaration = static_cast<Declaration*>(statement);
            if(declaration->badEquation()) {
                bad = declaration;
            }
        } else if(statement->isVariable()) {
            golite::Variable* variable = static_cast<Variable*>(statement);
            if(variable->badEquation()) {
                bad = variable;
            }
        } else if(statement->isBlock()) {
            golite::Block* block = static_cast<Block*>(statement);
            bad = block->badEquation();
        }
        if(bad) return bad;
    }
    return nullptr;
}