%{
#include <golite/bison.h>
#include <iostream>

// Information for Flex
extern "C" int yylex();
extern "C" int yyparse();
extern "C" int yylineno;
%}


// Define tokens
%token
    tCHAN                   "chan"
    tCONST                  "const"
    tDEFER                  "defer"
    tFALLTHROUGH            "fallthrough"
    tINTERFACE              "interface"
    tMAP                    "map"
    tRANGE                  "range"
    tSELECT                 "select"
    tARROW                  "<-"
    tELLIPSIS               "..."
    tGO                     "go"
    tGOTO                   "goto"

    tBREAK                  "break"
    tCASE                   "case"
    tCONTINUE               "continue"
    tDEFAULT                "default"
    tELSE                   "else"
    tFOR                    "for"
    tFUNC                   "func"
    tIF                     "if"
    tIMPORT                 "import"
    tPACKAGE                "package"
    tRETURN                 "return"
    tSTRUCT                 "struct"
    tSWITCH                 "switch"
    tTYPE                   "type"
    tVAR                    "var"
    tPRINT                  "print"
    tPRINTLN                "println"
    tAPPEND                 "append"

    tINT_TYPE               "int type"
    tFLOAT_TYPE             "float type"
    tSTRING_TYPE            "string type"
    tBOOL_TYPE              "bool type"
    tRUNE_TYPE              "rune type"

    tPLUS                   "+"
    tMINUS                  "-"
    tMULTIPLY               "*"
    tDIVIDE                 "/"
    tMODULO                 "%"
    tBIT_AND                "&"
    tBIT_OR                 "|"
    tBIT_XOR                "^"
    tLEFT_SHIFT             "<<"
    tRIGHT_SHIFT            ">>"
    tBIT_CLEAR              "&^"
    tPLUS_EQUAL             "+="
    tMINUS_EQUAL            "-="
    tMULTIPLY_EQUAL         "*="
    tDIVIDE_EQUAL           "/="
    tMODULO_EQUAL           "%="
    tBIT_AND_EQUAL          "&="
    tBIT_OR_EQUAL           "|="
    tBIT_XOR_EQUAL          "^="
    tLEFT_SHIFT_EQUAL       "<<="
    tRIGHT_SHIFT_EQUAL      ">>="
    tBIT_CLEAR_EQUAL        "&^="
    tAND                    "&&"
    tOR                     "||"
    tINC                    "++"
    tDEC                    "--"
    tIS_EQUAL               "=="
    tIS_NOT_EQUAL           "!="
    tLESS_THAN              "<"
    tGREATER_THAN           ">"
    tEQUAL                  "="
    tNOT                    "!"
    tLESS_THAN_EQUAL        "<="
    tGREATER_THAN_EQUAL     ">="
    tDECLARATION            ":="
    tLEFT_PAR               "("
    tLEFT_SQUARE            "["
    tLEFT_CURL              "{"
    tCOMMA                  ","
    tDOT                    "."
    tRIGHT_PAR              ")"
    tRIGHT_SQUARE           "]"
    tRIGHT_CURL             "}"
    tSEMICOLON              ";"
    tCOLON                  ":"

    tFLOAT                  "float"
    tINT                    "integer"
    tBOOL                   "bool"
    tSTRING                 "string"
    tRUNE                   "rune"
    tIDENTIFIER             "identifier"

    tNEWLINE                "new line"
    ;

// Configure bison
%locations
%error-verbose

// Configure grammar
%start program

%left tOR
%left tAND
%left tIS_EQUAL tIS_NOT_EQUAL tLESS_THAN tGREATER_THAN tLESS_THAN_EQUAL tGREATER_THAN_EQUAL
%left tPLUS tMINUS tBIT_OR tBIT_XOR
%left tMULTIPLY tDIVIDE tMODULO tLEFT_SHIFT tRIGHT_SHIFT tBIT_AND tBIT_CLEAR
%left pNEG pPOS pNOT pXOR
%left tDOT
%left pINDEX pCALL

%%

/****************************
 *        PROGRAM
 ****************************/

/**
 * Grammar starting point
 **/
program
    : package_dec global_decs
    ;

/**
 * Global scope delcarations
 **/
global_decs
    : global_decs type_dec
    | global_decs var_dec
    | global_decs func_dec
    | %empty
    ;

/**
 * Package decalaration
 **/
package_dec
    : tPACKAGE tIDENTIFIER tSEMICOLON
    ;

/****************************
 *     IDENTIFIER TYPE
 ****************************/

/**
 * Type for identifiers
 **/
identifier_type
    : array_type identifier_type
    | slice_type identifier_type
    | struct_type
    | tIDENTIFIER
    | tLEFT_PAR identifier_type tRIGHT_PAR
    | identifier_builtin_type
    ;

