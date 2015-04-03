all: syntaxTree.o y.tab.o lex.yy.o main.o 
	gcc -o main syntaxTree.o lex.yy.o y.tab.o main.o 

y.tab.h: grammar.y
	yacc -dv grammar.y

y.tab.c: grammar.y
	yacc -dv grammar.y

y.tab.o: y.tab.h y.tab.c
	cc -c y.tab.c 

lex.yy.c: tokens.l
	lex tokens.l

lex.yy.o: lex.yy.c
	cc -c lex.yy.c -g

syntaxTree.o: syntaxTree.c
	cc -c syntaxTree.c -g

main.o: main.c
	cc -c main.c -g

clean:
	rm -f *.o main syntaxTree lex.yy y.tab