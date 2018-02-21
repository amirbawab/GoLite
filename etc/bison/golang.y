%{
#include <golite/bison.h>

// Information for Flex
extern "C" int yylex();
extern "C" int yyparse();
extern "C" int yylineno;
%}

%code requires {
    #include <golite/expressions/identifier_expression.h>
    #include <golite/statements/declarables/type_declarable.h>
    #include <golite/scope/program.h>
    #include <string>
    #include <iostream>
}

%union {
    golite::IdentifierExpression*   g_identifier;
    golite::TypeDeclarable*         g_type_decl;
    std::vector<golite::IdentifierExpression*>* g_identifier_list;
}

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

    <g_type_decl>           tFLOAT                  "float"
    <g_type_decl>           tINT                    "integer"
    <g_type_decl>           tBOOL                   "bool"
    <g_type_decl>           tSTRING                 "string"
    tRUNE                   "rune"
    <g_identifier>          tIDENTIFIER             "identifier"

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

%type <g_identifier_list> var_identifiers
%type <g_type_decl> type

%%
program
    : package_dec declarations {
        //golite::Program::getInstance()->setPackageName("test");
    }
    ;

declarations
    : declarations type_dec
    | declarations struct_dec
    | declarations var_dec
    | declarations func_dec
    | %empty
    ;

package_dec
    : tPACKAGE tIDENTIFIER[package_name] tSEMICOLON {
        golite::IdentifierExpression* package_name = static_cast<golite::IdentifierExpression*>($package_name);
        golite::Program::getInstance()->setPackageName(package_name->getName());
    }
    ;

statements
    : statements statement
    |  %empty
    ;

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
    ;

block_dec
    : tLEFT_CURL statements tRIGHT_CURL tSEMICOLON
    ;

var_dec
    : tVAR var_body tSEMICOLON
    | tVAR tLEFT_PAR vars_bodies tRIGHT_PAR tSEMICOLON
    ;

vars_bodies
    : vars_bodies var_body tSEMICOLON
    |  %empty
    ;

var_body
    : var_identifiers var_opt_type var_opt_expression
    ;

var_identifiers[root]
    : var_identifiers tCOMMA tIDENTIFIER[id] {
        if(!$root) {
            $root = new std::vector<golite::IdentifierExpression*>();
        }

        $root->push_back($id);
    }
    | tIDENTIFIER
    ;

var_opt_type[root]
    : type
    | %empty
    ;

var_opt_expression
    : tEQUAL expressions
    | %empty
    ;

expressions_opt
    : expressions
    |  %empty
    ;

expressions
    : expressions tCOMMA expression
    | expression
    ;

type_dec
    : tTYPE type_body tSEMICOLON
    | tTYPE tLEFT_PAR types_bodies tRIGHT_PAR tSEMICOLON
    ;

types_bodies
    : types_bodies type_body tSEMICOLON
    | types_bodies struct_body tSEMICOLON
    |  %empty
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
    : struct_scope var_identifiers type tSEMICOLON
    | struct_scope struct_body tSEMICOLON
    |  %empty
    ;

func_dec
    : tFUNC tIDENTIFIER tLEFT_PAR func_opt_params tRIGHT_PAR func_type tLEFT_CURL statements tRIGHT_CURL tSEMICOLON
    ;

func_opt_params
    : func_params
    |  %empty

func_params
    : func_params tCOMMA var_identifiers type
    | var_identifiers type
    ;

func_type
    : type
    |  %empty
    ;

return_dec
    : tRETURN return_val tSEMICOLON
    ;

return_val
    : expression
    |  %empty
    ;

if_dec
    : tIF expression tLEFT_CURL statements tRIGHT_CURL else_if_opt else_opt
    ;

else_opt
    : tELSE tLEFT_CURL statements tRIGHT_CURL tSEMICOLON
    | tSEMICOLON
    ;

else_if_opt
    : else_if_opt tELSE tIF expression tLEFT_CURL statements tRIGHT_CURL
    |  %empty
    ;

for_dec
    : tFOR for_condition tLEFT_CURL statements tRIGHT_CURL tSEMICOLON
    ;

for_condition
    : expression
    | assignment_body tSEMICOLON expression tSEMICOLON assignment_body
    |  %empty
    ;

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
    | tDECLARATION
    ;

break_dec
    : tBREAK tSEMICOLON
    ;

continue_dec
    : tCONTINUE tSEMICOLON
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

expression
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
    | expression tDOT expression
    | tMINUS expression %prec pNEG
    | tPLUS expression %prec pPOS
    | tNOT expression %prec pNOT
    | tBIT_XOR expression %prec pXOR
    | tLEFT_PAR expression tRIGHT_PAR
    | tAPPEND tLEFT_PAR expression tCOMMA expression tRIGHT_PAR
    | expression tLEFT_PAR expressions_opt tRIGHT_PAR %prec pCALL
    | expression tLEFT_SQUARE expression tRIGHT_SQUARE %prec pINDEX
    | tINT
    | tFLOAT
    | tSTRING
    | tRUNE
    | tIDENTIFIER
    ;

type
    : array_dec type
    | slice_dec type
    | type_val
    ;

type_val
    : tINT_TYPE
    | tFLOAT_TYPE
    | tSTRING_TYPE
    | tBOOL_TYPE
    | tRUNE_TYPE
    | tIDENTIFIER
    ;

array_dec
    : tLEFT_SQUARE tINT tRIGHT_SQUARE
    ;

slice_dec
    : tLEFT_SQUARE tRIGHT_SQUARE
    ;
