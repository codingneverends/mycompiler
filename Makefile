all:
	bison --yacc -d yacc.y
	lex _lexer.l
	gcc y.tab.c lex.yy.c -o mycompiler

clean:
	rm lex* y.tab* mycompiler