/**
 * Built-in type for identifiers
 **/
identifier_builtin_type
    : tINT_TYPE
    | tFLOAT_TYPE
    | tSTRING_TYPE
    | tBOOL_TYPE
    | tRUNE_TYPE
    ;

/**
 * Array type
 **/
array_type
    : tLEFT_SQUARE tINT tRIGHT_SQUARE
    ;

/**
 * Slice type
 **/
slice_type
    : tLEFT_SQUARE tRIGHT_SQUARE
    ;

/****************************
 *     TYPE DECLARATION
 ****************************/

/**
 * Type declaration
 **/
type_dec
    : tTYPE type_def tSEMICOLON
    | tTYPE tLEFT_PAR type_defs tRIGHT_PAR tSEMICOLON
    ;

/**
 * Type definition
 **/
type_def
    : tIDENTIFIER identifier_type
    ;

/**
 * 'struct' type
 **/
struct_type
    : tSTRUCT tLEFT_CURL struct_body tRIGHT_CURL
    ;

/**
 * 'struct' body
 **/
struct_body
    : struct_body identifiers identifier_type tSEMICOLON
    | %empty
    ;

/****************************
 *        FUNCTION
 ****************************/

/**
 * Function declaration
 **/
func_dec
    : tFUNC tIDENTIFIER func_opt_params func_type block_body tSEMICOLON
    ;

/**
 * Function optional parameters
 **/
func_opt_params
    : tLEFT_PAR func_params tRIGHT_PAR
    | tLEFT_PAR tRIGHT_PAR

/**
 * Function parameters
 **/
func_params
    : func_params tCOMMA identifiers identifier_type
    | identifiers identifier_type
    ;

/**
 * Function type
 **/
func_type
    : identifier_type
    | %empty
    ;

/****************************
 *        VARIABLE
 ****************************/

/**
 * Variable delcaration
 **/
var_dec
    : tVAR var_def tSEMICOLON
    | tVAR tLEFT_PAR var_defs tRIGHT_PAR tSEMICOLON
    ;

/**
 * Variable definition
 **/
var_def
    : identifiers identifier_type var_opt_expression
    | identifiers tEQUAL expressions
    ;

/**
 * Variable optional expression
 **/
var_opt_expression
    : tEQUAL expressions
    | %empty
    ;

/****************************
 *      IF STATEMENT
 ****************************/

/**
 * 'if' statement declaration
 **/
if_dec
    : if_def else_if_opt else_opt tSEMICOLON
    ;

/**
 * 'if' statement definition
 **/
if_def
    : tIF simple_statement tSEMICOLON expression block_body
    | tIF expression block_body
    ;

/**
 * Optional 'else if' statement
 **/
else_if_opt
    : else_if_opt tELSE if_def
    | %empty
    ;

/**
 * Optional 'else' statement
 **/
else_opt
    : tELSE block_body
    | %empty
    ;

/****************************
 *      FOR STATEMENT
 ****************************/

/**
 * For declaration
 **/
for_dec
    : tFOR for_condition block_body tSEMICOLON
    ;

/**
 * For condition forms
 **/
for_condition
    : expression
    | simple_statement tSEMICOLON expression tSEMICOLON simple_statement
    | %empty
    ;

/****************************
 *     SWITCH STATEMENT
 ****************************/

/**
 * Swtich declaration
 **/
switch_dec
    : switch_def tLEFT_CURL switch_body tRIGHT_CURL tSEMICOLON
    ;

/**
 * Switch definition
 **/
switch_def
    : tSWITCH simple_statement tSEMICOLON switch_expression 
    | tSWITCH switch_expression 
    ;

/**
 * Switch optional expression
 **/
switch_expression
    : expression
    | %empty
    ;

/**
 * Switch statement body
 **/
switch_body
    : switch_body tCASE expressions tCOLON statements
    | switch_body tDEFAULT tCOLON statements
    | %empty
    ;

/****************************
 *     BLOCK STATEMENT
 ****************************/

/**
 * Block statement
 **/
block_dec
    : block_body tSEMICOLON
    ;

/**
 * Block statement body
 **/
block_body
    : tLEFT_CURL statements tRIGHT_CURL
    ;

/****************************
 *     OTHER STATEMENTS
 ****************************/

/** 
 * Complex Statement declaration
 **/
statement
    : var_dec
    | type_dec
    | simple_statement_dec
    | return_dec
    | break_dec
    | continue_dec
    | block_dec
    | if_dec
    | for_dec
    | print_dec
    | println_dec
    | switch_dec
    ;

/**
 * Simple statement declaration
 **/
 simple_statement_dec
    : simple_statement tSEMICOLON
    ;

