#ifndef GOLITE_EXPRESSIONS_LITERALS_OCTAL_VALUE_H
#define GOLITE_EXPRESSIONS_LITERALS_OCTAL_VALUE_H

namespace golite {
    class OctalValue {
    public:
        OctalValue() { this->octal_val_ = 0; }
        OctalValue(int repr) { this->octal_val_ = repr; }
    private:
        int octal_val_;
    };
}

#endif