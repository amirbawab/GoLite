#include <golite/assignment.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Assignment::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent);
    for(size_t i = 0; i < left_expressions_.size(); i++) {
        if(i != 0) {
            ss << ", ";
        }
        ss << left_expressions_[i]->toGoLite(0);
    }

    switch (kind_) {
        case EQUAL:
            ss << " = ";
            break;
        case PLUS_EQUAL:
            ss << " += ";
            break;
        case MINUS_EQUAL:
            ss << " -= ";
            break;
        case MULTIPLY_EQUAL:
            ss << " *= ";
            break;
        case DIVIDE_EQUAL:
            ss << " /= ";
            break;
        case MODULO_EQUAL:
            ss << " %= ";
            break;
        case LEFT_SHIFT_EQUAL:
            ss << " <<= ";
            break;
        case RIGHT_SHIFT_EQUAL:
            ss << " >>= ";
            break;
        case BIT_AND_EQUAL:
            ss << " &= ";
            break;
        case BIT_OR_EQUAL:
            ss << " |= ";
            break;
        case BIT_XOR_EQUAL:
            ss << " ^= ";
            break;
        case BIT_CLEAR_EQUAL:
            ss << " &^= ";
            break;
    }

    for(size_t i = 0; i < right_expressions_.size(); i++) {
        if(i != 0) {
            ss << ", ";
        }
        ss << right_expressions_[i]->toGoLite(0);
    }
    ss << ";";
    return ss.str();
}