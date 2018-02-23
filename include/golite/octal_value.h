#ifndef GOLITE_EXPRESSIONS_LITERALS_OCTAL_VALUE_H
#define GOLITE_EXPRESSIONS_LITERALS_OCTAL_VALUE_H

// TODO We won't need to keep track of the original integer format, directory convert to decimal
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