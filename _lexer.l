%{
	#include<stdio.h>
	#include<stdlib.h>
	#include "y.tab.h"
	#include "defenitions.h"
	int number;
%}

%%
\/\/(.*) {};	
\/\*(.*\n)*.*\*\/  {};	
[ \t\n]  { ; }
"{" { return Begin; }
";" { return End_L; }
"}" { return End; }
">" { return gt; }
"<" { return lt; }
">=" { return ge; }
"<=" { return le; }
"==" { return eq; }
"!=" { return ne; }
"write" { return Write; }
"read" { return Read; }
"if" { return If; }
"else" { return Else; }
"while" { return While; }
"do" { return Do; }
"for" { return For; }
"return" { return Return; }
"FUN" { return FUN; }
[a-zA-Z]+[a-zA-Z0-9]* { yylval.node = create_ID_Node(strdup(yytext)); return ID;}
[0-9]+ { number=atoi(yytext); yylval.node = create_Number_Node(number);return NUM; }
\+|\*|\-|\/|\=    { return yytext[0]; }
[()]   { return yytext[0]; }
.      { printf("lex error: %s\n", yytext); exit(1); }
%%

int yywrap() { return 1; }
