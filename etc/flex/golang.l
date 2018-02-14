%{
#include <iostream>
#define YY_DECL extern "C" int yylex()
%}

%option yylineno

%x C_COMMENT

%%
break
case
chan
const
continue
default
defer
else
fallthrough
for
func
go
goto
if
import
interface
map
package
range
return
select
struct
switch
type
var
print
println
append

"+"
"-"
"*"
"/"
"%"
"&"
"|"
"^"
"<<"
">>"
"&^"
"+="
"-="
"*="
"/="
"%="
"&="
"|="
"^="
"<<="
">>="
"&^="
"&&"
"||"
"<-"
"++"
"--"
"=="
"<"
">"
"="
"!"
"!="
"<="
">="
":="
"..."
"("
"["
"{"
","
"."
")"
"]"
"}"
";"
":"

[ \t\r\n] {
    // White-space
}

"//".* {
    // Inline comment
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