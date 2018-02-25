%{
#include <golite/bison.h>

// Information for Flex
extern "C" int yylex();
extern "C" int yyparse();
extern "C" int yylineno;
%}

%code requires {
    #include <string>
    #include <vector>
    #include <algorithm>
    #include <iostream>
    #include <golite/variable.h>
    #include <golite/identifier.h>
    #include <golite/program.h>
    #include <golite/declarable.h>
    #include <golite/type_reference.h>
    #include <golite/array.h>
    #include <golite/slice.h>
    #include <golite/expression.h>
    #include <golite/selector.h>
    #include <golite/literal.h>
    #include <golite/index.h>
    #include <golite/function_call.h>
    #include <golite/expression_factory.h>
    #include <golite/append.h>
    #include <golite/struct.h>
    #include <golite/struct_field.h>
    #include <golite/function.h>
    #include <golite/function_param.h>
    #include <golite/return.h>
    #include <golite/break.h>
    #include <golite/continue.h>
    #include <golite/print.h>
    #include <golite/println.h>
    #include <golite/if.h>
    #include <golite/for.h>
    #include <golite/switch.h>
    #include <golite/empty.h>
    #include <golite/assignment_factory.h>
    #include <golite/inc_dec.h>
    #include <golite/declaration.h>
    #include <golite/switch_case.h>
}

%union {
    golite::Variable*                       g_variable;
    std::vector<golite::Variable*>*         g_variables;
    golite::Type*                           g_type;
    std::vector<golite::Type*>*             g_types;
    golite::Identifier*                     g_identifier;
    std::vector<golite::Identifier*>*       g_identifiers;
    std::vector<golite::Declarable*>*       g_declarables;
    golite::TypeComponent*                  g_type_component;
    golite::Expression*                     g_expression;
    std::vector<golite::Expression*>*       g_expressions;
    golite::Primary*                        g_primary;
    golite::Literal<int>*                   g_literal_int;
    golite::Literal<char*>*                 g_literal_string;
    golite::Literal<float>*                 g_literal_float;
    golite::Literal<char>*                  g_literal_rune;
    golite::Literal<bool>*                  g_literal_bool;
    golite::Struct*                         g_struct;
    std::vector<golite::StructField*>*      g_struct_fields;
    golite::Function*                       g_function;
    golite::Block*                          g_block;
    std::vector<golite::FunctionParam*>*    g_function_params;
    std::vector<golite::Statement*>*        g_statements;
    golite::Statement*                      g_statement;
    golite::If*                             g_if;
    std::vector<golite::If*>*               g_ifs;
    struct {
        golite::Simple* left;
        golite::Simple* right;
        golite::Expression* expression;}    g_for_condition;
    golite::Simple*                         g_simple;
    golite::Switch*                         g_switch;
    std::vector<golite::SwitchCase*>*       g_switch_cases;
}

%type <g_identifiers>       identifiers
%type <g_declarables>       global_decs
%type <g_variable>          var_def
%type <g_variables>         var_defs
%type <g_variables>         var_dec
%type <g_type>              type_def
%type <g_types>             type_defs
%type <g_types>             type_dec
%type <g_type_component>    identifier_type
%type <g_expression>        expression
%type <g_expressions>       expressions
%type <g_expressions>       var_opt_expressions
%type <g_primary>           primary_expression
%type <g_primary>           selector
%type <g_primary>           index
%type <g_primary>           func_call
%type <g_expression>        expression_opt
%type <g_expressions>       expressions_opt
%type <g_expression>        binary_expression
%type <g_expression>        unary_expression
%type <g_literal_int>       array_type
%type <g_struct>            struct_type
%type <g_struct_fields>     struct_body
%type <g_function>          func_dec
%type <g_block>             block_dec
%type <g_block>             block_body
%type <g_function_params>   func_params
%type <g_function_params>   func_opt_params
%type <g_type_component>    func_type
%type <g_statements>        statement
%type <g_statements>        statements
%type <g_statement>         return_dec
%type <g_statement>         break_dec
%type <g_statement>         continue_dec
%type <g_statement>         print_dec
%type <g_statement>         println_dec
%type <g_if>                if_dec
%type <g_if>                if_def
%type <g_statement>         for_dec
%type <g_ifs>               else_if_opt
%type <g_block>             else_opt
%type <g_for_condition>     for_condition
%type <g_simple>            simple_statement_dec
%type <g_simple>            simple_statement
%type <g_switch>            switch_dec
%type <g_switch>            switch_def
%type <g_switch_cases>      switch_cases

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

    <g_literal_float>       tFLOAT                  "float"
    <g_literal_int>         tINT                    "integer"
    <g_literal_bool>        tBOOL                   "bool"
    <g_literal_string>      tSTRING                 "string"
    <g_literal_rune>        tRUNE                   "rune"
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

