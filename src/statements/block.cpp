#include <golite/block.h>
#include <golite/utils.h>
#include <golite/if.h>
#include <sstream>
#include <golite/switch.h>

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