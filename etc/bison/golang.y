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
    | global_decs struct_dec
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

assignment_dec
    : assignment_body tSEMICOLON
    ;

assignment_body
    : expressions assignment_operator expressions
    | expression tINC
    | expression tDEC
    | expression
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

type_dec
    : tTYPE type_body tSEMICOLON
    | tTYPE tLEFT_PAR types_bodies tRIGHT_PAR tSEMICOLON
    ;

types_bodies
    : types_bodies type_body tSEMICOLON
    | types_bodies struct_body tSEMICOLON
    | %empty
    ;

type_body
    : tIDENTIFIER type
    ;

struct_dec
    : tTYPE struct_body tSEMICOLON
    ;

struct_body
    : tIDENTIFIER tSTRUCT tLEFT_CURL struct_scope tRIGHT_CURL
    ;

struct_scope
    : struct_scope identifiers identifier_type tSEMICOLON
    | struct_scope struct_body tSEMICOLON
    | %empty
    ;


/****************************
 *        FUNCTION
 ****************************/

/**
 * Function declaration
 **/
func_dec
    : tFUNC tIDENTIFIER tLEFT_PAR func_opt_params tRIGHT_PAR func_type tLEFT_CURL statements tRIGHT_CURL tSEMICOLON
    ;

/**
 * Function optional parameters
 **/
func_opt_params
    : func_params
    | %empty

/**
 * Function parameters
 **/
func_params
    : func_params tCOMMA identifiers identifier_type
    | identifiers type
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
 * 'if' statement
 **/
if_dec
    : tIF if_simple_statement expression tLEFT_CURL statements tRIGHT_CURL else_if_opt else_opt tSEMICOLON
    ;

/**
 * Optional 'else if' statement
 **/
else_if_opt
    : else_if_opt tELSE tIF if_simple_statement expression tLEFT_CURL statements tRIGHT_CURL
    | %empty
    ;

/**
 * Optional 'else' statement
 **/
else_opt
    : tELSE tLEFT_CURL statements tRIGHT_CURL tSEMICOLON
    | %empty
    ;

/**
 * Optional if simple statement
 **/
if_simple_statement
    : simple_statement tSEMICOLON
    | %empty
    ;

/****************************
 *      FOR STATEMENT
 ****************************/

/**
 * For declaration
 **/
for_dec
    : tFOR for_condition tLEFT_CURL statements tRIGHT_CURL tSEMICOLON
    ;

/**
 * For condition forms
 **/
for_condition
    : expression
    | for_simple_statement tSEMICOLON expression tSEMICOLON for_simple_statement
    | %empty
    ;

/**
 * Optional for simple statement
 **/
for_simple_statement
    : simple_statement
    | %empty
    ;


/****************************
 *     OTHER STATEMENTS
 ****************************/

/** 
 * Complex Statement declaration
 **/
statement
    : var_dec
    | struct_dec
    | type_dec
    | return_dec
    | if_dec
    | for_dec
    | break_dec
    | continue_dec
    | block_dec
    | assignment_dec
    | print_dec
    | println_dec
    ;

/**
 * Print statement
 **/
print_dec
    : tPRINT tLEFT_PAR expressions tRIGHT_PAR tSEMICOLON
    ;

/**
 * Println statement
 **/
println_dec
    : tPRINTLN tLEFT_PAR expressions tRIGHT_PAR tSEMICOLON
    ;

/**
 * Block statement
 **/
block_dec
    : tLEFT_CURL statements tRIGHT_CURL tSEMICOLON
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
    | expression tINT
    | expression tDEC_
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
 * Casting
 **/
cast_expression
    : type tLEFT_PAR expression tRIGHT_PAR
    :

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
 * One or more expression
 **/
expressions
    : expressions tCOMMA expression
    | expression
    ;

/**
 * Zero or more statements
 **/
statements
    : statements statement
    | %empty
    ;

/**
 * Variable definitions
 **/
var_defs
    : var_defs var_def tSEMICOLON
    | %empty
    ;