%%

/****************************
 *        PROGRAM
 ****************************/

/**
 * Grammar starting point
 **/
program
    : package_dec global_decs[declarables]
        {
            golite::Program::getInstance()->setDeclarables(*$declarables);
        }
    ;

/**
 * Global scope delcarations
 **/
global_decs[root]
    : global_decs type_dec[types]
        {
            for(golite::Type* type : *$types) {
                $root->push_back(type);
            }
        }
    | global_decs var_dec[variables]
        {
            for(golite::Variable* variable : *$variables) {
                $root->push_back(variable);
            }
        }
    | global_decs func_dec[function]
        {
            $root->push_back($function);
        }
    | %empty
        {
            $root = new std::vector<golite::Declarable*>();
        }
    ;

/**
 * Package decalaration
 **/
package_dec
    : tPACKAGE tIDENTIFIER[identifier] tSEMICOLON
        {
            golite::Program::getInstance()->setPackageName($identifier);
        }
    ;

/****************************
 *     IDENTIFIER TYPE
 ****************************/

/**
 * Type for identifiers
 **/
identifier_type[root]
    : array_type[size] identifier_type
        {
            $root = new golite::Array($root, $size);
        }
    | slice_type identifier_type
        {
            $root = new golite::Slice($root);
        }
    | struct_type[struct]
        {
            $root = $struct;
        }
    | tIDENTIFIER[id]
        {
            golite::TypeReference* type_reference = new golite::TypeReference();
            type_reference->setIdentifier($id);
            $root = type_reference;
        }
    | tLEFT_PAR identifier_type[id_type] tRIGHT_PAR
        {
            $root = $id_type;
        }
    ;

/**
 * Array type
 **/
array_type[root]
    : tLEFT_SQUARE tINT[size] tRIGHT_SQUARE
        {
            $root = $size;
        }
    ;

/**
 * Slice type
 **/
slice_type
    : tLEFT_SQUARE tRIGHT_SQUARE
        {
            // Do nothing
        }
    ;

/****************************
 *     TYPE DECLARATION
 ****************************/

/**
 * Type declaration
 **/
type_dec[root]
    : tTYPE type_def[type] tSEMICOLON
        {
            $root = new std::vector<golite::Type*>();
            $root->push_back($type);
        }
    | tTYPE tLEFT_PAR type_defs[types] tRIGHT_PAR tSEMICOLON
        {
            $root = $types;
        }
    ;

/**
 * Type definition
 **/
type_def[root]
    : tIDENTIFIER[id] identifier_type[id_type]
        {
            $root = new golite::Type($id, $id_type);
        }
    ;

/**
 * 'struct' type
 **/
struct_type[root]
    : tSTRUCT tLEFT_CURL struct_body[fields] tRIGHT_CURL
        {
            $root = new golite::Struct();
            $root->setFields(*$fields);
        }
    ;

/**
 * 'struct' body
 **/
struct_body[root]
    : struct_body identifiers[ids] identifier_type[id_type] tSEMICOLON
        {
            golite::StructField* struct_field = new golite::StructField();
            struct_field->setIdentifiers(*$ids);
            struct_field->setTypeComponent($id_type);
            $root->push_back(struct_field);
        }
    | %empty
        {
            $root = new std::vector<golite::StructField*>();
        }
    ;

