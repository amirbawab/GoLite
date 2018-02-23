#ifndef GOLITE_UTILS_H
#define GOLITE_UTILS_H
namespace golite {
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
         * Log tokens if flag is on
         * @param lex
         * @param val
         */
        static void log_token(const char* lex, const char* val = nullptr);
    };
}

#endif