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