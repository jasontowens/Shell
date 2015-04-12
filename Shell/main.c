#include <stdio.h>
#include <stdlib.h>
#include "alias.h"
#include "syntaxTree.h"
#include "pipe.h"
#include "y.tab.h"

#define OK 0
#define BYE 1
#define ERROR 2
#define ALIASCOM 3
#define PIPECOM 4
#define REGULARCOM 5
#define UNALIASCOM 6
#define NONECOM 7
#define GLOBCOM 8

extern int yyparse();
extern char yytext[];
extern int yy_scan_string(const char *);
void initialize_aliases();

char line[500];

int getCommand(){
	fgets(line,sizeof(line),stdin);
	yy_scan_string(line);
	if(yyparse()){
		return ERROR;
	}else if(globCommand){
		return GLOBCOM;
	}else{
		switch(type){
			case ALIAS_:
				return ALIASCOM;
			case NONE:
				return NONECOM;
			case PIPES:
				return PIPECOM;
			case REGULAR:
				return REGULARCOM;
		}
	}
	return REGULARCOM;
}

int main( int argc, const char* argv[],char** envp )
{
	//char* yo[4] = {"sh","-c","ls *.txt"};
	//execvp(yo[0],yo);



	//system("ls *.txt");
	numAlias = 0;
	myCommand = (COMMAND *)malloc(sizeof(COMMAND));
	myCommand->arguments = (ARGUMENTS *)malloc(sizeof(ARGUMENTS));
	myGlobCommand = (COMMAND *)malloc(sizeof(COMMAND));
	myGlobCommand->arguments = (ARGUMENTS *)malloc(sizeof(ARGUMENTS));
	pipingTable = (PIPINGTABLE *)malloc(sizeof(PIPINGTABLE));
	for(int i = 0; i!= MAXPIPES;++i){
		pipingTable->pipes[i].command = (COMMAND *)malloc(sizeof(COMMAND));
	}
	myCommand->numArgs = 0;	
	myGlobCommand->numArgs = 0;	
	pipingTable->numPipes = 0;
	file_input = 0;
	file_output = 0;
	int continueLoop = 1;
	initialize_aliases();
	myCommand->numArgs = 0;
	globCommand = 0;
	while(continueLoop)
	{	
		
		printf("nicebackend>");
		int g = getCommand();
		//printf("%d\n", file_output);
		switch(g){
			case GLOBCOM:
				continueLoop = performGlobedCommand();
				break;
			case REGULARCOM:
			//printf("regcol\n");
				continueLoop = performCommand(myCommand);
				//printf("continueloop%d\n",continueLoop);
				break;
			case PIPECOM:
			//printf("pipcome\n");
				continueLoop = performPipe();
				break;
			case NONECOM:
				break;
			case ERROR:
				break;
		}
		file_input = 0;
		file_output = 0;
		myCommand->numArgs = 0;	
		pipingTable->numPipes = 0;	
		globCommand = 0;
		myGlobCommand->numArgs = 0;	
	}
	printf("one\n");
	free(myCommand->arguments);
	printf("two\n");
	free(myGlobCommand->arguments);
	printf("dfg\n");
	free(myCommand);
	printf("ayyy\n");
	free(myGlobCommand);
	printf("yoooommma\n");
	printf("three\n");
	for(int i = 0; i!= MAXPIPES;++i){
		free(pipingTable->pipes[i].command);
	}
	printf("six\n");
	
	
}

// initialize_aliases();
	// add_alias("hi","yo");
	// alias_t** myal = all_aliases();

	// while(*myal != NULL ){
	// 	printf("adsgkh\n");
	// 	printf("%s\n",(*myal)->name);
	// 	printf("hie\n");
	// 	++myal;
	// }