%{
#include <stdio.h>
#include <string.h>
#include "syntaxTree.h"


 
void yyerror(const char *str)
{
        fprintf(stderr,"error: %s\n",str);
}
 
int yywrap()
{

        return 1;
} 

int yylex();

%}


%union {
  int number;
  char* string;
  struct command* command;
}

%token<string> EOL
%token<string> WORD
%token<number> NUMBER


%type<command> real_command
%type<command> single_command

%start real_command 
%%

real_command :  single_command EOL{}
            |   real_command EOL{}
            |   EOL {}

single_command : WORD {
                      myCommand->commandName = yylval.string;  
                }
                | single_command WORD{
                      myCommand->arguments->args[0] = yylval.string;
                }

%%