/****************************
 *        FUNCTION
 ****************************/

/**
 * Function declaration
 **/
func_dec[root]
    : tFUNC tIDENTIFIER[id] func_opt_params[params] func_type[id_type] block_body[block] tSEMICOLON
        {
            $root = new golite::Function($id);
            $root->setParams(*$params);
            $root->setBlock($block);
            $root->setTypeComponent($id_type);
        }
    ;

/**
 * Function optional parameters
 **/
func_opt_params[root]
    : tLEFT_PAR func_params[params] tRIGHT_PAR
        {
            $root = $params;
        }
    | tLEFT_PAR tRIGHT_PAR
        {
            $root = new std::vector<golite::FunctionParam*>(0);
        }
    ;

/**
 * Function parameters
 **/
func_params[root]
    : func_params tCOMMA identifiers[ids] identifier_type[id_type]
        {
            golite::FunctionParam* function_param = new golite::FunctionParam();
            function_param->setIdentifiers(*$ids);
            function_param->setTypeComponent($id_type);
            $root->push_back(function_param);
        }
    | identifiers[ids] identifier_type[id_type]
        {
            golite::FunctionParam* function_param = new golite::FunctionParam();
            function_param->setIdentifiers(*$ids);
            function_param->setTypeComponent($id_type);
            $root = new std::vector<golite::FunctionParam*>();
            $root->push_back(function_param);
        }
    ;

/**
 * Function type
 **/
func_type[root]
    : identifier_type[id_type]
        {
            $root = $id_type;
        }
    | %empty
        {
            $root = nullptr;
        }
    ;

/****************************
 *        VARIABLE
 ****************************/

/**
 * Variable delcaration
 **/
var_dec[root]
    : tVAR var_def[variable] tSEMICOLON
        {
            $root = new std::vector<golite::Variable*>();
            $root->push_back($variable);
        }
    | tVAR tLEFT_PAR var_defs[variables] tRIGHT_PAR tSEMICOLON
        {
            $root = $variables;
        }
    ;

/**
 * Variable definition
 **/
var_def[root]
    : identifiers[ids] identifier_type[id_type] var_opt_expressions[exprs]
        {
            $root = new golite::Variable();
            $root->setIdentifiers(*$ids);
            $root->setTypeComponent($id_type);
            $root->setExpressions(*$exprs);
        }
    | identifiers[ids] tEQUAL expressions[exprs]
        {
            $root = new golite::Variable();
            $root->setIdentifiers(*$ids);
            $root->setExpressions(*$exprs);
        }
    ;

/**
 * Variable optional expression
 **/
var_opt_expressions[root]
    : tEQUAL expressions[exprs]
        {
            $root = $exprs;
        }
    | %empty
        {
            $root = new std::vector<golite::Expression*>(0);
        }
    ;

/****************************
 *      IF STATEMENT
 ****************************/

/**
 * 'if' statement declaration
 **/
if_dec[root]
    : if_def[if] else_if_opt[else_if] else_opt[else] tSEMICOLON
        {
            $if->setElseIf(*$else_if);
            $if->setElse($else);
            $root = $if;
        }
    ;

/**
 * 'if' statement definition
 **/
if_def[root]
    : tIF simple_statement[simple] tSEMICOLON expression[expr] block_body[block]
        {
            $root = new golite::If();
            $root->setExpression($expr);
            $root->setBlock($block);
            $root->setSimple($simple);
        }
    | tIF expression[expr] block_body[block]
        {
            $root = new golite::If();
            $root->setExpression($expr);
            $root->setBlock($block);
        }
    ;

/**
 * Optional 'else if' statement
 **/
else_if_opt[root]
    : else_if_opt tELSE if_def[if]
        {
            $root->push_back($if);
        }
    | %empty
        {
            $root = new std::vector<golite::If*>();
        }
    ;

/**
 * Optional 'else' statement
 **/
