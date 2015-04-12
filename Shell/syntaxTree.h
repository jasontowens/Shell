#ifndef SYNTAXTREE_H
#define SYNTAXTREE_H

#define MAXARGS 100
#define ALIAS_ 0
#define PIPES 1
#define REGULAR 2
#define UNALIAS_ 3
#define NONE 4
typedef struct comargs{
	char* args[MAXARGS];
}ARGUMENTS;

typedef struct command{
	ARGUMENTS* arguments;
	int numArgs;
	char* inputFile;
	char* outputFile;
}COMMAND;



int performCommand(COMMAND* myLocalCommand);
int performPipingCommand(COMMAND* myLocalCommand);

int performGlobedCommand();

extern COMMAND* myCommand;
extern COMMAND* myGlobCommand;
extern int type;
extern int file_input;
extern int file_output;
extern int globCommand;
#endif