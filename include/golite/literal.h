#ifndef GOLITE_LITERAL_H
#define GOLITE_LITERAL_H

#include <golite/program.h>
#include <golite/primary.h>
#include <golite/utils.h>
#include <sstream>
#include <regex>

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
        std::string toTypeScript(int indent) { return std::string((value_ ? "true" : "false")); }
        std::string toTypeScriptInitializer(int indent) { return std::string(); }
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
        std::string toTypeScript(int indent) { return std::to_string(value_); }
        std::string toTypeScriptInitializer(int indent) { return std::string(); }
    };

    template <>
    class Literal<char*> : public Primary {
    private:
        char* value_;
        int line_;
    public:
        bool f_rune_ = false;
        bool f_raw_ = false;
        Literal(char* value, int line) : value_(value), line_(line){}
        std::string toGoLite(int indent) {
            std::stringstream ss;
            ss << golite::Utils::indent(indent) << std::string(value_);
            return ss.str();
        }
        int getLine() { return line_; }
        void weedingPass() { /*Do nothing*/ }
        golite::TypeComponent* typeCheck() {
            if(f_rune_) {
                return golite::Program::RUNE_BUILTIN_TYPE->getTypeComponent();
            }
            return golite::Program::STRING_BUILTIN_TYPE->getTypeComponent();
        }
        void symbolTablePass(SymbolTable* root) { /*Do nothing*/ }
        char* getValue() { return value_; }
        bool isLiteral() { return true; }
        std::string toTypeScript(int indent) {
            // Rune
            if(f_rune_) {
                return std::string(value_) + ".charCodeAt(0)";
            }

            // Raw string
            if(f_raw_) {
                std::string val;
                val = std::regex_replace(value_, std::regex("\\\\"), "\\\\");
                val = std::regex_replace(val, std::regex("\n"), "\\n");
                val[0] = '"';
                val[val.size()-1] = '"';
                return val;
            }

            // Interpreted string
            std::stringstream ss;
            bool escape = false;
            std::string org_value = std::string(value_);
            for(size_t i=0; i < org_value.size(); i++) {
                if(!escape && org_value[i] == '\\') {
                    ss << org_value[i];
                    escape = true;
                } else {
                    // \Convert unsupported escape characters in TypeScript
                    // instead replace them with their hex value
                    if(escape) {
                        if(org_value[i] == 'a') {
                            ss << "x07";
                        } else {
                            ss << org_value[i];
                        }
                    } else {
                        ss << org_value[i];
                    }
                    escape = false;
                }
            }
            return ss.str();
        }
        std::string toTypeScriptInitializer(int indent) { return std::string(); }
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
        std::string toTypeScript(int indent) { return std::to_string(value_); }
        std::string toTypeScriptInitializer(int indent) { return std::string(); }
    };
}

#endif
