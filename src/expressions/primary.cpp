#include <golite/primary.h>

void golite::Primary::addChild(golite::Expression *child) {
    children_.push_back(child);
}