#include <golite/if.h>

void golite::If::addElseIf(If *elseIf) {
    else_if_.push_back(elseIf);
}