else_opt[root]
    : tELSE block_body[block]
        {
            $root = $block;
        }
    | %empty
        {
            $root = nullptr;
        }
    ;

/****************************
 *      FOR STATEMENT
 ****************************/

/**
 * For declaration
 **/
for_dec[root]
    : tFOR for_condition[condition] block_body[block] tSEMICOLON
        {
            golite::For* for_statement = new golite::For();
            for_statement->setBlock($block);
            for_statement->setLeftSimple($condition.left);
            for_statement->setRightSimple($condition.right);
            for_statement->setExpression($condition.expression);
            $root = for_statement;
        }
    ;

/**
 * For condition forms
 **/
for_condition[root]
    : expression[expr]
        {
            $root.left = nullptr;
            $root.right = nullptr;
            $root.expression = $expr;
        }
    | simple_statement[left] tSEMICOLON expression[expr] tSEMICOLON simple_statement[right]
        {
            $root.left = $left;
            $root.right = $right;
            $root.expression = $expr;
        }
    | %empty
        {
            $root.left = nullptr;
            $root.right = nullptr;
            $root.expression = nullptr;
        }
    ;

/****************************
 *     SWITCH STATEMENT
 ****************************/

/**
 * Swtich declaration
 **/
switch_dec[root]
    : switch_def[switch] tLEFT_CURL switch_cases[body] tRIGHT_CURL tSEMICOLON
        {
            $switch->setCases(*$body);
            $root = $switch;
        }
    ;

/**
 * Switch definition
 **/
switch_def[root]
    : tSWITCH simple_statement[simple] tSEMICOLON expression_opt[expr]
        {
            $root = new golite::Switch();
            $root->setSimple($simple);
            $root->setExpression($expr);
        }
    | tSWITCH expression_opt[expr]
        {
            $root = new golite::Switch();
            $root->setExpression($expr);
        }
    ;

/**
 * Switch statement body
 **/
switch_cases[root]
    : switch_cases tCASE expressions[exprs] tCOLON statements[stmts]
        {
            golite::SwitchCase* switch_case = new golite::SwitchCase();
            switch_case->setExpressions(*$exprs);
            switch_case->setStatements(*$stmts);
            $root->push_back(switch_case);
        }
    | switch_cases tDEFAULT tCOLON statements[stmts]
        {
            golite::SwitchCase* switch_case = new golite::SwitchCase();
            switch_case->setStatements(*$stmts);
            $root->push_back(switch_case);
        }
    | %empty
        {
            $root = new std::vector<golite::SwitchCase*>();
        }
    ;

/****************************
 *     BLOCK STATEMENT
 ****************************/

/**
 * Block statement
 **/
block_dec[root]
    : block_body[block] tSEMICOLON
        {
            $root = $block;
        }
    ;

/**
 * Block statement body
 **/
block_body[root]
    : tLEFT_CURL statements[stmts] tRIGHT_CURL
        {
            $root = new golite::Block();
            $root->setStatements(*$stmts);
        }
    ;

/****************************
 *     OTHER STATEMENTS
 ****************************/

/** 
 * Complex Statement declaration
 **/
statement[root]
    : var_dec[variables]
        {
            $root = new std::vector<golite::Statement*>();
            for(golite::Variable* variable : *$variables) {
                $root->push_back(variable);
            }
        }
    | type_dec[types]
        {
            $root = new std::vector<golite::Statement*>();
            for(golite::Type* type : *$types) {
                $root->push_back(type);
            }
        }
    | simple_statement_dec[simple]
        {
            $root = new std::vector<golite::Statement*>(1);
            $root->push_back($simple);
        }
    | return_dec[return]
        {
            $root = new std::vector<golite::Statement*>(1);
            $root->push_back($return);
        }
    | break_dec[break]
        {
            $root = new std::vector<golite::Statement*>(1);
            $root->push_back($break);
        }
    | continue_dec[continue]
        {
            $root = new std::vector<golite::Statement*>(1);
            $root->push_back($continue);
        }
    | block_dec[block]
        {
            $root = new std::vector<golite::Statement*>(1);
            $root->push_back($block);
        }
    | if_dec
        {
            $root = new std::vector<golite::Statement*>(1);
            $root->push_back($if_dec);
        }
    | for_dec
        {
            $root = new std::vector<golite::Statement*>(1);
            $root->push_back($for_dec);
        }
    | print_dec[print]
        {
            $root = new std::vector<golite::Statement*>(1);
            $root->push_back($print);
        }
    | println_dec[println]
        {
            $root = new std::vector<golite::Statement*>(1);
            $root->push_back($println);
        }
    | switch_dec
        {
            $root = new std::vector<golite::Statement*>(1);
            $root->push_back($switch_dec);
        }
    ;

