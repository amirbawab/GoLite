#ifndef GOLITE_LITERAL_H
#define GOLITE_LITERAL_H

#include <golite/primary.h>

namespace golite {
    template <class T>
    class Literal : public Primary {};

    template <>
    class Literal<bool> : public Primary {
    private:
        bool value_;
    public:
        Literal(bool value) : value_(value){}
        std::string toGoLite(int indent) {
            return value_ ? "true" : "false";
        }
    };

    template <>
    class Literal<int> : public Primary {
    private:
        int value_;
    public:
        Literal(int value) : value_(value){}
        std::string toGoLite(int indent) {
            return std::to_string(value_);
        }
    };

    template <>
    class Literal<char*> : public Primary {
    private:
        char* value_;
    public:
        Literal(char* value) : value_(value){}
        std::string toGoLite(int indent) {
            return value_;
        }
    };

    template <>
    class Literal<char> : public Primary {
    private:
        char value_;
    public:
        Literal(char value) : value_(value){}
        std::string toGoLite(int indent) {
            return std::to_string(value_);
        }
    };

    template <>
    class Literal<float> : public Primary {
    private:
        float value_;
    public:
        Literal(float value) : value_(value){}
        std::string toGoLite(int indent) {
            return std::to_string(value_);
        }
    };
}

#endif
