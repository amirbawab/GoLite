namespace go {
    namespace utils {

        // Constants
        const int EXIT_FINE = 0;
        const int EXIT_ERROR = 1;

        /**
         * Report error of unsupported lex
         * @param lex
         * @param line
         */
        void support_error(char* lex, int line);
    }
}