/**
 * Simple statement declaration
 **/
 simple_statement_dec[root]
    : simple_statement[simple] tSEMICOLON
        {
            $root = $simple;
        }
    ;

/**
 * Print statement
 **/
print_dec[root]
    : tPRINT tLEFT_PAR expressions_opt[exprs] tRIGHT_PAR tSEMICOLON
        {
            golite::Print* print_statement = new golite::Print();
            print_statement->setExpressions(*$exprs);
            $root = print_statement;
        }
    ;

/**
 * Println statement
 **/
println_dec[root]
    : tPRINTLN tLEFT_PAR expressions_opt[exprs] tRIGHT_PAR tSEMICOLON
        {
            golite::Println* println_statement = new golite::Println();
            println_statement->setExpressions(*$exprs);
            $root = println_statement;
        }
    ;

/**
 * Break statement
 **/
break_dec[root]
    : tBREAK tSEMICOLON
        {
            $root = new golite::Break();
        }
    ;

/**
 * Continue statement
 **/
continue_dec[root]
    : tCONTINUE tSEMICOLON
        {
            $root = new golite::Continue();
        }
    ;

/**
 * Simple statement
 **/
simple_statement[root]
    : expression[expr]
        {
            $root = $expr;
        }
    | expression[expr] tINC
        {
            $root = new golite::IncDec($expr, true);
        }
    | expression[expr] tDEC
        {
            $root = new golite::IncDec($expr, false);
        }
    | expressions[left] tEQUAL expressions[right]
        {
            $root = golite::AssignmentFactory::createEqual(*$left, *$right);
        }
    | expressions[left] tPLUS_EQUAL expressions[right]
        {
            $root = golite::AssignmentFactory::createPlusEqual(*$left, *$right);
        }
    | expressions[left] tMINUS_EQUAL expressions[right]
        {
            $root = golite::AssignmentFactory::createMinusEqual(*$left, *$right);
        }
    | expressions[left] tMULTIPLY_EQUAL expressions[right]
        {
            $root = golite::AssignmentFactory::createMultiplyEqual(*$left, *$right);
        }
    | expressions[left] tDIVIDE_EQUAL expressions[right]
        {
            $root = golite::AssignmentFactory::createDivideEqual(*$left, *$right);
        }
    | expressions[left] tMODULO_EQUAL expressions[right]
        {
            $root = golite::AssignmentFactory::createModuloEqual(*$left, *$right);
        }
    | expressions[left] tBIT_AND_EQUAL expressions[right]
        {
            $root = golite::AssignmentFactory::createBitANDEqual(*$left, *$right);
        }
    | expressions[left] tBIT_OR_EQUAL expressions[right]
        {
            $root = golite::AssignmentFactory::createBitOREqual(*$left, *$right);
        }
    | expressions[left] tBIT_XOR_EQUAL expressions[right]
        {
            $root = golite::AssignmentFactory::createBitXOREqual(*$left, *$right);
        }
    | expressions[left] tLEFT_SHIFT_EQUAL expressions[right]
        {
            $root = golite::AssignmentFactory::createLeftShiftEqual(*$left, *$right);
        }
    | expressions[left] tRIGHT_SHIFT_EQUAL expressions[right]
        {
            $root = golite::AssignmentFactory::createRightShiftEqual(*$left, *$right);
        }
    | expressions[left] tBIT_CLEAR_EQUAL expressions[right]
        {
            $root = golite::AssignmentFactory::createBitClearEqual(*$left, *$right);
        }
    | identifiers[ids] tDECLARATION expressions[exprs]
        {
            $root = new golite::Declaration(*$ids, *$exprs);
        }
    | %empty
        {
            $root = new golite::Empty();
        }
    ;

