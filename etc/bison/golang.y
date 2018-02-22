%{
#include <golite/bison.h>

// Information for Flex
extern "C" int yylex();
extern "C" int yyparse();
extern "C" int yylineno;
%}

%code requires {
    #include <golite/expressions/expression.h>
    #include <golite/expressions/identifier_expression.h>
    #include <golite/statements/declarables/builtin.h>
    #include <golite/scope/program.h>

    #include <golite/expressions/expression_factory.h>
    #include <golite/statements/declarables/declarable_factory.h>

    #include <string>
    #include <iostream>
}

%union {
    golite::Expression*         g_expr;
    golite::Declarable*         g_declarable;

    std::vector<golite::Expression*>* g_expression_list;
    std::vector<golite::Declarable*>* g_declarable_list;
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

    <g_expr>           tFLOAT                  "float"
    <g_expr>           tINT                    "integer"
    <g_expr>           tBOOL                   "bool"
    <g_expr>           tSTRING                 "string"
    <g_expr>           tRUNE                   "rune"
    <g_expr>          tIDENTIFIER             "identifier"

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

%type <g_expression_list> var_identifiers expressions expressions_opt var_opt_expression
%type <g_declarable_list> var_body vars_bodies var_dec types_bodies type_dec
%type <g_declarable> type var_opt_type type_body struct_dec struct_body struct_scope
%type <g_expr> expression

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

var_dec[root]
    : tVAR var_body[body] tSEMICOLON { $root = $body; }
    | tVAR tLEFT_PAR vars_bodies[bodies] tRIGHT_PAR tSEMICOLON { $root = $bodies; }
    ;

vars_bodies[root]
    : vars_bodies var_body[body] tSEMICOLON {
        if(!$root) {
            $root = new std::vector<golite::Declarable*>();
        }

        std::vector<golite::Declarable*>* body = static_cast<std::vector<golite::Declarable*>*>($body);
        for(std::vector<golite::Declarable*>::iterator it = body->begin();
            it != body->end();
            ++it) {
            $root->push_back(*it);
        }
    }
    |  %empty { $root = nullptr; }
    ;

var_body[root]
    : var_identifiers[ids] var_opt_type[type] var_opt_expression[expr] {
        std::vector<golite::Declarable*>* var_decls = new std::vector<golite::Declarable*>();
        std::vector<golite::Expression*>* ids = static_cast<std::vector<golite::Expression*>*>($ids);

        for(std::vector<golite::Expression*>::iterator it = ids->begin();
            it != ids->end();
            ++it) {
            golite::Declarable* var_decl = golite::DeclarableFactory::createVarDecl(((golite::IdentifierExpression*)(*it))->getName(), (golite::TypeDeclarable*)$type);
            var_decls->push_back(var_decl);
        }

        $root = var_decls;
    }
    ;

var_identifiers[root]
    : var_identifiers tCOMMA tIDENTIFIER[id] {
        if(!$root) {
            $root = new std::vector<golite::Expression*>();
        }

        $root->push_back($id);
    }
    | tIDENTIFIER[id] {
        std::vector<golite::Expression*>* ids = new std::vector<golite::Expression*>();
        ids->push_back($id);
        $root = ids;
    }
    ;

var_opt_type[root]
    : type { $root = $root; }
    | %empty { $root = nullptr; }
    ;

var_opt_expression[root]
    : tEQUAL expressions { $root = $root; }
    | %empty { $root = nullptr; }
    ;

expressions_opt[root]
    : expressions { $root = $root; }
    |  %empty { $root = nullptr; }
    ;

expressions[root]
    : expressions tCOMMA expression[expr] {
        if(!$root) {
            $root = new std::vector<golite::Expression*>();
        }

        $root->push_back($expr);
    }
    | expression[expr] {
        std::vector<golite::Expression*>* exprs = new std::vector<golite::Expression*>();
        exprs->push_back($expr);

        $root = exprs;
    }
    ;

type_dec[root]
    : tTYPE type_body tSEMICOLON {
        $root = new std::vector<golite::Declarable*>();

    }
    | tTYPE tLEFT_PAR types_bodies tRIGHT_PAR tSEMICOLON
    ;

types_bodies[root]
    : types_bodies type_body[body] tSEMICOLON {
        if(!$root) {
            $root = new std::vector<golite::Declarable*>();
        }

        $root->push_back($body);
    }
    | types_bodies struct_body tSEMICOLON
    |  %empty
    ;

type_body[root]
    : tIDENTIFIER[id] type {
        golite::Expression* id = static_cast<golite::Expression*>($id);
        $root = golite::DeclarableFactory::createCustomTypeDecl(((golite::IdentifierExpression*)id)->getName());
    }
    ;

struct_dec[root]
    : tTYPE struct_body[body] tSEMICOLON { $root = $body; }
    ;

struct_body[root]
    : tIDENTIFIER[id] tSTRUCT tLEFT_CURL struct_scope[struct] tRIGHT_CURL {
        golite::IdentifierExpression* id = (golite::IdentifierExpression*)static_cast<golite::Expression*>($id);
        golite::StructDeclarable* structDec = (golite::StructDeclarable*)static_cast<golite::Declarable*>($struct);

        structDec->setName(id->getName());

        $root = $struct;
    }
    ;

struct_scope[root]
    : struct_scope var_identifiers[ids] type[type] tSEMICOLON {
        std::vector<golite::Expression*>* ids = static_cast<std::vector<golite::Expression*>*>($ids);
        golite::TypeDeclarable* type = (golite::TypeDeclarable*)static_cast<golite::Declarable*>($type);

        std::vector<golite::VariableDeclarable*>* vars = new std::vector<golite::VariableDeclarable*>();
        for(std::vector<golite::Expression*>::iterator it = ids->begin();
            it != ids->end();
            ++it) {
            golite::IdentifierExpression* id = (golite::IdentifierExpression*)*it;
            golite::VariableDeclarable* var_decl = golite::DeclarableFactory::createVarDecl(id->getName(), type);
            vars->push_back(var_decl);
        }

        golite::StructDeclarable* currentStruct = golite::DeclarableFactory::createStruct("", vars);
        $root = currentStruct;
    }
    | struct_scope struct_body[nested] tSEMICOLON {
        // set the current struct scope nested struct ?
        golite::StructDeclarable* nested = (golite::StructDeclarable*)static_cast<golite::Declarable*>($nested);
        if(!$root) {
            $root = golite::DeclarableFactory::createStruct("", new std::vector<golite::VariableDeclarable*>(), nested);
        } else {
            golite::StructDeclarable* root = (golite::StructDeclarable*)static_cast<golite::Declarable*>($root);

            root->setNestedStruct(nested);
        }
    }
    |  %empty { $root = nullptr; }
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

expression[root]
    : expression[lhs] tPLUS expression[rhs] { $root = golite::ExpressionFactory::createBPlus($lhs, $rhs); }
    | expression[lhs] tMINUS expression[rhs] { $root = golite::ExpressionFactory::createBMinus($lhs, $rhs); }
    | expression[lhs] tMULTIPLY expression[rhs] { $root = golite::ExpressionFactory::createBMultiply($lhs, $rhs); }
    | expression[lhs] tDIVIDE expression[rhs] { $root = golite::ExpressionFactory::createBDivide($lhs, $rhs); }
    | expression[lhs] tMODULO expression[rhs] { $root = golite::ExpressionFactory::createBModulo($lhs, $rhs); }
    | expression[lhs] tBIT_AND expression[rhs] { $root = golite::ExpressionFactory::createBBitAND($lhs, $rhs); }
    | expression[lhs] tBIT_OR expression[rhs] { $root = golite::ExpressionFactory::createBBitOR($lhs, $rhs); }
    | expression[lhs] tBIT_XOR expression[rhs] { $root = golite::ExpressionFactory::createBBitXOR($lhs, $rhs); }
    | expression[lhs] tBIT_CLEAR expression[rhs] { $root = golite::ExpressionFactory::createBBitClear($lhs, $rhs); }
    | expression[lhs] tLEFT_SHIFT expression[rhs] { $root = golite::ExpressionFactory::createBLeftShift($lhs, $rhs); }
    | expression[lhs] tRIGHT_SHIFT expression[rhs] { $root = golite::ExpressionFactory::createBRightShift($lhs, $rhs); }
    | expression[lhs] tIS_EQUAL expression[rhs] { $root = golite::ExpressionFactory::createBIsEquals($lhs, $rhs); }
    | expression[lhs] tIS_NOT_EQUAL expression[rhs] { $root = golite::ExpressionFactory::createBIsNotEquals($lhs, $rhs); }
    | expression[lhs] tLESS_THAN expression[rhs] { $root = golite::ExpressionFactory::createBLessThan($lhs, $rhs); }
    | expression[lhs] tGREATER_THAN expression[rhs] { $root = golite::ExpressionFactory::createBGreaterThan($lhs, $rhs); }
    | expression[lhs] tLESS_THAN_EQUAL expression[rhs] { $root = golite::ExpressionFactory::createBLessEqualThan($lhs, $rhs); }
    | expression[lhs] tGREATER_THAN_EQUAL expression[rhs] { $root = golite::ExpressionFactory::createBGreaterEqualThan($lhs, $rhs); }
    | expression[lhs] tAND expression[rhs] { $root = golite::ExpressionFactory::createBAnd($lhs, $rhs); }
    | expression[lhs] tOR expression[rhs] { $root = golite::ExpressionFactory::createBOr($lhs, $rhs); }
    | expression[lhs] tDOT expression[rhs] { $root = golite::ExpressionFactory::createBDot($lhs, $rhs); }
    | tMINUS expression[op] %prec pNEG { $root = golite::ExpressionFactory::createUMinus($op); }
    | tPLUS expression[op] %prec pPOS { $root = golite::ExpressionFactory::createUPlus($op); }
    | tNOT expression[op] %prec pNOT { $root = golite::ExpressionFactory::createUNot($op); }
    | tBIT_XOR expression[op] %prec pXOR { $root = golite::ExpressionFactory::createUBitXOR($op); }
    | tLEFT_PAR expression[op] tRIGHT_PAR { $root = $op; }
    | tAPPEND tLEFT_PAR expression[src_slice] tCOMMA expression[expr] tRIGHT_PAR {
        std::vector<golite::Expression*>* expr = new std::vector<golite::Expression*>();
        expr->push_back($src_slice);
        expr->push_back($expr);

        $root = golite::ExpressionFactory::createFunctionCall(golite::BuiltIn::APPEND_FN_ID, expr);
    }
    | expression[function] tLEFT_PAR expressions_opt[args] tRIGHT_PAR %prec pCALL { $root = golite::ExpressionFactory::createFunctionCall($function, $args); }
    | expression[target] tLEFT_SQUARE expression[idx] tRIGHT_SQUARE %prec pINDEX { $root = golite::ExpressionFactory::createIndexExpr($target, $idx); }
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
