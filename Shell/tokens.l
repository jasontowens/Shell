%{
#include <stdio.h>
#include "syntaxTree.h"
#include "y.tab.h"

%}
%%
\n {
	return EOL; }
[A-Za-z0-9:/.&\-]+    { 

				yylval.string = strdup(yytext); 
				return WORD; 
			}
[A-Za-z0-9/.:*~?\\-]+    { 
				yylval.string = strdup(yytext); 
				printf("hello %s\n",yylval.string);
				globCommand = 1;
				return WORD;
			}

$\{[^}\n]*[}\n]  { 
				yylval.string = strdup(yytext+2);
				//printf("thisiswhatudid %s\n",yylval.string);
		 		if (yylval.string[yyleng-3] != '}'){
		 		printf("UNTERMINATED BRACE\n");
		 		}
       	 		else{
            		yylval.string[yyleng-3] = 0;
            		//printf("thisiswhatudid %s\n",yylval.string);
					return VARIABLE;
				}
			}

[|]			{
				return PIPE;
			}
[>]			{
				return OUTPUT;
			}
[<]			{
				return INPUT;
			}			
[ \t]   /* ignore whitespace */ ;

\"[^"\n]*["\n] {
		 yylval.string = strdup(yytext+1);
		 if (yylval.string[yyleng-2] != '"'){
		 	printf("UNTERMINATED QUOTE\n");
		 }
       	 else{
            	yylval.string[yyleng-2] = 0;
            	//printf("%s\n",yylval.string);
				return QUOTED;
			}
		}
%%
