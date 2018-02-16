%{
#include <golite/bison.h>
#include <golite/utils.h>
#include <bison/golang_bison.h>
#include <iostream>

#define YY_DECL extern "C" int yylex()
%}

%option yylineno

%x C_COMMENT

%%
chan            { go::utils::support_error(yytext, yylineno); }
const           { go::utils::support_error(yytext, yylineno); }
defer           { go::utils::support_error(yytext, yylineno); }
fallthrough     { go::utils::support_error(yytext, yylineno); }
interface       { go::utils::support_error(yytext, yylineno); }
map             { go::utils::support_error(yytext, yylineno); }
range           { go::utils::support_error(yytext, yylineno); }
select          { go::utils::support_error(yytext, yylineno); }
"<-"            { go::utils::support_error(yytext, yylineno); }
"..."           { go::utils::support_error(yytext, yylineno); }

break           { return tBREAK; }
case            { return tCASE; }
continue        { return tCONTINUE; }
default         { return tDEFAULT; }
else            { return tELSE; }
for             { return tFOR; }
func            { return tFUNC; }
go              { return tGO; }
goto            { return tGOTO; }
if              { return tIF; }
import          { return tIMPORT; }
package         { return tPACKAGE; }
return          { return tRETURN; }
struct          { return tSTRUCT; }
switch          { return tSWITCH; }
type            { return tTYPE; }
var             { return tVAR; }
print           { return tPRINT; }
println         { return tPRINTLN; }
append          { return tAPPEND; }

int             { return tINT_TYPE; }
float64         { return tFLOAT_TYPE; }
bool            { return tBOOL_TYPE; }
rune            { return tRUNE_TYPE; }
string          { return tSTRING_TYPE; }

"+"             { return tPLUS; }
"-"             { return tMINUS; }
"*"             { return tMULTIPLY; }
"/"             { return tDIVIDE; }
"%"             { return tMODULO; }
"&"             { return tBIT_AND; }
"|"             { return tBIT_OR; }
"^"             { return tBIT_XOR; }
"<<"            { return tLEFT_SHIFT; }
">>"            { return tRIGHT_SHIFT; }
"&^"            { return tBIT_CLEAR; }
"+="            { return tPLUS_EQUAL; }
"-="            { return tMINUS_EQUAL; }
"*="            { return tMULTIPLY_EQUAL; }
"/="            { return tDIVIDE_EQUAL; }
"%="            { return tMODULO_EQUAL; }
"&="            { return tBIT_AND_EQUAL; }
"|="            { return tBIT_OR_EQUAL; }
"^="            { return tBIT_XOR_EQUAL; }
"<<="           { return tLEFT_SHIFT_EQUAL; }
">>="           { return tRIGHT_SHIFT_EQUAL; }
"&^="           { return tBIT_CLEAR_EQUAL; }
"&&"            { return tAND; }
"||"            { return tOR; }
"++"            { return tINC; }
"--"            { return tDEC; }
"=="            { return tIS_EQUAL; }
"<"             { return tLESS_THAN; }
">"             { return tGREATER_THAN; }
"="             { return tEQUAL; }
"!"             { return tNOT; }
"!="            { return tIS_NOT_EQUAL; }
"<="            { return tLESS_THAN_EQUAL; }
">="            { return tGREATER_THAN_EQUAL; }
":="            { return tDECLARATION; }
"("             { return tLEFT_PAR; }
"["             { return tLEFT_SQUARE; }
"{"             { return tLEFT_CURL; }
","             { return tCOMMA; }
"."             { return tDOT; }
")"             { return tRIGHT_PAR; }
"]"             { return tRIGHT_SQUARE; }
"}"             { return tRIGHT_CURL; }
";"             { return tSEMICOLON; }
":"             { return tCOLON; }

[ \t\r\n] {
    // White-space
}

"//".* {
    // Inline comment
}

0|([1-9][0-9]*) {
    // Integer
}

0[1-7][0-7]* {
    // Octal
}

0[x][0-9a-f]+ {
    // Hex
}

(0|[1-9][0-9]*)?\.[0-9]* {
    // Float
}

'(\\[abfnrtv\\\'])|[^\\]' {
    // Character
}

\"((\\[abfnrtv\"\\])|[ a-zA-Z0-9\~\@\#\$\%\^\&\*\-\+\/\`\<\>\=\_\|\'\.\,\;\:\!\?\{\}\[\]\(\)])*\"  {
    // String
}

[a-zA-Z_][a-zA-Z0-9_]* {
    // Identifier
}

"/*"            { BEGIN(C_COMMENT); }
<C_COMMENT>"*/" { BEGIN(INITIAL); }
<C_COMMENT>.    { }

. {
    // Everything else
    std::cerr << "" << std::endl;
    exit(1);
}
%%