/**
 * Return statement
 **/
return_dec[root]
    : tRETURN expression_opt[expr] tSEMICOLON
        {
            golite::Return* return_statement = new golite::Return();
            return_statement->setExpression($expr);
            $root = return_statement;
        }
    ;

/****************************
 *       EXPRESSIONS
 ****************************/

/**
 * All kinds of expressions
 **/
expression[root]
    : binary_expression[binary]
        {
            $root = $binary;
        }
    | unary_expression[unary]
        {
            $root = $unary;
        }
    | primary_expression[primary]
        {
            $root = $primary;
        }
    | tAPPEND tLEFT_PAR expression[left] tCOMMA expression[right] tRIGHT_PAR
        {
            $root = new golite::Append($left, $right);
        }
    ;

/**
 * All the binary expressions
 **/
binary_expression[root]
    : expression[left] tPLUS expression[right]
        {
            $root = golite::ExpressionFactory::createBPlus($left, $right);
        }
    | expression[left] tMINUS expression[right]
        {
            $root = golite::ExpressionFactory::createBMinus($left, $right);
        }
    | expression[left] tMULTIPLY expression[right]
        {
            $root = golite::ExpressionFactory::createBMultiply($left, $right);
        }
    | expression[left] tDIVIDE expression[right]
        {
            $root = golite::ExpressionFactory::createBDivide($left, $right);
        }
    | expression[left] tMODULO expression[right]
        {
            $root = golite::ExpressionFactory::createBModulo($left, $right);
        }
    | expression[left] tBIT_AND expression[right]
        {
            $root = golite::ExpressionFactory::createBBitAND($left, $right);
        }
    | expression[left] tBIT_OR expression[right]
        {
            $root = golite::ExpressionFactory::createBBitOR($left, $right);
        }
    | expression[left] tBIT_XOR expression[right]
        {
            $root = golite::ExpressionFactory::createBBitXOR($left, $right);
        }
    | expression[left] tBIT_CLEAR expression[right]
        {
            $root = golite::ExpressionFactory::createBBitClear($left, $right);
        }
    | expression[left] tLEFT_SHIFT expression[right]
        {
            $root = golite::ExpressionFactory::createBLeftShift($left, $right);
        }
    | expression[left] tRIGHT_SHIFT expression[right]
        {
            $root = golite::ExpressionFactory::createBRightShift($left, $right);
        }
    | expression[left] tIS_EQUAL expression[right]
        {
            $root = golite::ExpressionFactory::createBIsEqual($left, $right);
        }
    | expression[left] tIS_NOT_EQUAL expression[right]
        {
            $root = golite::ExpressionFactory::createBIsNotEqual($left, $right);
        }
    | expression[left] tLESS_THAN expression[right]
        {
            $root = golite::ExpressionFactory::createBLessThan($left, $right);
        }
    | expression[left] tGREATER_THAN expression[right]
        {
            $root = golite::ExpressionFactory::createBGreaterThan($left, $right);
        }
    | expression[left] tLESS_THAN_EQUAL expression[right]
        {
            $root = golite::ExpressionFactory::createBLessEqualThan($left, $right);
        }
    | expression[left] tGREATER_THAN_EQUAL expression[right]
        {
            $root = golite::ExpressionFactory::createBGreaterEqualThan($left, $right);
        }
    | expression[left] tAND expression[right]
        {
            $root = golite::ExpressionFactory::createBAnd($left, $right);
        }
    | expression[left] tOR expression[right]
        {
            $root = golite::ExpressionFactory::createBOr($left, $right);
        }
    ;

/**
 * All the unary expressions
 **/
