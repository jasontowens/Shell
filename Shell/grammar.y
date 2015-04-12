%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alias.h"
#include "syntaxTree.h"
#include "pipe.h"


#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>


 
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
%token<string> VARIABLE
%token<string> WORD
%token<string> ALIAS
%token<string> UNALIAS
%token<string> QUOTED
%token<number> NUMBER
%token<string> PIPE
%token<string> PRINTENV
%token<string> INPUT
%token<string> OUTPUT


%type<command> real_command
%type<command> single_command

%start real_command 
%%

real_command :  single_command EOL{}
            |   single_command {}
            |   real_command EOL{}
            |   real_command REDIRECT EOL{}
            |   piping_command{};
            |   piping_command REDIRECT{};
            |   EOL {
                type = NONE;
              }

single_command : WORD { 
                     myCommand->arguments->args[myCommand->numArgs] = yylval.string;
                     myCommand->numArgs++;
                     myGlobCommand->arguments->args[myGlobCommand->numArgs] = yylval.string;
                     myGlobCommand->numArgs++;
                     type = REGULAR;  
                }
                |
                VARIABLE { 
                     myCommand->arguments->args[myCommand->numArgs] = yylval.string;
                     myCommand->numArgs++;
                     myGlobCommand->arguments->args[myGlobCommand->numArgs] = yylval.string;
                     myGlobCommand->numArgs++;
                     type = REGULAR;  
                }
                | single_command WORD{
                      myCommand->arguments->args[myCommand->numArgs] = yylval.string;
                      myCommand->numArgs++;
                      myGlobCommand->arguments->args[myGlobCommand->numArgs] = yylval.string;
                      myGlobCommand->numArgs++;
                      type = REGULAR;
                }
                | single_command QUOTED{
                      myCommand->arguments->args[myCommand->numArgs] = yylval.string;
                      myCommand->numArgs++;
                      myGlobCommand->arguments->args[myGlobCommand->numArgs] = yylval.string;
                      myGlobCommand->numArgs++;
                      type = REGULAR;
                }
                | single_command VARIABLE{
                      char* variableName = yylval.string;
                      myCommand->arguments->args[myCommand->numArgs] = getenv(variableName);
                      myCommand->numArgs++;
                      myGlobCommand->arguments->args[myGlobCommand->numArgs] = getenv(variableName);
                      myGlobCommand->numArgs++;
                      type = REGULAR;
                }
piping_command :single_command PIPE{//This will always be first
                   printf("first\n");
                
                  pipingTable->pipes[pipingTable->numPipes].command->arguments = myCommand->arguments;
                  pipingTable->pipes[pipingTable->numPipes].command->numArgs = myCommand->numArgs;
                  free(myCommand->arguments);
                  free(myCommand);
                  myCommand = (COMMAND *)malloc(sizeof(COMMAND));
                  myCommand->arguments = (ARGUMENTS *)malloc(sizeof(ARGUMENTS));
                  myCommand->numArgs = 0;
                  

                  myGlobCommand->arguments->args[myGlobCommand->numArgs] = "|";
                  myGlobCommand->numArgs++;
                
                  pipingTable->numPipes++;
                  type = PIPES;
                }
                |  
                piping_command single_command{//This will always be first
                  //fix
                  printf("second\n");
                  pipingTable->pipes[pipingTable->numPipes].command->arguments = myCommand->arguments;
                  pipingTable->pipes[pipingTable->numPipes].command->numArgs = myCommand->numArgs;
                  free(myCommand->arguments);
                  free(myCommand);
                  myCommand = (COMMAND *)malloc(sizeof(COMMAND));
                  myCommand->arguments = (ARGUMENTS *)malloc(sizeof(ARGUMENTS));
                  pipingTable->numPipes++;
                  myCommand->numArgs = 0;
                  type = PIPES;
                }
                |  
                piping_command PIPE single_command{//This will always be first
                  //fix
                  printf("third\n");
                  pipingTable->pipes[pipingTable->numPipes].command->arguments = myCommand->arguments;
                  pipingTable->pipes[pipingTable->numPipes].command->numArgs = myCommand->numArgs;
                  free(myCommand->arguments);
                  free(myCommand);
                  myCommand = (COMMAND *)malloc(sizeof(COMMAND));
                  myCommand->arguments = (ARGUMENTS *)malloc(sizeof(ARGUMENTS));

                  myGlobCommand->arguments->args[myGlobCommand->numArgs] = "|";
                  myGlobCommand->numArgs++;

                  pipingTable->numPipes++;
                  myCommand->numArgs = 0;
                  type = PIPES;
                }

REDIRECT  : INPUT QUOTED{ 
              printf("input\n");
              file_input = 1;
              myCommand->inputFile = yylval.string;
              myGlobCommand->arguments->args[myGlobCommand->numArgs] = "<";
              myGlobCommand->numArgs++;
              myGlobCommand->arguments->args[myGlobCommand->numArgs] = yylval.string;
              myGlobCommand->numArgs++;
            }
            |
            OUTPUT QUOTED{
                 printf("output\n");
              file_output = 1;
              myCommand->outputFile = yylval.string;
              myGlobCommand->arguments->args[myGlobCommand->numArgs] = ">";
              myGlobCommand->numArgs++;
              myGlobCommand->arguments->args[myGlobCommand->numArgs] = yylval.string;
              myGlobCommand->numArgs++;
            }
            |
            INPUT WORD{ 
              printf("input\n");
              file_input = 1;
              char* fixed = fixWord(yylval.string);
              if(fixed != NULL){
                 myCommand->inputFile = fixed;
                 myGlobCommand->arguments->args[myGlobCommand->numArgs] = ">";
                 myGlobCommand->numArgs++;
                 myGlobCommand->arguments->args[myGlobCommand->numArgs] = yylval.string;
                 myGlobCommand->numArgs++;
              }else{
                myCommand->inputFile = yylval.string;
                myGlobCommand->arguments->args[myGlobCommand->numArgs] = ">";
                myGlobCommand->numArgs++;
                myGlobCommand->arguments->args[myGlobCommand->numArgs] = yylval.string;
                myGlobCommand->numArgs++;
              }
            }
            |
            OUTPUT WORD{
                 printf("output\n");
              file_output = 1;
               char* fixed = fixWord(yylval.string);
              if(fixed != NULL){
                 myCommand->outputFile = fixed;
                 myGlobCommand->arguments->args[myGlobCommand->numArgs] = ">";
                 myGlobCommand->numArgs++;
                 myGlobCommand->arguments->args[myGlobCommand->numArgs] = yylval.string;
                 myGlobCommand->numArgs++;
              }else{
                myCommand->inputFile = yylval.string;
                myGlobCommand->arguments->args[myGlobCommand->numArgs] = ">";
                myGlobCommand->numArgs++;
                myGlobCommand->arguments->args[myGlobCommand->numArgs] = yylval.string;
                myGlobCommand->numArgs++;
              }
            }
                

%%