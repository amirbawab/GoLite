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
    : var_dec
    ;


var_dec
    : tVAR var_body tSEMICOLON
    | tVAR tLEFT_PAR vars_bodies tRIGHT_PAR tSEMICOLON
    ;

vars_bodies
    : vars_bodies var_body tSEMICOLON
    | var_body tSEMICOLON
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

type
    : tINT_TYPE
    | tFLOAT_TYPE
    | tSTRING_TYPE
    | tBOOL_TYPE
    | tRUNE_TYPE
    | tIDENTIFIER
    ;