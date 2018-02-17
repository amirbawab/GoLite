#include <getopt.h>
#include <iostream>
#include <vector>
#include <golite/utils.h>

// Information for Flex
extern FILE *yyin;
extern int yyparse();
extern int yylex();
extern int yylineno;


// Program flags
bool token_flag = false;
bool scan_flag = false;
bool parse_flag = false;
bool pretty_flag = false;

// Input files
std::vector<std::string> input_files;

/**
 * Print compiler usage to STDOUT
 */
void printUsage() {
    std::cout
            << "GoLite - A mini Go language compiler using" << std::endl
            << "Usage: golite [OPTION]... [FILE]..." << std::endl
            << "    -s, --scan            Scan input. Exit (1) on error" << std::endl
            << "    -t, --tokens          Print tokens" << std::endl
            << "    -p, --parse           Parse tokens" << std::endl
            << "    -P, --pretty          Prettify input file" << std::endl
            << "    -h, --help            Display this help message" << std::endl;
}

/**
 * Initialize parameters passed to the compiler
 */
void initParams(int argc, char *argv[]) {
    struct option longOptions[] = {
            {"tokens", no_argument, 0, 't'},
            {"scan", no_argument, 0, 's'},
            {"parse", no_argument, 0, 'p'},
            {"pretty", no_argument, 0, 'P'},
            {"help", no_argument, 0, 'h'},
            {0, 0, 0, 0}
    };

    int optionIndex = 0;
    int c;
    while ((c = getopt_long(argc, argv, "tspPh", longOptions, &optionIndex)) != -1) {
        switch (c) {
            case 't':
                token_flag = true;
                break;
            case 's':
                scan_flag = true;
                break;
            case 'p':
                parse_flag = true;
                break;
            case 'P':
                pretty_flag = true;
                break;
            case 'h':
            default:
                // Print by default
                break;
        }
    }
}

/**
 * Check if the compiler has all required parameters
 * @return true if all required arguments are set
 */
bool validArguments() {
    return !input_files.empty() && (scan_flag || parse_flag|| token_flag || pretty_flag);
}

/**
 * Fetch input files from the list of arguments passed
 */
void fetchInputFiles(const int argc, char *argv[]) {
    for(int i = optind; i < argc; ++i) {
        input_files.push_back(argv[i]);
    }
}

/**
 * Compiler starts here!
 * @param argc
 * @param argv
 * @return success: 0 or error: 1
 */
int main(int argc, char** argv) {

    // Initialize params
    initParams(argc, argv);

    // Fetch input filesa
    fetchInputFiles(argc, argv);

    // Check if arguments are valid
    if(!validArguments()) {
        printUsage();
        return golite::Utils::EXIT_ERROR;
    }
    return golite::Utils::EXIT_FINE;
}