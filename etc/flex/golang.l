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
chan            { golite::Utils::log_token("tCHAN"); return tCHAN; }
const           { golite::Utils::log_token("tCONST"); return tCONST; }
defer           { golite::Utils::log_token("tDEFER"); return tDEFER; }
fallthrough     { golite::Utils::log_token("tFALLTHROUGH"); return tFALLTHROUGH; }
interface       { golite::Utils::log_token("tINTERFACE"); return tINTERFACE; }
map             { golite::Utils::log_token("tMAP"); return tMAP; }
range           { golite::Utils::log_token("tRANGE"); return tRANGE; }
select          { golite::Utils::log_token("tSELECT"); return tSELECT; }
"<-"            { golite::Utils::log_token("tARROW"); return tARROW; }
"..."           { golite::Utils::log_token("tELLIPSIS"); return tELLIPSIS; }
go              { golite::Utils::log_token("tGO"); return tGO; }
goto            { golite::Utils::log_token("tGOTO"); return tGOTO; }

break           { golite::Utils::log_token("tBREAK"); return tBREAK; }
case            { golite::Utils::log_token("tCASE"); return tCASE; }
continue        { golite::Utils::log_token("tCONTINUE"); return tCONTINUE; }
default         { golite::Utils::log_token("tDEFAULT"); return tDEFAULT; }
else            { golite::Utils::log_token("tELSE"); return tELSE; }
for             { golite::Utils::log_token("tFOR"); return tFOR; }
func            { golite::Utils::log_token("tFUNC"); return tFUNC; }
if              { golite::Utils::log_token("tIF"); return tIF; }
import          { golite::Utils::log_token("tIMPORT"); return tIMPORT; }
package         { golite::Utils::log_token("tPACKAGE"); return tPACKAGE; }
return          { golite::Utils::log_token("tRETURN"); return tRETURN; }
struct          { golite::Utils::log_token("tSTRUCT"); return tSTRUCT; }
switch          { golite::Utils::log_token("tSWITCH"); return tSWITCH; }
type            { golite::Utils::log_token("tTYPE"); return tTYPE; }
var             { golite::Utils::log_token("tVAR"); return tVAR; }
print           { golite::Utils::log_token("tPRINT"); return tPRINT; }
println         { golite::Utils::log_token("tPRINTLN"); return tPRINTLN; }
append          { golite::Utils::log_token("tAPPEND"); return tAPPEND; }

int             { golite::Utils::log_token("tINT_TYPE"); return tINT_TYPE; }
float64         { golite::Utils::log_token("tFLOAT_TYPE"); return tFLOAT_TYPE; }
bool            { golite::Utils::log_token("tBOOL_TYPE"); return tBOOL_TYPE; }
rune            { golite::Utils::log_token("tRUNE_TYPE"); return tRUNE_TYPE; }
string          { golite::Utils::log_token("tSTRING_TYPE"); return tSTRING_TYPE; }

