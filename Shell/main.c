#include <stdio.h>
#include <stdlib.h>
#include "syntaxTree.h"
#include "y.tab.h"

#define OK 0
#define BYE 1
#define ERROR 2

extern int yyparse();
extern char yytext[];
extern int yy_scan_string(const char *);

char line[500];

int getCommand(){
	fgets(line,sizeof(line),stdin);
	yy_scan_string(line);
	if(yyparse()){
		return ERROR;
	}else{
		return OK;
	}
}
int main( int argc, const char* argv[] )
{
	myCommand = (COMMAND *)malloc(sizeof(COMMAND));
	myCommand->arguments = (ARGUMENTS *)malloc(sizeof(ARGUMENTS));
	_aliasTable = (ALIASTABLE *)malloc(sizeof(ALIASTABLE));
	myCommand->numArgs = 0;	
	//_aliasTable->numAlias = 0;	
	int continueLoop = 1;
	while(continueLoop)
	{	
		printf("nicebackend>");
		switch(getCommand()){
			case OK:
			 	//printf("commandFailed\n");
				continueLoop = performCommand(myCommand);
				//printf("commandPerformed\n");
			break;
			case ERROR:
			break;

		}
		myCommand->numArgs = 0;	
	}
	free(myCommand);
	free(myCommand->arguments);
}