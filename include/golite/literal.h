#ifndef GOLITE_LITERAL_H
#define GOLITE_LITERAL_H

#include <golite/program.h>
#include <golite/primary.h>
#include <golite/utils.h>
#include <sstream>

namespace golite {
    template <class T>
    class Literal : public Primary {};

    template <>
    class Literal<bool> : public Primary {
    private:
        bool value_;
        int line_;
    public:
        Literal(bool value, int line) : value_(value), line_(line){}
        std::string toGoLite(int indent) {
            std::stringstream ss;
            ss << golite::Utils::indent(indent) << (value_ ? "true" : "false");
            return ss.str();
        }
        int getLine() { return line_; }
        void weedingPass() { /*Do nothing*/ }
        golite::TypeComponent* typeCheck() {
            return golite::Program::BOOL_BUILTIN_TYPE->getTypeComponent();
        }
        void symbolTablePass(SymbolTable* root) { /*Do nothing*/ }
        bool getValue() { return value_; }
        bool isLiteral() { return true; }
    };

    template <>
    class Literal<int> : public Primary {
    private:
        int value_;
        int line_;
    public:
        Literal(int value, int line) : value_(value), line_(line){}
        std::string toGoLite(int indent) {
            std::stringstream ss;
            ss << golite::Utils::indent(indent) << std::to_string(value_);
            return ss.str();
        }
        int getLine() { return line_; }
        void weedingPass() { /*Do nothing*/ }
        golite::TypeComponent* typeCheck() {
            return golite::Program::INT_BUILTIN_TYPE->getTypeComponent();
        }
        void symbolTablePass(SymbolTable* root) { /*Do nothing*/ }
        int getValue() { return value_; }
        bool isLiteral() { return true; }
    };

    template <>
    class Literal<char*> : public Primary {
    private:
        char* value_;
        int line_;
    public:
        Literal(char* value, int line) : value_(value), line_(line){}
        std::string toGoLite(int indent) {
            std::stringstream ss;
            ss << golite::Utils::indent(indent) << std::string(value_);
            return ss.str();
        }
        int getLine() { return line_; }
        void weedingPass() { /*Do nothing*/ }
        golite::TypeComponent* typeCheck() {
            return golite::Program::STRING_BUILTIN_TYPE->getTypeComponent();
        }
        void symbolTablePass(SymbolTable* root) { /*Do nothing*/ }
        char* getValue() { return value_; }
        bool isLiteral() { return true; }
    };

    template <>
    class Literal<float> : public Primary {
    private:
        float value_;
        int line_;
    public:
        Literal(float value, int line) : value_(value), line_(line){}
        std::string toGoLite(int indent) {
            std::stringstream ss;
            ss << golite::Utils::indent(indent) << std::to_string(value_);
            return ss.str();
        }
        int getLine() { return line_; }
        void weedingPass() { /*Do nothing*/ }
        golite::TypeComponent* typeCheck() {
            return golite::Program::FLOAT64_BUILTIN_TYPE->getTypeComponent();
        }
        void symbolTablePass(SymbolTable* root) { /*Do nothing*/ }
        float getValue() { return value_; }
        bool isLiteral() { return true; }
    };
}

#endif
