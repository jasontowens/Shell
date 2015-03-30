%{
#include <stdio.h>
#include "y.tab.h"
#include "syntaxTree.c"
%}
%%
\n {
	return EOL; }
[A-Za-z]+    { yylval.string = strdup(yytext); 
				return WORD; }

[0-9]		{ yylval.number = atoi(yytext); 
					return NUMBER; }

[ \t]   /* ignore whitespace */ ;


%%
