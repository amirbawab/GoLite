#ifndef GOLITE_EXPRESSIONS_LITERALS_HEX_VALUE_H
#define GOLITE_EXPRESSIONS_LITERALS_HEX_VALUE_H

#include <string>

// TODO We won't need to keep track of the original integer format, directory convert to decimal
namespace golite {
    class HexValue {
    public:
        HexValue() { this->hex_val_ = "0x0"; }
        HexValue(char* repr) { this->hex_val_ = repr; }
    private:
        std::string hex_val_;
    };
}

#endif