%{
// Information for Flex
extern "C" int yylex();
extern "C" int yyparse();
extern "C" int yylineno;
%}


// Define tokens
%token
    tBREAK                  "break"
    tCASE                   "case"
    tCHAN                   "chan"
    tCONST                  "const"
    tCONTINUE               "continue"
    tDEFAULT                "default"
    tDEFER                  "defer"
    tELSE                   "else"
    tFALLTHROUGH            "fallthrough"
    tFOR                    "for"
    tFUNC                   "func"
    tGO                     "go"
    tGOTO                   "goto"
    tIF                     "if"
    tIMPORT                 "import"
    tINTERFACE              "interface"
    tMAP                    "map"
    tPACKAGE                "package"
    tRANGE                  "range"
    tRETURN                 "return"
    tSELECT                 "select"
    tSTRUCT                 "struct"
    tSWITCH                 "switch"
    tTYPE                   "type"
    tVAR                    "var"
    tPRINT                  "print"
    tPRINTLN                "println"
    tAPPEND                 "append"

    tINT                    "int type"
    tFLOAT_TYPE             "float type"
    tSTRING_TYPE            "string type"
    tBOOL                   "bool type"
    tRUNE                   "rune type"

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
    tBIT_AND_BIT_XOR_EQUAL  "&^="
    tAND                    "&&"
    tOR                     "||"
    tCHAN_ARROW             "<-"
    tINC                    "++"
    tDEC                    "--"
    tIS_EQUAL               "=="
    tLESS_THAN              "<"
    tGREATER_THAN           ">"
    tEQUAL                  "="
    tNOT                    "!"
    tNOT_EQUAL              "!="
    tLESS_THAN_EQUAL        "<="
    tGREATER_THAN_EQUAL     ">="
    tDECLARATION            ":="
    tDOT_DOT_DOT            "..."
    tLEFT_PAR               "("
    tLEFT_SQUARE            "["
    tLEFT_CUR               "{"
    tCOMMA                  ","
    tDOT                    "."
    tRIGHT_PAR              ")"
    tRIGHT_SQUARE           "]"
    tRIGHT_CUR              "}"
    tSEMICOLON              ";"
    tCOLON                  ":"
    ;

// Configure bison
%locations
%error-verbose

// Configure grammar
%start S

s :
    packages declarations
    ;

declarations
    : declarations structs
    | declarations functions
    | %empty
    ;

packages
    : tSEMICOLON
    | %empty
    ;

statements
    : statements statement
    | %empty

statement
    : var_dec
    | type_dec
    | return_dec
    | if_dec
    | for_dec
    | break_dec
    | continue_dec
    ;

var_dec
    : tVAR var_body tSEMICOLON
    | tVAR tLEFT_PAR vars_bodies tRIGHT_PAR tSEMICOLON
    ;

vars_bodies
    : vars_bodies var_body tSEMICOLON
    | %empty
    ;

var_body:
    var_identifiers var_opt_type var_opt_expression
    ;

var_identifiers
    : var_identifiers tCOMMA tIDENTIFIER
    | tIDENTIFIER
    ;

var_opt_type
    : type
    | %empty
    ;

var_opt_expression
    : tEQUAL expression tSEMICOLON
    | %empty
    ;

type_dec
    : tTYPE type_body tSEMICOLON
    | tTYPE tLEFT_PAR type_bodies tRIGHT_PAR tSEMICOLON
    ;

types_bodies
    : types_bodies type_body tSEMICOLON
    | %empty
    ;

type_body
    : tIDENTIFIER type_val
    ;

type_val
    : type
    | tSTRUCT tLEFT_CUR type_bodies tRIGHT_CUR
    ;

func_dec
    : tFUNC tIDENTIFIER tLEFT_PAR func_params tRIGHT_PAR func_type tLEFT_CUR statements tRIGHT_CUR
    ;

func_params
    : func_params var_identifiers type
    | var_identifiers type
    ;

func_type
    : type
    | %empty
    ;

return_dec
    : tRETURN return_val tSEMICOLON
    ;

return_val
    : expression
    | %empty
    ;

if_dec
    : tIF expression tLEFT_CURL statements tRIGHT_CURL else_if_opt else_opt
    ;

else_opt
    : tELSE tLEFT_CURL statements tRIGHT_CURL
    | %empty
    ;

else_if_opt
    : else_if_opt tELSE tIF expression tLEFT_CURL statements tRIGHT_CURL
    | %empty
    ;

for_dec
    : tFOR for_condition tLEFT_CURL statements tRIGHT_CURL
    ;

for_condition
    : expression
    | assignment_body tSEMICOLON expression tSEMICOLON assignment_body
    | %empty
    ;

assignment
    : assignment_body tSEMICOLON

assignment_body
    : tIDENTIFIER assignment_operator expression
    | tIDENTIFIER tINC
    | tIDENTIFIER tDEC
    | tIDENTIFIER tDECLARATION expression
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
    ;

break_dec
    : tBREAK tSEMICOLON
    ;

continue_dec
    : tCONTINUE tSEMICOLON
     ;

type
    : tINT_TYPE
    | tFLOAT_TYPE
    | tSTRING_TYPE
    | tBOOL_TYPE
    | tRUNE_TYPE
    | tIDENTIFIER
    ;