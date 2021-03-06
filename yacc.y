%{
	#include<stdlib.h>
	#include<stdio.h>
	#include "defenitions.h"
	#include "descriptions.c"
	int yylex();
	int yyerror(char const *);
%}

%union {
	struct tnode *node;
}
%type <node> Prgm Sl S InpS OpS Asgs E IfStmt IfElseStmt ReturnStmt WhileLoop DoWhileLoop ForLoop
%token <node> Begin End NUM ID Read Write If Else While Do For gt lt ge le eq ne End_L FUN Return
%left gt lt ge le eq ne
%left '+' '-'
%left '*' '/'
%%
Prgm : Read '(' ID ')' End_L ID '=' FUN '(' ID ')' Begin Sl End Write '(' ID ')' End_L { $$=InitProgram($13); }
;
Sl : Sl S { $$ = Connect_Node($1,$2); }
	| S { $$ = $1; }
;
S : InpS End_L{ $$ = $1; }
	| OpS End_L{ $$ = $1; }
	| Asgs End_L{ $$ = $1; }
	| IfElseStmt { $$ = $1;}
	| IfStmt { $$ = $1;}
	| ReturnStmt { $$ = $1; }
	| WhileLoop { $$ = $1; }
	| DoWhileLoop { $$ = $1; }
	| ForLoop { $$ = $1; }
;
IfElseStmt : If '(' E ')' Begin Sl End Else Begin Sl End  { $$ = create_IfElse_Node($3,$6,$10); }
| If '(' E ')' S Else Begin Sl End  { $$ = create_IfElse_Node($3,$5,$8); }
| If '(' E ')' Begin Sl End Else S { $$ = create_IfElse_Node($3,$6,$9); }
| If '(' E ')' S Else S  { $$ = create_IfElse_Node($3,$5,$7); }
;
WhileLoop : While '(' E ')' Begin Sl End { $$ = create_WhileLoop_Node($3,$6); }
| While '(' E ')' S { $$ = create_WhileLoop_Node($3,$5); }
;
DoWhileLoop : Do Begin Sl End While '(' E ')' End_L { $$ = create_DoWhileLoop_Node($7,$3); }
| Do S While '(' E ')' End_L { $$ = create_DoWhileLoop_Node($5,$2); }
;
ForLoop : For '(' S E End_L S ')' Begin Sl End { $$ = create_ForLoop_Node($3,$4,$6,$9); }
| For '(' S E End_L S ')' S { $$ = create_ForLoop_Node($3,$4,$6,$8); }
;
IfStmt : If '(' E ')' Begin Sl End { $$ = create_If_Node($3,$6); }
| If '(' E ')' S { $$ = create_If_Node($3,$5); }
; 
InpS : Read'('E')' { $$ = create_Read_Node($3); }
;
OpS : Write'('E')' { $$ = create_Write_Node($3); }
;
Asgs : ID '=' E { $$ = create_Assgn_Node($1,$3); }
;
ReturnStmt : Return E End_L { $$=create_Return_Node($2); }
;
E: E '+' E   { $$ = create_OP_Node($1,$3,'+'); }
 | E '-' E   { $$ = create_OP_Node($1,$3,'-'); }
 | E '*' E   { $$ = create_OP_Node($1,$3,'*'); }
 | E '/' E   { $$ = create_OP_Node($1,$3,'/'); }
 | '(' E ')' { $$=$2; }
 | NUM       { $$=$1; }
 | ID       { $$=$1; }
 | E gt E { $$ = create_Bool_Node($1,$3,"gt"); }
 | E lt E { $$ = create_Bool_Node($1,$3,"lt"); }
 | E ge E { $$ = create_Bool_Node($1,$3,"ge"); }
 | E le E { $$ = create_Bool_Node($1,$3,"le"); }
 | E eq E { $$ = create_Bool_Node($1,$3,"eq"); }
 | E ne E { $$ = create_Bool_Node($1,$3,"ne"); }
 | FUN '(' E ')' { $$ = create_Func_Call_Node($3); }
 ;
%%

int yyerror(char const *s) {
	fprintf(stderr, "Error: %s\n", s);
	exit(1);
}
int main() {
	yyparse();
	return 0;
}

