#ifndef GOLITE_IDENTIFIER_H
#define GOLITE_IDENTIFIER_H

#include <string>
#include <golite/primary.h>

namespace golite {
    class Identifier : public Primary {
    private:
        static std::string BLANK;
        std::string name_;
        int line_;
    public:
        Identifier(std::string name, int line) : name_(name), line_(line) {}

        /**
         * Get name
         * @return name
         */
        std::string getName() const { return name_; }

        /**
         * Get line
         * @return line
         */
        int getLine() { return line_; }

        /**
         * @see Statement::toGoLite(int)
         */
        std::string toGoLite(int indent);

        /**
         * @ee Expression::isIdentifier()
         */
        bool isIdentifier() { return true; }

        /**
         * Check if identifier is a blank identifier
         * @return true if it is
         */
        bool isBlank();

        /**
         * @see Statement::weedingPass()
         */
        void weedingPass(bool check_break, bool check_continue);

        /**
         * @see Statement::typeCheck()
         */
        golite::TypeComponent* typeCheck();
    };
}

#endif