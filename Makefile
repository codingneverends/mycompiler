all:
	bison --yacc -d yacc.y
	lex _lexer.l
	gcc y.tab.c lex.yy.c -o mycompiler
	lex linker.l
	gcc lex.yy.c -o addresser
	./mycompiler < $(input) > intermediate.xsm
	./addresser < intermediate.xsm > B190480CS.xsm

clean:
	rm lex* y.tab* mycompiler addresser


