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
    };
}