/**
 * Print statement
 **/
print_dec
    : tPRINT tLEFT_PAR expressions_opt tRIGHT_PAR tSEMICOLON
    ;

/**
 * Println statement
 **/
println_dec
    : tPRINTLN tLEFT_PAR expressions_opt tRIGHT_PAR tSEMICOLON
    ;

/**
 * Break statement
 **/
break_dec
    : tBREAK tSEMICOLON
    ;

/**
 * Continue statement
 **/
continue_dec
    : tCONTINUE tSEMICOLON
    ;

/**
 * Simple statement
 **/
simple_statement
    : expression
    | expression tINC
    | expression tDEC
    | expressions assignment_operator expressions
    | identifiers tDECLARATION expressions
    | %empty
    ;

/**
 * Return statement
 **/
return_dec
    : tRETURN return_val tSEMICOLON
    ;

/**
 * Return statement option value
 **/
return_val
    : expression
    | %empty
    ;

/****************************
 *       EXPRESSIONS
 ****************************/

/**
 * All kinds of expressions
 **/
expression
    : binary_expression
    | unary_expression
    | primary_expression
    | tAPPEND tLEFT_PAR expression tCOMMA expression tRIGHT_PAR
    ;

/**
 * All the binary expressions
 **/
binary_expression
    : expression tPLUS expression
    | expression tMINUS expression
    | expression tMULTIPLY expression
    | expression tDIVIDE expression
    | expression tMODULO expression
    | expression tBIT_AND expression
    | expression tBIT_OR expression
    | expression tBIT_XOR expression
    | expression tBIT_CLEAR expression
    | expression tLEFT_SHIFT expression
    | expression tRIGHT_SHIFT expression
    | expression tIS_EQUAL expression
    | expression tIS_NOT_EQUAL expression
    | expression tLESS_THAN expression
    | expression tGREATER_THAN expression
    | expression tLESS_THAN_EQUAL expression
    | expression tGREATER_THAN_EQUAL expression
    | expression tAND expression
    | expression tOR expression
    ;

/**
 * All the unary expressions
 **/
unary_expression
    : tMINUS expression %prec pNEG
    | tPLUS expression %prec pPOS
    | tNOT expression %prec pNOT
    | tBIT_XOR expression %prec pXOR
    ;

/**
 * Function call
 **/
func_call
    : tLEFT_PAR func_args tRIGHT_PAR
    ;

/**
 * Function call arguments
 **/
func_args
    : expressions
    | %empty
    ;

/**
 * Expression decorators
 * Append syntax to an expression
 **/
primary_expression
    : primary_expression selector
    | primary_expression index
    | primary_expression func_call %prec pCALL
    | cast_expression
    | tLEFT_PAR expression tRIGHT_PAR
    | tIDENTIFIER
    | tINT
    | tFLOAT
    | tSTRING
    | tRUNE
    ;

/**
 * Member access
 **/
selector
    : tDOT tIDENTIFIER
    ;

/**
 * Array indices
 **/
index
    : tLEFT_SQUARE expression tRIGHT_SQUARE %prec pINDEX
    ;

/**
 * Casting expression
 **/
cast_expression
    : cast_type tLEFT_PAR expression tRIGHT_PAR
    ;

/**
 * Casting types
 **/
cast_type
    : tINT_TYPE
    | tFLOAT_TYPE
    | tBOOL_TYPE
    | tRUNE_TYPE
    ;

/**
 * Assignment operators
 **/
assignment_operator
    : tEQUAL
    | tPLUS_EQUAL
    | tMINUS_EQUAL
    | tMULTIPLY_EQUAL
    | tDIVIDE_EQUAL
    | tMODULO_EQUAL
    | tBIT_AND_EQUAL
    | tBIT_OR_EQUAL
    | tBIT_XOR_EQUAL
    | tLEFT_SHIFT_EQUAL
    | tRIGHT_SHIFT_EQUAL
    | tBIT_CLEAR_EQUAL
    | tDECLARATION
    ;

/****************************
 *          PLURALS
 ****************************/

/**
 * One or more identifier
 **/
identifiers
    : identifiers tCOMMA tIDENTIFIER
    | tIDENTIFIER
    ;

/**
 * One or more expressions
 **/
expressions
    : expressions tCOMMA expression
    | expression
    ;

/**
 * Zero or more expressions
 **/
expressions_opt
    : expressions
    | %empty
    ;

/**
 * Zero or more statements
 **/
statements
    : statements statement
    | %empty
    ;

/**
 * Optional variable definitions
 **/
var_defs
    : var_defs var_def tSEMICOLON
    | %empty
    ;

/**
 * Optinal type definitions
 */
type_defs
    : type_defs type_def tSEMICOLON
    | %empty
    ;
