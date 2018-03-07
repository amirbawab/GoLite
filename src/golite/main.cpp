#include <getopt.h>
#include <iostream>
#include <golite/utils.h>
#include <golite/program.h>

// Information for Flex
extern "C" FILE *yyin;
extern "C" int yyparse();
extern "C" int yylex();
extern "C" int yylineno;

// Program flags
bool scan_flag = false;
bool tokens_flag = false;
bool parse_flag = false;
bool pretty_flag = false;
bool symbol_flag = false;

// Input files
std::string input_file;
std::string input_file_name;

/**
 * Print compiler usage to STDOUT
 */
void printUsage() {
    std::cout
            << "GoLite - A mini Go language compiler using" << std::endl
            << "Usage: golite [OPTION]... [FILE]..." << std::endl
            << "    -t, --tokens          Print tokens" << std::endl
            << "    -s, --scan            Scan input. Exit (1) on error" << std::endl
            << "    -p, --parse           Parse tokens" << std::endl
            << "    -P, --pretty          Prettify input file" << std::endl
            << "    -S, --symbol          Outputs the symbol table." << std::endl
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
            {"symbol", no_argument, 0, 'S'},
            {"help", no_argument, 0, 'h'},
            {0, 0, 0, 0}
    };

    int optionIndex = 0;
    int c;
    while ((c = getopt_long(argc, argv, "tspPh", longOptions, &optionIndex)) != -1) {
        switch (c) {
            case 't':
                tokens_flag = true;
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
            case 'S':
                symbol_flag = true;
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
    return !input_file.empty() && scan_flag + parse_flag + pretty_flag + tokens_flag == 1;
}

/**
 * Fetch input files from the list of arguments passed
 */
void fetchInputFiles(const int argc, char *argv[]) {
    if(optind < argc) {
        input_file = argv[optind];
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

    // Fetch input files
    fetchInputFiles(argc, argv);

    // Check if arguments are valid
    if(!validArguments()) {
        printUsage();
        return golite::Utils::EXIT_ERROR;
    }

    // Read file
    input_file_name = input_file.substr(input_file.find_last_of("/\\") + 1);
    FILE *file = fopen(input_file.c_str(), "r");
    if (!file) {
        std::cerr << "Cannot open input file: " << input_file_name << std::endl;
        return golite::Utils::EXIT_ERROR;
    }
    yyin = file;

    if(tokens_flag) {
        while (yylex()) {}
    } else if(scan_flag) {
        while (yylex()) {}
    } else if(parse_flag) {
        do { yyparse(); } while (!feof(yyin));
        golite::Program::getInstance()->weedingPass();
    } else if(pretty_flag) {
        do { yyparse(); } while (!feof(yyin));
        golite::Program::getInstance()->weedingPass();
        std::cout << golite::Program::getInstance()->toGoLite(0) << std::endl;
    } else if(symbol_flag) {
        do { yyparse(); } while(!feof(yyin));
        golite::Program::getInstance()->symbolTablePass();
    }

    return golite::Utils::EXIT_FINE;
}