unary_expression[root]
    : tMINUS expression[operand]
        {
            $root = golite::ExpressionFactory::createUMinus($operand);
        }
    | tPLUS expression[operand]
        {
            $root = golite::ExpressionFactory::createUPlus($operand);
        }
    | tNOT expression[operand]
        {
            $root = golite::ExpressionFactory::createUNot($operand);
        }
    | tBIT_XOR expression[operand]
        {
            $root = golite::ExpressionFactory::createUBitXOR($operand);
        }
    ;

/**
 * Function call
 **/
func_call[root]
    : tLEFT_PAR expressions_opt[exprs] tRIGHT_PAR
        {
            golite::FunctionCall* function_call = new golite::FunctionCall();
            function_call->setArgs(*$exprs);
            $root = function_call;
        }
    ;

/**
 * Expression decorators
 * Append syntax to an expression
 **/
primary_expression[root]
    : primary_expression selector[id_selector]
        {
            $root->addChild($id_selector);
        }
    | primary_expression index[i]
        {
            $root->addChild($i);
        }
    | primary_expression func_call[call]
        {
            $root->addChild($call);
        }
    | tLEFT_PAR expression[expr] tRIGHT_PAR
        {
            $root = new golite::Primary();
            $root->addChild($expr);
        }
    | tIDENTIFIER[id]
        {
            $root = new golite::Primary();
            $root->addChild($id);
        }
    | tINT[integer]
        {
            $root = new golite::Primary();
            $root->addChild($integer);
        }
    | tFLOAT[float]
        {
            $root = new golite::Primary();
            $root->addChild($float);
        }
    | tSTRING[string]
        {
            $root = new golite::Primary();
            $root->addChild($string);
        }
    | tRUNE[rune]
        {
            $root = new golite::Primary();
            $root->addChild($rune);
        }
    ;

/**
 * Member access
 **/
selector[root]
    : tDOT tIDENTIFIER[id]
        {
            $root = new golite::Selector($id);
        }
    ;

/**
 * Array indices
 **/
index[root]
    : tLEFT_SQUARE expression[expr] tRIGHT_SQUARE
        {
            $root = new golite::Index($expr);
        }
    ;

/****************************
 *          PLURALS
 ****************************/

/**
 * One or more identifier
 **/
identifiers[root]
    : identifiers tCOMMA tIDENTIFIER[identifier]
        {
            $root->push_back($identifier);
        }
    | tIDENTIFIER[identifier]
        {
            $root = new std::vector<golite::Identifier*>();
            $root->push_back($identifier);
        }
    ;

/**
 * One or more expressions
 **/
expressions[root]
    : expressions tCOMMA expression[expr]
        {
            $root->push_back($expr);
        }
    | expression[expr]
        {
            $root = new std::vector<golite::Expression*>();
            $root->push_back($expr);
        }
    ;

/**
 * Option expression
 **/
expression_opt[root]
    : expression[expr]
        {
            $root = $expr;
        }
    | %empty
        {
            $root = nullptr;
        }
    ;

/**
 * Zero or more expressions
 **/
expressions_opt[root]
    : expressions[exprs]
        {
            $root = $exprs;
        }
    | %empty
        {
            $root = new std::vector<golite::Expression*>(0);
        }
    ;

/**
 * Zero or more statements
 **/
statements[root]
    : statements statement[stmt]
        {
            $root->insert($root->end(), $stmt->begin(), $stmt->end());
        }
    | %empty
        {
            $root = new std::vector<golite::Statement*>();
        }
    ;

/**
 * Optional variable definitions
 **/
var_defs[root]
    : var_defs var_def[variable] tSEMICOLON
        {
            $root->push_back($variable);
        }
    | %empty
        {
            $root = new std::vector<golite::Variable*>();
        }
    ;

/**
 * Optinal type definitions
 */
type_defs[root]
    : type_defs type_def[type] tSEMICOLON
        {
            $root->push_back($type);
        }
    | %empty
        {
            $root = new std::vector<golite::Type*>();
        }
    ;
