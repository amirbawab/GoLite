#ifndef GOLITE_UTILS_H
#define GOLITE_UTILS_H

#include <string>
#include <vector>

namespace golite {

    /**
     * Project utils
     *
     * functions in this class must be static
     * No instance of this class is needed to be created
     */
    class Utils {
    public:
        // Constants
        static const int EXIT_FINE = 0;
        static const int EXIT_ERROR = 1;

        /**
         * Report error of unsupported lex
         * @param lex
         * @param line
         */
        static void support_error(char* lex, int line);

        /**
         * Custom message
         * @param msg
         * @param line
         */
        static void error_message(std::basic_string<char, std::char_traits<char>, std::allocator<char>> msg, int line);

        /**
         * Log tokens if flag is on
         * @param lex
         * @param val
         */
        static void log_token(const char* lex, const char* val = nullptr);

        /**
         * Create indentation
         * @param val
         * @return spaces
         */
        static std::string indent(int val);

        /**
         * Generate block comment
         * @param lines
         * @return block comment
         */
        static std::string blockComment(std::vector<std::string> lines, int indent, int line = -1);

        /**
         * Generate block comment
         * @param code
         * @return code
         */
        static std::string codeNotGenerated(std::string code, int indent, int line);
    };
}

#endif