all: alias.o syntaxTree.o y.tab.o lex.yy.o  hashlib.o pipe.o main.o 
	gcc -o main alias.o syntaxTree.o lex.yy.o y.tab.o hashlib.o pipe.o main.o 

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

pipe.o: pipe.c
	cc -c pipe.c -g

alias.o: alias.c
	cc -c alias.c -g

hashlib.o: hashlib.c
	cc -c hashlib.c -g

syntaxTree.o: syntaxTree.c
	cc -c syntaxTree.c -g


main.o: main.c
	cc -c main.c -g

clean:
	rm -f *.o main syntaxTree lex.yy y.tab pipe alias hashlib