#ifndef GOLITE_LITERAL_H
#define GOLITE_LITERAL_H

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
        void weedingPass(bool check_break, bool check_continue) { /*Do nothing*/ }
        void symbolTablePass(SymbolTable* root) { /*Do nothing*/ }
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
        void weedingPass(bool check_break, bool check_continue) { /*Do nothing*/ }
        void symbolTablePass(SymbolTable* root) { /*Do nothing*/ }
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
        void weedingPass(bool check_break, bool check_continue) { /*Do nothing*/ }
        void symbolTablePass(SymbolTable* root) { /*Do nothing*/ }
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
        void weedingPass(bool check_break, bool check_continue) { /*Do nothing*/ }
        void symbolTablePass(SymbolTable* root) { /*Do nothing*/ }
    };
}

#endif