"+"             { golite::Utils::log_token("tPLUS"); return tPLUS; }
"-"             { golite::Utils::log_token("tMINUS"); return tMINUS; }
"*"             { golite::Utils::log_token("tMULTIPLY"); return tMULTIPLY; }
"/"             { golite::Utils::log_token("tDIVIDE"); return tDIVIDE; }
"%"             { golite::Utils::log_token("tMODULO"); return tMODULO; }
"&"             { golite::Utils::log_token("tBIT_AND"); return tBIT_AND; }
"|"             { golite::Utils::log_token("tBIT_OR"); return tBIT_OR; }
"^"             { golite::Utils::log_token("tBIT_XOR"); return tBIT_XOR; }
"<<"            { golite::Utils::log_token("tLEFT_SHIFT"); return tLEFT_SHIFT; }
">>"            { golite::Utils::log_token("tRIGHT_SHIFT"); return tRIGHT_SHIFT; }
"&^"            { golite::Utils::log_token("tBIT_CLEAR"); return tBIT_CLEAR; }
"+="            { golite::Utils::log_token("tPLUS_EQUAL"); return tPLUS_EQUAL; }
"-="            { golite::Utils::log_token("tMINUS_EQUAL"); return tMINUS_EQUAL; }
"*="            { golite::Utils::log_token("tMULTIPLY_EQUAL"); return tMULTIPLY_EQUAL; }
"/="            { golite::Utils::log_token("tDIVIDE_EQUAL"); return tDIVIDE_EQUAL; }
"%="            { golite::Utils::log_token("tMODULO_EQUAL"); return tMODULO_EQUAL; }
"&="            { golite::Utils::log_token("tBIT_AND_EQUAL"); return tBIT_AND_EQUAL; }
"|="            { golite::Utils::log_token("tBIT_OR_EQUAL"); return tBIT_OR_EQUAL; }
"^="            { golite::Utils::log_token("tBIT_XOR_EQUAL"); return tBIT_XOR_EQUAL; }
"<<="           { golite::Utils::log_token("tLEFT_SHIFT_EQUAL"); return tLEFT_SHIFT_EQUAL; }
">>="           { golite::Utils::log_token("tRIGHT_SHIFT_EQUAL"); return tRIGHT_SHIFT_EQUAL; }
"&^="           { golite::Utils::log_token("tBIT_CLEAR_EQUAL"); return tBIT_CLEAR_EQUAL; }
"&&"            { golite::Utils::log_token("tAND"); return tAND; }
"||"            { golite::Utils::log_token("tOR"); return tOR; }
"++"            { golite::Utils::log_token("tINC"); return tINC; }
"--"            { golite::Utils::log_token("tDEC"); return tDEC; }
"=="            { golite::Utils::log_token("tIS_EQUAL"); return tIS_EQUAL; }
"<"             { golite::Utils::log_token("tLESS_THAN"); return tLESS_THAN; }
">"             { golite::Utils::log_token("tGREATER_THAN"); return tGREATER_THAN; }
"="             { golite::Utils::log_token("tEQUAL"); return tEQUAL; }
"!"             { golite::Utils::log_token("tNOT"); return tNOT; }
"!="            { golite::Utils::log_token("tIS_NOT_EQUAL"); return tIS_NOT_EQUAL; }
"<="            { golite::Utils::log_token("tLESS_THAN_EQUAL"); return tLESS_THAN_EQUAL; }
">="            { golite::Utils::log_token("tGREATER_THAN_EQUAL"); return tGREATER_THAN_EQUAL; }
":="            { golite::Utils::log_token("tDECLARATION"); return tDECLARATION; }
"("             { golite::Utils::log_token("tLEFT_PAR"); return tLEFT_PAR; }
"["             { golite::Utils::log_token("tLEFT_SQUARE"); return tLEFT_SQUARE; }
"{"             { golite::Utils::log_token("tLEFT_CURL"); return tLEFT_CURL; }
","             { golite::Utils::log_token("tCOMMA"); return tCOMMA; }
"."             { golite::Utils::log_token("tDOT"); return tDOT; }
")"             { golite::Utils::log_token("tRIGHT_PAR"); return tRIGHT_PAR; }
"]"             { golite::Utils::log_token("tRIGHT_SQUARE"); return tRIGHT_SQUARE; }
"}"             { golite::Utils::log_token("tRIGHT_CURL"); return tRIGHT_CURL; }
";"             { golite::Utils::log_token("tSEMICOLON"); return tSEMICOLON; }
":"             { golite::Utils::log_token("tCOLON"); return tCOLON; }

[ \t\r\n] {
    // White-space
}

"//".* {
    // Inline comment
}

0+|([1-9][0-9]*) {
    // Integer
    golite::Utils::log_token("tINT", yytext);
    return tINT;
}

0[1-7][0-7]* {
    // Octal
    golite::Utils::log_token("tINT", yytext);
    return tINT;
}

0[xX][0-9a-fA-F]+ {
    // Hex
    golite::Utils::log_token("tINT", yytext);
    return tINT;
}

([0-9]*\.[0-9]+)|([0-9]+\.[0-9]*) {
    // Float
    golite::Utils::log_token("tFLOAT", yytext);
    return tFLOAT;
}

'((\\[abfnrtv\\\'])|[^\\'])' {
    // Rune/Character
    golite::Utils::log_token("tRUNE", yytext);
    return tRUNE;
}

`(.|\n)*` {
    // Raw String
    golite::Utils::log_token("tSTRING", yytext);
    return tSTRING;
}

\"(\\[abfnrtv\\\"]|[^\\"])*\" {
    // String
    golite::Utils::log_token("tSTRING", yytext);
    return tSTRING;
}

[a-zA-Z_][a-zA-Z0-9_]* {
    // Identifier
    golite::Utils::log_token("tIDENTIFIER", yytext);
    return tIDENTIFIER;
}

"/*"            { BEGIN(C_COMMENT); /*Go to C_COMMENT state*/ }
<C_COMMENT>.    { /* Comment can contain any char */ }
<C_COMMENT>\n   { /* Comment can contains new lines */ }
<C_COMMENT>"*/" { BEGIN(INITIAL); /* Go back to initial state */ }

. {
    // Everything else
    golite::Utils::support_error(yytext, yylineno);
}
%%