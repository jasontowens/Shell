all: y.tab.o lex.yy.o main.o syntaxTree.o
	cc lex.yy.o y.tab.o main.o syntaxTree.o -o main -g

y.tab.h: grammar.y
	yacc -dv grammar.y

y.tab.c: grammar.y
	yacc -dv grammar.y

y.tab.o: y.tab.h y.tab.c
	cc -c y.tab.c -g

lex.yy.c: tokens.l
	lex tokens.l

lex.yy.o: lex.yy.c
	cc -c lex.yy.c -g

syntaxTree.o: syntaxTree.c
	cc -c syntaxTree.c -g

main.o: main.c
	cc -c main.c -g